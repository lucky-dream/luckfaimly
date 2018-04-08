#include"fmis/lf_fmis_service_handler.h"
#include"task_svr/lf_token_mgr.h"
#include"dbmgr/lf_db_mgr.h"
#include"rapidjson/writer.h"
#include"rapidjson/stringbuffer.h"
#include <ctime>
namespace LF
{
	bool lf_fmis_service_handler::query_owner_bill(const lf_string & uid, const lf_string & param, lf_string & out_json)
	{
		return false;
	}
	bool lf_fmis_service_handler::add_owner_bill(const lf_string & uid, const lf_string & param, lf_string & out_json)
	{
		return false;
	}
	bool lf_fmis_service_handler::del_owner_bill(const lf_string & uid, const lf_string & param, lf_string & out_json)
	{
		return false;
	}
	bool lf_fmis_service_handler::sync_owner_bill_to_group(const lf_string & uid, const lf_string & param, lf_string & out_json)
	{
		return false;
	}
	bool lf_fmis_service_handler::query_group_bill(const lf_string & uid, const lf_string & param, lf_string & out_json)
	{
		return false;
	}
	bool lf_fmis_service_handler::compute_group_bill(const lf_string & uid, const lf_string & param, lf_string & out_json)
	{
		return false;
	}
	bool lf_fmis_service_handler::del_group_bill(const lf_string & uid, const lf_string & param, lf_string & out_json)
	{
		return false;
	}
}