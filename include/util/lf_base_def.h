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

	typedef int  int32_t;
	typedef unsigned int uint32_t;
	typedef short int16_t;
	typedef unsigned short uint16_t;
	typedef char int8_t;
	typedef unsigned char uint8_t;
	typedef std::string lf_string;
	typedef unsigned long long uint64_t;
	typedef long long int64_t;
}
#endif // !LF_BASE_DEF_H

