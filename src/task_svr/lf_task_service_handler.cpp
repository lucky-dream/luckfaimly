#include"task_svr/lf_task_service_handler.h"
#include"task_svr/lf_token_mgr.h"
namespace LF
{
	bool lf_task_service_handler::login(const lf_string & name, const lf_string & password, lf_string & out_json)
	{
		return false;
	}
	bool lf_task_service_handler::logout(const lf_string & token, lf_string & out_json)
	{
		lf_string uid = lf_token_mgr::singleton().get_uid_by_token(token);
		if (uid.empty())
		{
			return false;
		}
		return false;
	}
	bool lf_task_service_handler::user_register(const lf_string & param, lf_string & out_json)
	{
		return false;
	}
	bool lf_task_service_handler::register_confirm(const lf_string & param, lf_string & out_json)
	{
		return false;
	}
}