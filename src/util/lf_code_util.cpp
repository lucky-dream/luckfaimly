#include"util/lf_code_util.h"
#include<cctype>
namespace LF
{
	static const char *uppercase_hex_digits = "0123456789ABCDEF";
	static const char *lowcase_hex_digits = "0123456789abcdef";
	void lf_code_util::uint64_to_hex(uint64_t val, lf_string& out_data, bool low_case )
	{
		out_data.clear();
		out_data.reserve(32);
		char *ptr = (char*)&val;
		for (uint32_t i = 0; i < sizeof(uint64_t); i++) {
			if (low_case)
			{
				out_data += lowcase_hex_digits[(ptr[i] & 0xf0) >> 4];
				out_data += lowcase_hex_digits[ptr[i] & 0x0f];
			}
			else
			{
				out_data += uppercase_hex_digits[(ptr[i] & 0xf0) >> 4];
				out_data += uppercase_hex_digits[ptr[i] & 0x0f];
			}
		}
		//just:hacker
		ptr = (char*)out_data.c_str();
		ptr[out_data.size()] = '\0';
	}

	static const char b64_table[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	static const char reverse_table[128] = {
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
		64, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
		64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64
	};



	void lf_code_util::base64_encode(const lf_string& bindata, lf_string& out_data)
	{
		using std::numeric_limits;
#undef max
		if (bindata.size() > (numeric_limits<std::string::size_type>::max() / 4u) * 3u) {
			//throw length_error("Converting too large a string to base64.");
			 out_data.clear();
			 return;
		}

		const size_t binlen = bindata.size();
		// Use = signs so the end is properly padded.
		std::string retval((((binlen + 2) / 3) * 4), '=');
		size_t outpos = 0;
		int bits_collected = 0;
		unsigned int accumulator = 0;
		const lf_string::const_iterator binend = bindata.end();

		for (lf_string::const_iterator i = bindata.begin(); i != binend; ++i) {
			accumulator = (accumulator << 8) | (*i & 0xffu);
			bits_collected += 8;
			while (bits_collected >= 6) {
				bits_collected -= 6;
				retval[outpos++] = b64_table[(accumulator >> bits_collected) & 0x3fu];
			}
		}
		if (bits_collected > 0) { // Any trailing bits that are missing.
			accumulator <<= 6 - bits_collected;
			retval[outpos++] = b64_table[accumulator & 0x3fu];
		}
		out_data.assign(retval);
	}
	void lf_code_util::base64_decode(const lf_string& ascdata, lf_string& out_data)
	{
		lf_string retval;
		const lf_string::const_iterator last = ascdata.end();
		int bits_collected = 0;
		unsigned int accumulator = 0;

		for (lf_string::const_iterator i = ascdata.begin(); i != last; ++i) {
			const int c = *i;
			if (isspace(c) || c == '=') {
				// Skip whitespace and padding. Be liberal in what you accept.
				continue;
			}
			if ((c > 127) || (c < 0) || (reverse_table[c] > 63)) {
				out_data.clear();
				return;
			}
			accumulator = (accumulator << 6) | reverse_table[c];
			bits_collected += 6;
			if (bits_collected >= 8) {
				bits_collected -= 8;
				retval += (char)((accumulator >> bits_collected) & 0xffu);
			}
		}
		out_data.append(retval);
	}
}