#ifndef LF_FMIS_HTTP_DISPATH_H
#define LF_FMIS_HTTP_DISPATH_H
#include"util/lf_name_value_collection.h"
#include"net/lf_context.h"
namespace LF
{
	class lf_fmis_http_dispath
	{
	public:
		static void fmis_http_service_dispath(const LFCtxPtr & ctx,const lf_name_value_collection& params,const lf_string& op);
		static void request_fwd(const LFCtxPtr & ctx,const lf_string& op);
	};
}
#endif // !LF_FMIS_HTTP_DISPATH_H

