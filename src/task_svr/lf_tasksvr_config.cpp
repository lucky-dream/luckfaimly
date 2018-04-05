#include"task_svr/lf_tasksvr_config.h"
namespace LF
{
	OBJ_SINGLETON_INIT(lf_tasksvr_config_mgr);
	lf_tasksvr_config_mgr g_lf_tasksvr_config_mgr;
	bool lf_tasksvr_config_mgr::read_config_file(const lf_string & path)
	{
		return false;
	}
	bool lf_tasksvr_config_mgr::parse_tasksvr_config()
	{
		return false;
	}
	bool lf_tasksvr_config_mgr::parse_proxy_config()
	{
		return false;
	}
}