#ifndef LF_CODE_UTIL
#define LF_CODE_UTIL
#include"util/lf_base_def.h"
namespace LF
{
	class lf_code_util
	{
	public:
		static void base64_encode(const lf_string& data, lf_string& out_data);
		static void base64_decode(const lf_string& data, lf_string& out_data);
		static void uint64_to_hex(uint64_t val, lf_string& out_data,bool low_case = false);
	};

} //end unispace
#endif //?_US_CODE_UTIL_H_4161A2AC_6039_4A6A_B069_008BD1F78BC5_