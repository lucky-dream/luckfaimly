#include"task_svr/lf_user_register_cache.h"
namespace LF
{
	void lf_user_register_cache::clear_timeout()
	{
		lf_lock::scoped_lock scoped(_mutex);
		_users.clear();
	}
	bool lf_user_register_cache::add_recode(const UserInfoPtr & user_info)
	{
		lf_lock::scoped_lock scoped(_mutex);
		auto it = _users.find(user_info->_name);
		if (it == _users.end())
		{
			_users.insert(std::make_pair(user_info->_name, user_info));
			return true;
		}
		return false;
	}
	bool lf_user_register_cache::has_recode(const lf_string & name)
	{
		lf_lock::scoped_lock scoped(_mutex);
		auto it = _users.find(name);
		if (it == _users.end())
		{
			return false;
		}
		return true;
	}
	bool lf_user_register_cache::del_recode(const lf_string & name)
	{
		lf_lock::scoped_lock scoped(_mutex);
		auto it = _users.find(name);
		if (it == _users.end())
		{
			return true;
		}
		_users.erase(it);
		return true;
	}
	UserInfoPtr lf_user_register_cache::get_user_info(const lf_string & name)
	{
		lf_lock::scoped_lock scoped(_mutex);
		auto it = _users.find(name);
		if (it == _users.end())
		{
			return UserInfoPtr();
		}
		return it->second;
	}
}