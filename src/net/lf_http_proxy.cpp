#include "net/lf_http_proxy.h"
#include"evpp/httpc/request.h"
#include"evpp/httpc/response.h"
#include"net/lf_proxy_conf.h"
#include"net/lf_http_def.h"
#include"util/lf_name_value_collection.h"
namespace LF
{
	void lf_http_proxy::proxy_by_svr_name(const lf_string && uri, const LFCtxPtr && ctx,
		evpp::EventLoop * loop, const evpp::http::HTTPSendResponseCallback && cb)
	{
		lf_string proxy_url  = ctx->original_uri();
		Uint32 index = proxy_url.find(uri);
		proxy_url = proxy_url.substr(index+uri.size()+1);
		lf_string host;
		if (lf_proxy_conf::singleton().is_proxy_fwd())
		{
			lf_proxy_conf::singleton().find_host(LF_PROXY_DOMAIN, host);
		}
		else
		{
			index = proxy_url.find_first_of("\?");
			lf_string domain = proxy_url.substr(0, index);
			lf_proxy_conf::singleton().find_host(domain, host);
		}
		if (host.empty())
		{
			ctx->AddResponseHeader("Content-Length", std::to_string(ctx->get_response_http_body().length()));
			ctx->set_response_http_code(lf_http_def::HTTP_NOT_FOUND);
			cb(ctx->get_response_http_body());
			return;
		}
		proxy_url = host + "/" + proxy_url;
		std::shared_ptr<evpp::httpc::Request> r(new evpp::httpc::Request(loop,
			proxy_url, ctx->body(),evpp::Duration(3.0)));
		lf_name_value_collection fwd_head = ctx->get_fwd_http_heads();
		for (auto it =fwd_head.begin();it!=fwd_head.end();it++)
		{
			r->AddHeader(it->first,it->second);
		}
		auto f = [ctx, cb](const std::shared_ptr<evpp::httpc::Response>& response){/
			ctx->set_response_http_code(response->http_code());
			std::string rc = response->body().ToString();
			cb(rc);
		};
		r->Execute(f);
	}

}
