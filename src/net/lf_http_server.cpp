#include "net/lf_http_server.h"
#include "net/lf_http_proxy.h"
namespace LF
{
	lf_http_server::lf_http_server(const uint32_t & thread_num)
	{
		_svr.reset(new evpp::http::Server(thread_num));
	}
	lf_http_server::~lf_http_server()
	{
	}
	bool lf_http_server::Init(int listen_port)
	{
		if (!_svr.get())
		{
			//todo:@str set log
			return false;
		}
		return _svr->Init(listen_port);
	}
	bool lf_http_server::Init(const std::vector<int>& listen_ports)
	{
		if (!_svr.get())
		{
			//todo:@str set log
			return false;
		}
		return _svr->Init(listen_ports);
	}
	bool lf_http_server::Init(const std::string & listen_ports)
	{
		if (!_svr.get())
		{
			//todo:@str set log
			return false;
		}
		return _svr->Init(listen_ports);
	}
	bool lf_http_server::Start()
	{
		if (!_svr.get())
		{
			//todo:@str set log
			return false;
		}
		return _svr->Start();
	}
	void lf_http_server::Stop()
	{
		if (!_svr.get())
		{
			//todo:@str set log
			return;
		}
		_svr->Stop();
	}
	void lf_http_server::Pause()
	{
		if (!_svr.get())
		{
			//todo:@str set log
			return;
		}
		_svr->Pause();
	}
	void lf_http_server::Continue()
	{
		if (!_svr.get())
		{
			//todo:@str set log
			return;
		}
		_svr->Continue();
	}
	void lf_http_server::AfterFork()
	{
		if (!_svr.get())
		{
			//todo:@str set log
			return;
		}
		_svr->AfterFork();
	}

	bool lf_http_server::IsRunning()
	{
		if (!_svr.get())
		{
			//todo:@str set log
			return false;
		}
		return _svr->IsRunning();
	}
	
	void lf_http_server::RegisterHandler(const std::string & uri, LF_HTTPRequestCB callback)
	{
		if (!_svr.get())
		{
			//todo:@str set log
			return;
		}
		auto f = [uri, callback](evpp::EventLoop* loop,
			const evpp::http::ContextPtr& evpp_ctx,
			const evpp::http::HTTPSendResponseCallback& cb) {
			LFCtxPtr ctx(new lf_context(evpp_ctx));
			callback(ctx);
			lf_string proxy_url = ctx->original_uri();
			uint32_t index = proxy_url.find(uri);
			if (proxy_url[index + uri.size() + 1] != '?'||ctx->get_response_handler_type() == LFResponseHandlerType::LF_NORMAL)
			{
				ctx->AddResponseHeader("Content-Length", std::to_string(ctx->get_response_http_body().length()));
				cb(ctx->get_response_http_body());
				return;
			}
			else if(ctx->get_response_handler_type() == LFResponseHandlerType::LF_PROXY)
			{
				lf_http_proxy::proxy_by_svr_name(std::move(uri),std::move(ctx),
					loop,std::move(cb));
			}
		};
		_svr->RegisterHandler(uri,f);
	}
#ifndef LF_TASKSVR_NAME
#define LF_TASKSVR_NAME "task"
#endif // !LF_TASKSVR_NAME

	void lf_http_server::RegisterDefaultHandler(LF_HTTPRequestCB callback)
	{
		if (!_svr.get())
		{
			//todo:@str set log
			return;
		}
		lf_string uri(LF_TASKSVR_NAME);
		auto f = [uri,callback](evpp::EventLoop* loop,
			const evpp::http::ContextPtr& evpp_ctx,
			const evpp::http::HTTPSendResponseCallback& cb) {
			LFCtxPtr ctx(new lf_context(evpp_ctx));
			callback(ctx);
			lf_string proxy_url = ctx->original_uri();
			uint32_t index = proxy_url.find(uri);
			if (proxy_url[index + uri.size() + 1] != '?' || ctx->get_response_handler_type() == LFResponseHandlerType::LF_NORMAL)
			{
				ctx->AddResponseHeader("Content-Length", std::to_string(ctx->get_response_http_body().length()));
				cb(ctx->get_response_http_body());
				return;
			}
			else if (ctx->get_response_handler_type() == LFResponseHandlerType::LF_PROXY)
			{
				lf_http_proxy::proxy_by_svr_name(std::move(uri), std::move(ctx),
					loop, std::move(cb));
			}
		};
		_svr->RegisterDefaultHandler(f);
	}
}

