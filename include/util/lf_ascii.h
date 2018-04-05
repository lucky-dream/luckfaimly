#ifndef LF_ASCII_H
#define LF_ASCII_H
#include"util/lf_base_def.h"
namespace LF
{
	/// This class contains enumerations and static
	/// utility functions for dealing with ASCII characters
	/// and their properties.
	///
	/// The classification functions will also work if
	/// non-ASCII character codes are passed to them,
	/// but classification will only check for
	/// ASCII characters.
	///
	/// This allows the classification methods to be used
	/// on the single bytes of a UTF-8 string, without
	/// causing assertions or inconsistent results (depending
	/// upon the current locale) on bytes outside the ASCII range,
	/// as may be produced by lf_ascii::isSpace(), etc.
	class lf_ascii
	{
	public:
		enum CharacterProperties
			/// ASCII character properties.
		{
			US_ACP_CONTROL = 0x0001,
			US_ACP_SPACE = 0x0002,
			US_ACP_PUNCT = 0x0004,
			US_ACP_DIGIT = 0x0008,
			US_ACP_HEXDIGIT = 0x0010,
			US_ACP_ALPHA = 0x0020,
			US_ACP_LOWER = 0x0040,
			US_ACP_UPPER = 0x0080,
			US_ACP_GRAPH = 0x0100,
			US_ACP_PRINT = 0x0200
		};

		static int properties(int ch);
		/// Return the ASCII character properties for the
		/// character with the given ASCII value.
		///
		/// If the character is outside the ASCII range
		/// (0 .. 127), 0 is returned.

		static bool has_some_properties(int ch, int properties);
		/// Returns true if the given character is
		/// within the ASCII range and has at least one of 
		/// the given properties.

		static bool has_properties(int ch, int properties);
		/// Returns true if the given character is
		/// within the ASCII range and has all of 
		/// the given properties.

		static bool isAscii(int ch);
		/// Returns true iff the given character code is within
		/// the ASCII range (0 .. 127).

		static bool isSpace(int ch);
		/// Returns true iff the given character is a whitespace.

		static bool isDigit(int ch);
		/// Returns true iff the given character is a digit.

		static bool isHexDigit(int ch);
		/// Returns true iff the given character is a hexadecimal digit.

		static bool isPunct(int ch);
		/// Returns true iff the given character is a punctuation character.

		static bool isAlpha(int ch);
		/// Returns true iff the given character is an alphabetic character.	

		static bool isAlphaNumeric(int ch);
		/// Returns true iff the given character is an alphabetic character.	

		static bool isLower(int ch);
		/// Returns true iff the given character is a lowercase alphabetic
		/// character.

		static bool isUpper(int ch);
		/// Returns true iff the given character is an uppercase alphabetic
		/// character.

		static int toLower(int ch);
		/// If the given character is an uppercase character,
		/// return its lowercase counterpart, otherwise return
		/// the character.

		static int toUpper(int ch);
		/// If the given character is a lowercase character,
		/// return its uppercase counterpart, otherwise return
		/// the character.

	private:
		lf_ascii();
		static const int CHARACTER_PROPERTIES[128];
	};
	inline int lf_ascii::properties(int ch)
	{
		if (isAscii(ch))
			return CHARACTER_PROPERTIES[ch];
		else
			return 0;
	}


	inline bool lf_ascii::isAscii(int ch)
	{
		return (static_cast<uint32_t>(ch)& 0xFFFFFF80) == 0;
	}


	inline bool lf_ascii::has_properties(int ch, int props)
	{
		return (properties(ch) & props) == props;
	}


	inline bool lf_ascii::has_some_properties(int ch, int props)
	{
		return (properties(ch) & props) != 0;
	}


	inline bool lf_ascii::isSpace(int ch)
	{
		return has_properties(ch, US_ACP_SPACE);
	}


	inline bool lf_ascii::isDigit(int ch)
	{
		return has_properties(ch, US_ACP_DIGIT);
	}


	inline bool lf_ascii::isHexDigit(int ch)
	{
		return has_properties(ch, US_ACP_HEXDIGIT);
	}


	inline bool lf_ascii::isPunct(int ch)
	{
		return has_properties(ch, US_ACP_PUNCT);
	}


	inline bool lf_ascii::isAlpha(int ch)
	{
		return has_properties(ch, US_ACP_ALPHA);
	}


	inline bool lf_ascii::isAlphaNumeric(int ch)
	{
		return has_some_properties(ch, US_ACP_ALPHA | US_ACP_DIGIT);
	}


	inline bool lf_ascii::isLower(int ch)
	{
		return has_properties(ch, US_ACP_LOWER);
	}


	inline bool lf_ascii::isUpper(int ch)
	{
		return has_properties(ch, US_ACP_UPPER);
	}


	inline int lf_ascii::toLower(int ch)
	{
		if (isUpper(ch))
			return ch + 32;
		else
			return ch;
	}


	inline int lf_ascii::toUpper(int ch)
	{
		if (isLower(ch))
			return ch - 32;
		else
			return ch;
	}

} 
#endif 