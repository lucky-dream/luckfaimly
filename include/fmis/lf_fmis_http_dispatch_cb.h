#ifndef LF_FMIS_HTTP_DISPATCH_CB_H
#define LF_FMIS_HTTP_DISPATCH_CB_H
#include"net/lf_context.h"
#define LF_FMIS_NAME "fmis"
namespace LF
{
	class lf_fmis_http_dispatch_cb
	{
	public:
		static void fmis_http_handler_callback(const LFCtxPtr& ctx);
		static void default_http_handler_callback(const LFCtxPtr& ctx);
	};
}
#endif // !LF_FMIS_HTTP_DISPATCH_CB_H

