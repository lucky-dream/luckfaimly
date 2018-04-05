#ifndef LF_SCOPED_LOCK_H
#define LF_SCOPED_LOCK_H
#include"util/lf_base_def.h"
namespace LF {
#if defined(_DEBUG) 
#define US_UNEXPECTED() 
#else 
#define US_UNEXPECTED() 
#endif
	template <class M>
	class LF_DLL_API lf_scoped_lock
		/// A class that simplifies thread synchronization
		/// with a mutex.
		/// The constructor accepts a Mutex (and optionally
		/// a timeout value in milliseconds) and locks it.
		/// The destructor unlocks the mutex.
	{
	public:
		explicit lf_scoped_lock(M& mutex) : _mutex(mutex)
		{
			_mutex.lock();
		}

		lf_scoped_lock(M& mutex, long milliseconds) : _mutex(mutex)
		{
			_mutex.lock(milliseconds);
		}

		~lf_scoped_lock()
		{
			try
			{
				_mutex.unlock();
			}
			catch (...)
			{
				US_UNEXPECTED();
			}
		}

	private:
		M& _mutex;

		lf_scoped_lock();
		lf_scoped_lock(const lf_scoped_lock&);
		lf_scoped_lock& operator = (const lf_scoped_lock&);
	};


	template <class M>
	class LF_DLL_API lf_scoped_lock_with_unlock
		/// A class that simplifies thread synchronization
		/// with a mutex.
		/// The constructor accepts a Mutex (and optionally
		/// a timeout value in milliseconds) and locks it.
		/// The destructor unlocks the mutex.
		/// The unlock() member function allows for manual
		/// unlocking of the mutex.
	{
	public:
		explicit lf_scoped_lock_with_unlock(M& mutex) : _pMutex(&mutex)
		{
			_pMutex->lock();
		}

		lf_scoped_lock_with_unlock(M& mutex, long milliseconds) : _pMutex(&mutex)
		{
			_pMutex->lock(milliseconds);
		}

		~lf_scoped_lock_with_unlock()
		{
			try
			{
				unlock();
			}
			catch (...)
			{
				US_UNEXPECTED();
			}
		}

		void unlock()
		{
			if (_pMutex)
			{
				_pMutex->unlock();
				_pMutex = 0;
			}
		}

	private:
		M* _pMutex;

		lf_scoped_lock_with_unlock();
		lf_scoped_lock_with_unlock(const lf_scoped_lock_with_unlock&);
		lf_scoped_lock_with_unlock& operator = (const lf_scoped_lock_with_unlock&);
	};



}
#endif //
