#include "net/lf_proxy_conf.h"
namespace LF
{
	OBJ_SINGLETON_INIT(lf_proxy_conf);
	lf_proxy_conf g_lf_proxy_conf;
	bool lf_proxy_conf::add_host(const lf_string & url, const lf_string & host)
	{
		lf_lock::scoped_lock scoped_mutex(_mutex);
		auto it = _conf_map.find(url);
		if (it == _conf_map.end())
		{
			_conf_map.insert(std::make_pair(url,host));
			return true;
		}
		it->second.assign(host);
		return true;
	}

	bool lf_proxy_conf::find_host(const lf_string & url, lf_string & host)
	{
		lf_lock::scoped_lock scoped_mutex(_mutex);
		auto it = _conf_map.find(url);
		if (it == _conf_map.end())
		{
			return false;
		}
		host.assign(it->second);
		return true;
	}

	void lf_proxy_conf::del_host(const lf_string & url)
	{
		lf_lock::scoped_lock scoped_mutex(_mutex);
		auto it = _conf_map.find(url);
		if (it == _conf_map.end())
		{
			return ;
		}
		_conf_map.erase(it);
		return ;
	}
}

