#include"net/lf_context.h"
namespace LF
{

	lf_context::lf_context(const evpp::http::ContextPtr & ctx , const lf_string rsp_body
		, const LFResponseHandlerType rsp_type):_ctx(ctx),_rsp_body(rsp_body),
		_rsp_type(rsp_type)
		
	{
	}
	lf_context::~lf_context()
	{
	}
	bool lf_context::Init()
	{
		if (!_ctx.get())
		{
			//todo:@str set log
			return false;
		}
		return _ctx->Init();
	}
	void lf_context::AddResponseHeader(const std::string & key, const std::string & value)
	{
		if (!_ctx.get())
		{
			//todo:@str set log
			return ;
		}
		return _ctx->AddResponseHeader(key,value);
	}
	const char * lf_context::FindRequestHeader(const char * key)
	{
		if (!_ctx.get())
		{
			//todo:@str set log
			return NULL;
		}
		return _ctx->FindRequestHeader(key);
	}
	const char * lf_context::original_uri() const
	{
		if (!_ctx.get())
		{
			//todo:@str set log
			return NULL;
		}
		return _ctx->original_uri();
	}
	const std::string & lf_context::uri() const
	{
		if (!_ctx.get())
		{
			//todo:@str set log
			return std::string();
		}
		return _ctx->uri();
	}
	const std::string & lf_context::remote_ip() const
	{
		if (!_ctx.get())
		{
			//todo:@str set log
			return std::string();
		}
		return _ctx->remote_ip();
	}
	const lf_string & lf_context::body() const
	{
		if (!_ctx.get())
		{
			//todo:@str set log
			return lf_string();
		}
		return lf_string(_ctx->body().data(),_ctx->body().size());
	}
	evhttp_request * lf_context::req() const
	{
		if (!_ctx.get())
		{
			//todo:@str set log
			return NULL;
		}
		return _ctx->req();
	}
	void lf_context::set_response_http_code(int code)
	{
		if (!_ctx.get())
		{
			//todo:@str set log
			return;
		}
		_ctx->set_response_http_code(code);
	}
	int lf_context::response_http_code() const
	{
		if (!_ctx.get())
		{
			//todo:@str set log
			return 0;
		}
		return _ctx->response_http_code();
	}
	void lf_context::set_response_http_body(const lf_string & body)
	{
		_rsp_body.assign(_rsp_body);
	}
	bool lf_context::add_fwd_http_head(const lf_string & name, const lf_string & value)
	{
		if (_inside_head.has(name))
		{
			_inside_head.erase(name);
		}
		_inside_head.add(name,value);
		return true;
	}
	std::string lf_context::GetQuery(const char * query_key, size_t key_len)
	{
		if (!_ctx.get())
		{
			//todo:@str set log
			return std::string();
		}
		return _ctx->GetQuery(query_key, key_len);
	}
	std::string lf_context::GetQuery(const std::string & query_key)
	{
		if (!_ctx.get())
		{
			//todo:@str set log
			return std::string();
		}
		return _ctx->GetQuery(query_key);
	}
	std::string lf_context::FindClientIPFromURI(const char * uri, size_t uri_len)
	{
		return evpp::http::Context::FindClientIPFromURI(uri,uri_len);
	}
	std::string lf_context::FindQueryFromURI(const char * uri, size_t uri_len, const char * key, size_t key_len)
	{
		return evpp::http::Context::FindQueryFromURI(uri,uri_len,key,key_len);
	}
	std::string lf_context::FindQueryFromURI(const char * uri, const char * key)
	{
		return evpp::http::Context::FindQueryFromURI(uri,key);
	}
	std::string lf_context::FindQueryFromURI(const std::string & uri, const std::string & key)
	{
		return evpp::http::Context::FindQueryFromURI(uri,key);
	}
}