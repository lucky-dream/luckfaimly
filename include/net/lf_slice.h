#ifndef LF_SLICE_H
#define LF_SLICE_H
#include "evpp/slice.h"
namespace LF
{
	class lf_slice :public evpp::Slice
	{
	public:
		lf_slice(evpp::Slice s) : evpp::Slice(s) {}
		lf_slice() : evpp::Slice(){}

		// Create a slice that refers to d[0,n-1].
		lf_slice(const char* d, size_t n) : evpp::Slice(d,n){}

		// Create a slice that refers to the contents of "s"
		lf_slice(const std::string& s) : evpp::Slice(s) {}

		// Create a slice that refers to s[0,strlen(s)-1]
		lf_slice(const char* s) : evpp::Slice(s) {}
	};
}
#endif // !IF_SLICE_H

