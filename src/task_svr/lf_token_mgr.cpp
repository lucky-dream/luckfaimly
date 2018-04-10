#include"task_svr/lf_token_mgr.h"
#include "xxhash/xxhash.h"
#include "util/lf_code_util.h"
#include <ctime>
namespace LF
{
	OBJ_SINGLETON_INIT(lf_token_mgr);
	lf_token_mgr g_lf_token_mgr;
	lf_string lf_token_mgr::gen_token(const lf_string & name, const lf_string & password)
	{
		uint64_t now = time(NULL);
		lf_string info = name + password + std::to_string(now);
		uint64_t token_num = XXH64(info.c_str(), info.length(),2018);
		lf_string token;
		lf_code_util::uint64_to_hex(token_num, token);
		return token;
	}
	bool lf_token_mgr::add_token(const lf_token_info& token_info)
	{
		lf_lock::scoped_lock scoped(_mutex);
		auto it = _token_token.find(token_info.token);
		if (it== _token_token.end())
		{
			_token_token.insert(std::make_pair(token_info.token,token_info));
			return true;
		}
		return false;
	}
	bool lf_token_mgr::is_online_by_token(const lf_string & token)
	{
		lf_lock::scoped_lock scoped(_mutex);
		auto it = _token_token.find(token);
		if (it == _token_token.end())
		{
			return true;
		}
		return false;
	}
	bool lf_token_mgr::is_online_by_name(const lf_string & name)
	{
		lf_lock::scoped_lock scoped(_mutex);
		auto it = _name_token.find(name);
		if (it == _name_token.end())
		{
			return true;
		}
		return false;
	}
	lf_string lf_token_mgr::get_uid_by_token(const lf_string & token)
	{
		lf_lock::scoped_lock scoped(_mutex);
		auto it = _token_token.find(token);
		if (it == _token_token.end())
		{
			return lf_string();
		}
		return it->second.uid;
	}
	void lf_token_mgr::del_token_by_token(const lf_string & token)
	{
		lf_lock::scoped_lock scoped(_mutex);
		auto it = _token_token.find(token);
		if (it == _token_token.end())
		{
			return;
		}
		_token_token.erase(it);
	}
	void lf_token_mgr::del_token_by_name(const lf_string & name)
	{
		lf_lock::scoped_lock scoped(_mutex);
		auto it = _name_token.find(name);
		if (it == _name_token.end())
		{
			return;
		}
		_name_token.erase(it);
	}
}