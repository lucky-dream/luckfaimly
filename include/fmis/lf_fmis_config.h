#ifndef LF_FMIS_CONFIG_H
#define LF_FMIS_CONFIG_H
#include"util/lf_singleton.h"
namespace LF
{
	struct lf_fmis_config_info 
	{
		lf_string ip;
		lf_string port;
	};
	class lf_fmis_config_mgr :public lf_singleton<lf_fmis_config_mgr>
	{
	public:
		bool read_config_file(const lf_string& path);
		lf_fmis_config_info get_tasksvr_info() {
			return _tasksvr;
		}
	private:
		lf_fmis_config_info _tasksvr;
	};
}
#endif // !LF_FMIS_CONFIG_H

