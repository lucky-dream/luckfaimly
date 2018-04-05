#include"task_svr/lf_token_mgr.h"
namespace LF
{
	OBJ_SINGLETON_INIT(lf_token_mgr);
	lf_token_mgr g_lf_token_mgr;
	lf_string lf_token_mgr::gen_token(const lf_string & name, const lf_string & password)
	{
		return lf_string();
	}
	bool lf_token_mgr::add_token(const lf_string & uid, const lf_string & token)
	{
		return false;
	}
	bool lf_token_mgr::is_online(const lf_string & token)
	{
		return false;
	}
	lf_string lf_token_mgr::get_uid_by_token(const lf_string & token)
	{
		return lf_string();
	}
	void lf_token_mgr::del_token(const lf_string & token)
	{
	}
}