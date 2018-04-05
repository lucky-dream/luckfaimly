#ifndef LF_HTTP_PROXY_H
#define LF_HTTP_PROXY_H
#include"util/lf_base_def.h"
#include"net/lf_context.h"
namespace LF
{
	class lf_http_proxy
	{
	public:
		static void proxy_by_svr_name(const lf_string && uri, const LFCtxPtr && ctx,
			evpp::EventLoop * loop, const evpp::http::HTTPSendResponseCallback && cb);

	};
}
#endif // !LF_HTTP_PROXY_H

