#include"task_svr/lf_task_http_dispath.h"
#include"net/lf_http_def.h"
#include"task_svr/lf_tasksvr_constant_def.h"
#include"task_svr/lf_task_service_handler.h"
#include"task_svr/lf_token_mgr.h"
#include"util\lf_code_util.h"
namespace LF
{
	static bool UriDecode(const std::string& str, std::string& decodedStr, bool plusAsSpace)
	{
		bool inQuery = false;
		std::string::const_iterator it = str.begin();
		std::string::const_iterator end = str.end();
		while (it != end)
		{
			char c = *it++;
			if (c == '?') inQuery = true;
			// spaces may be encoded as plus signs in the query
			if (inQuery && plusAsSpace && c == '+') c = ' ';
			else if (c == '%')
			{
				if (it == end) return false;
				char hi = *it++;
				if (it == end) return false;
				char lo = *it++;
				if (hi >= '0' && hi <= '9')
					c = hi - '0';
				else if (hi >= 'A' && hi <= 'F')
					c = hi - 'A' + 10;
				else if (hi >= 'a' && hi <= 'f')
					c = hi - 'a' + 10;
				else return false;
				c *= 16;
				if (lo >= '0' && lo <= '9')
					c += lo - '0';
				else if (lo >= 'A' && lo <= 'F')
					c += lo - 'A' + 10;
				else if (lo >= 'a' && lo <= 'f')
					c += lo - 'a' + 10;
				else return false;
			}
			decodedStr += c;
		}
		return true;
	}

	static bool is_basic(const lf_string& auth)
	{
		if (auth.length() <= 5)
		{
			return false;
		}
		lf_string basic = auth.substr(0,5);
		if (basic == "Basic")
		{
			return true;
		}
		return false;
	}

	static lf_string decode_base64(lf_string auth)
	{
		if (auth.length() < 6)
		{
			return lf_string();
		}
		lf_string user_data = auth.substr(6, auth.length()-6);
		if (user_data.empty())
		{
			return lf_string();
		}
		lf_string out_user_data;
		lf_code_util::base64_decode(user_data, out_user_data);
		return out_user_data;
	}

	void LF::lf_task_http_dispath::task_http_service_dispath(const LFCtxPtr & ctx, const lf_name_value_collection& params, const lf_string& op)
	{
		Uint32 cmd = lf_task_cmd_map::singleton().get_cmd(op);
		bool ret = false;
		lf_string body;
		LFResponseHandlerType rht = LFResponseHandlerType::LF_NORMAL;
		switch (cmd)
		{
		case LF_TASK_CMD_LOGIN:
		{
			lf_string name,password;
			lf_string str = "Authenticate";
			const char* auth = ctx->FindRequestHeader(str.c_str());
			if (auth == NULL)
			{
				ret = false;
				body.append("Not Authenticate!");
			}
			else 
			{
				if (!is_basic(auth))
				{
					ret = false;
					body.append("Not Auth!");
				}
				else
				{
					lf_string user_info = decode_base64(auth);
					if (user_info.empty())
					{
						ret = false;
						body.append("Not UserInfo!");
					}
					else
					{
						int index = user_info.find_first_of(":");
						name = user_info.substr(0, index);
						password = user_info.substr(index+1, user_info.length() - index - 1);
						ret = lf_task_service_handler::login(name, password, body);
					}			
				}	
			}
			ctx->set_response_http_code(ret ? lf_http_def::HTTP_OK : lf_http_def::HTTP_UNAUTHORIZED);
			ctx->AddResponseHeader("Content-Type", "text/html");
			ctx->AddResponseHeader("Server", "LF_TASK");
			ctx->AddResponseHeader("Access-Control-Allow-Origin", "*");
			ctx->AddResponseHeader("Transfer-Encoding", "utf-8");
			ctx->AddResponseHeader("Content-Length", std::to_string(body.length()));
			ctx->set_response_http_body(body);
			return;
		}
		case LF_TASK_CMD_LOGOUT:
		{
			std::string token = params.get("token", "?");
			lf_task_service_handler::logout(token,body);
			break;
		}
		case LF_TASK_CMD_REGISTER:
		{
			std::string param = ctx->body();
			ret = lf_task_service_handler::user_register(param, body);
			break;
		}
		case LF_TASK_CMD_CONFIRM:
		{
			std::string param = ctx->body();
			ret = lf_task_service_handler::register_confirm(param, body);
			break;
		}
		default:
			break;
		}
		if (rht == LFResponseHandlerType::LF_NORMAL)
		{
			ctx->set_response_http_code(ret ? lf_http_def::HTTP_OK : lf_http_def::HTTP_BAD_REQUEST);
			ctx->AddResponseHeader("Content-Type", "text/html");
			ctx->AddResponseHeader("Server", "LF_TASK");
			ctx->AddResponseHeader("Access-Control-Allow-Origin", "*");
			ctx->AddResponseHeader("Transfer-Encoding", "utf-8");
			ctx->AddResponseHeader("Content-Length", std::to_string(body.length()));
			ctx->set_response_http_body(body);
			ctx->set_response_hander_type(rht);
		}
		return;
	}
	void lf_task_http_dispath::request_fwd(const LFCtxPtr & ctx, const lf_string & op)
	{

	}
}