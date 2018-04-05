#ifndef _LF_SINGLETON_H
#define _LF_SINGLETON_H
#include"lf_base_def.h"
#include <assert.h>
namespace LF{

	template <typename T>
	class lf_singleton
	{
	protected:
		static T* singleton_;

	public:
		lf_singleton(void)
		{
			assert(!singleton_);
#if defined(_MSC_VER) && _MSC_VER < 1200	 
			int offset = (int)(T*)1 - (int)(lf_singleton <T>*)(T*)1;
			singleton_ = (T*)((int)this + offset);
#else
			singleton_ = static_cast< T* >(this);
#endif
		}


		~lf_singleton(void){ assert(singleton_);  singleton_ = 0; }

		static T& singleton(void) { assert(singleton_);  return (*singleton_); }
		static T* singleton_ptr(void){ return singleton_; }
	};

#define OBJ_SINGLETON_INIT(TYPE)					\
 template <>	 TYPE * lf_singleton< TYPE >::singleton_ = 0;


}

#endif //!_LF_SINGLETON_H