#ifndef LF_PROXY_CONF_H
#define LF_PROXY_CONF_H
#include"util/lf_base_def.h"
#include"util/lf_singleton.h"
#include"util/lf_lock.h"
#include <map>
namespace LF
{
#define LF_PROXY_DOMAIN "proxy"
	typedef std::map<lf_string, lf_string> ConfMap;
	class lf_proxy_conf:public lf_singleton<lf_proxy_conf>
	{
	public:
		bool add_host(const lf_string& url,const lf_string& host);
		bool find_host(const lf_string& url, lf_string& host);
		void del_host(const lf_string& url);
		void set_is_proxy_fwd(bool is_proxy_fwd)
		{
			_is_proxy_fwd = is_proxy_fwd;
		}
		bool is_proxy_fwd()
		{
			return _is_proxy_fwd;
		}
	private:
		ConfMap _conf_map;
		bool _is_proxy_fwd;
		lf_lock _mutex;
	};
}
#endif // !LF_PROXY_CONF_H

