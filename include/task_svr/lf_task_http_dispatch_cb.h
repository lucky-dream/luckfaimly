#ifndef LF_TASK_HTTP_DISPATCH_CB_H
#define LF_TASK_HTTP_DISPATCH_CB_H
#include"net/lf_context.h"
#define LF_TASKSVR_NAME "task"
namespace LF
{
	class lf_task_http_dispatch_cb
	{
	public:
		static void task_http_handler_callback(const LFCtxPtr& ctx);
		static void default_http_handler_callback(const LFCtxPtr& ctx);
	};
}
#endif // !LF_TASK_HTTP_DISPATCH_CB_H

