#ifndef LF_OS_TYPE_H
#define LF_OS_TYPE_H

#ifdef _WIN32
#include <WinSock2.h>
#include <WinBase.h>
#include <Windows.h>
#include<errno.h>
#define millisleep(n) Sleep(n)
#define get_current_thread_id() GetCurrentThreadId()
#define get_process_pid()	  GetCurrentProcessId()	
#define strncasecmp(x,y,z) _strnicmp(x,y,z)
#else
#include <sys/epoll.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>		
#include <signal.h>
#include <unistd.h>
#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)
#define closesocket close
#define ioctlsocket ioctl
#define millisleep(n) usleep((n)*1000)
#define get_current_thread_id() gettid()
#define get_process_pid() getpid()
#endif

#endif /
