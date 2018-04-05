#ifndef LF_LOCK_H
#define LF_LOCK_H
#include"util/lf_base_def.h"
#include"util/lf_scoped_lock.h"
#include"util/lf_os_type.h"
namespace LF{
	class LF_DLL_API lf_fast_lock
	{
	public:
		lf_fast_lock();
		~lf_fast_lock();

	public:
#ifdef _WIN32
		CRITICAL_SECTION m_critical_section;
#else
		pthread_mutex_t m_mutex;
#endif
	};


	class LF_DLL_API lf_lock
	{
	public:
		typedef lf_scoped_lock<lf_lock> scoped_lock;
		typedef lf_scoped_lock_with_unlock<lf_lock> scoped_lock_with_unlock;
		void lock();
		void unlock();
#ifndef _WIN32
		virtual bool try_lock();
#endif
	private:
		lf_fast_lock	m_lock;
	};

	class LF_DLL_API lf_auto_lock
	{
	public:
		lf_auto_lock(lf_lock* pLock);
		virtual ~lf_auto_lock();
	private:
		lf_lock* m_pLock;
	};

}
#endif //