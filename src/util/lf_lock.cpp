#include"util/lf_lock.h"
namespace LF{
	lf_fast_lock::lf_fast_lock()
	{
#ifdef _WIN32
		InitializeCriticalSection(&m_critical_section);
#else
		pthread_mutex_init(&m_mutex, NULL);
#endif
	}

	lf_fast_lock::~lf_fast_lock()
	{
#ifdef _WIN32
		DeleteCriticalSection(&m_critical_section);
#else
		pthread_mutex_destroy(&m_mutex);
#endif
	}

	void lf_lock::lock()
	{
#ifdef _WIN32
		EnterCriticalSection(&m_lock.m_critical_section);
#else
		pthread_mutex_lock(&m_lock.m_mutex);
#endif
	}

	void lf_lock::unlock()
	{
#ifdef _WIN32
		LeaveCriticalSection(&m_lock.m_critical_section);
#else
		pthread_mutex_unlock(&m_lock.m_mutex);
#endif
	}

#ifndef _WIN32
	bool lf_lock::try_lock()
	{
		return pthread_mutex_trylock(&m_lock.m_mutex) == 0;
	}
#endif

	lf_auto_lock::lf_auto_lock(lf_lock* pLock)
	{
		m_pLock = pLock;
		if (NULL != m_pLock)
			m_pLock->lock();
	}

	lf_auto_lock::~lf_auto_lock()
	{
		if (NULL != m_pLock)
			m_pLock->unlock();
	}
}