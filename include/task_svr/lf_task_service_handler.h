#ifndef LF_TASK_SERVICE_HANDLER_H
#define LF_TASK_SERVICE_HANDLER_H
#include"util/lf_base_def.h"
namespace LF
{
	class lf_task_service_handler
	{
	public:
		static bool login(const lf_string& name,const lf_string& password,lf_string& out_json);
		static bool logout(const lf_string& uid,lf_string& out_json);
		static bool user_register(const lf_string& param,lf_string& out_json);
		static bool register_confirm(const lf_string& param, lf_string& out_json);
	private:

	}; 
}
#endif // !LF_TASK_SERVICE_HANDLER_H

