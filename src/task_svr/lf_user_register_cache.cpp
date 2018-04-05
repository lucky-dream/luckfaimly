#include"task_svr/lf_user_register_cache.h"
namespace LF
{
	void lf_user_register_cache::clear_timeout()
	{
	}
	bool lf_user_register_cache::add_recode(const UserInfoPtr & user_info)
	{
		return false;
	}
	bool lf_user_register_cache::has_recode(const lf_string & name)
	{
		return false;
	}
	bool lf_user_register_cache::del_recode(const lf_string & name)
	{
		return false;
	}
	UserInfoPtr lf_user_register_cache::get_user_info(const lf_string & name)
	{
		return UserInfoPtr();
	}
}