#include"fmis/lf_fmis_http_dispatch_cb.h"
#include"net/lf_http_def.h"
#include"net/lf_slice.h"
#include"util/lf_string_util.h"
#include"util/lf_name_value_collection.h"
#include"fmis/lf_fmis_http_dispatch.h"
namespace LF
{
	static void ParserURI(std::string& in_uri/*, std::string& out_theme, std::string& out_layer*/, lf_name_value_collection& out_nv)
	{
		std::string name;
		std::string value;
		name.reserve(64);
		value.reserve(64);
		std::string::const_iterator it = in_uri.begin();
		std::string::const_iterator end = in_uri.end();
		while (it != end)
		{
			name.clear();
			value.clear();
			while (it != end && *it != '=') { name += *it++; }
			while (it != end && *it == '=') { it++; }    //escape '='
			while (it != end && *it != '&') { value += *it++; }    //escape '/';
			while (it != end && *it == '&') { it++; }    //escape '&'
														 //keep the key to lower.
			out_nv.add(lf_string_util::toLowerInPlace(name), value);
		}
	}
	static void get_query_paramter(const std::string& orig_uri, std::string& out_str)
	{
		std::string::size_type pos = orig_uri.find('?');
		if (pos != std::string::npos)
		{
			out_str = orig_uri.substr(pos + 1);
			return;
		}
		out_str.append("");
	}
	void lf_fmis_http_dispatch_cb::fmis_http_handler_callback(const LFCtxPtr & ctx)
	{
		std::string query;
		//ctx->AddResponseHeader
		if ((lf_http_def::http_method_type)(ctx->get_req_type()) == lf_http_def::HTTP_REQ_GET
			|| (lf_http_def::http_method_type)(ctx->get_req_type()) == lf_http_def::HTTP_REQ_POST)
		{
			lf_string orig_uri = (ctx->original_uri() == nullptr) ? "" : ctx->original_uri();
			get_query_paramter(orig_uri, query);

		}
		else
		{
			ctx->set_response_http_code(lf_http_def::HTTP_NOT_IMPLEMENTED);
			ctx->AddResponseHeader("Content-Type", "text/html");
			ctx->AddResponseHeader("Server", "LF_TASK");
			ctx->AddResponseHeader("Access-Control-Allow-Origin", "*");
			ctx->AddResponseHeader("Transfer-Encoding", "utf-8");
			lf_string err = "Not Implemented£¡";
			ctx->AddResponseHeader("Content-Length", std::to_string(err.length()));
			ctx->set_response_http_body(err); 
			return;
		}
		lf_name_value_collection name_value;
		ParserURI(query, name_value);

		std::string op = name_value.get("op", "");
		if (op.empty())
		{
			ctx->set_response_http_code(lf_http_def::HTTP_BAD_REQUEST);
			ctx->AddResponseHeader("Content-Type", "text/html");
			ctx->AddResponseHeader("Server", "LF_TASK");
			ctx->AddResponseHeader("Access-Control-Allow-Origin", "*");
			ctx->AddResponseHeader("Transfer-Encoding", "utf-8");
			lf_string err = "Bad Request£¡";
			ctx->AddResponseHeader("Content-Length", std::to_string(err.length()));
			ctx->set_response_http_body(err);
			return;
		}
		lf_fmis_http_dispath::fmis_http_service_dispath(ctx,name_value, op);
	}
	void lf_fmis_http_dispatch_cb::default_http_handler_callback(const LFCtxPtr & ctx)
	{
		ctx->set_response_http_code(lf_http_def::HTTP_NOT_FOUND);
		ctx->AddResponseHeader("Content-Type", "text/html");
		ctx->AddResponseHeader("Server", "LF_TASK");
		ctx->AddResponseHeader("Access-Control-Allow-Origin", "*");
		ctx->AddResponseHeader("Transfer-Encoding", "utf-8");
		lf_string err = "Not Found£¡";
		ctx->AddResponseHeader("Content-Length", std::to_string(err.length()));
		ctx->set_response_http_body(err);
		return;
	}
}