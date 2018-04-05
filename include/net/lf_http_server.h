#ifndef LF_HTTP_SERVER_H
#define LF_HTTP_SERVER_H
#include"util/lf_base_def.h"
#include"evpp/http/http_server.h"
#include"net/lf_context.h"
namespace LF
{
	typedef std::shared_ptr<evpp::http::Server> HTTPSvrPtr;
	class LF_DLL_API lf_http_server
	{
	public:
		lf_http_server(const Uint32& thread_num);
		~lf_http_server();
		bool Init(int listen_port);
		bool Init(const std::vector<int>& listen_ports);
		bool Init(const std::string& listen_ports/*like "80,8080,443"*/);

		bool Start();

		void Stop();

		void Pause();
		void Continue();

		// @brief Reinitialize the event_base object after a fork
		void AfterFork();
		bool IsRunning();
	public:
		void RegisterHandler(const std::string& uri,
			LF_HTTPRequestCB callback);

		void RegisterDefaultHandler(LF_HTTPRequestCB callback);
	private:
		HTTPSvrPtr _svr;
	};
}
#endif // !LF_HTTP_SERVER_H

