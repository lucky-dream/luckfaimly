#ifndef LF_BASE_DEF_H
#define LF_BASE_DEF_H
#include <string>
namespace LF
{
#ifdef _WIN32
#ifndef DLL_EXPORT
#define LF_DLL_API __declspec(dllexport)
#else
#define LF_DLL_API __declspec(dllimport)
#endif
#endif // WIN32

	typedef int  Int32;
	typedef unsigned int Uint32;
	typedef short Int16;
	typedef unsigned short Uint16;
	typedef char Int8;
	typedef unsigned char Uint8;
	typedef std::string lf_string;
	typedef unsigned long long Uint64;
}
#endif // !LF_BASE_DEF_H

