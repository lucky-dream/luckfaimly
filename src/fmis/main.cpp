#include"util/lf_base_def.h"
#include"net/lf_http_server.h"
#include"fmis/lf_fmis_config.h"
#include"fmis/lf_fmis_http_dispatch_cb.h"



#define FMIS_THREAD_NUM 4

using namespace LF;
int main(int argc, char* argv[])
{
	lf_string path("./lf_service.conf");
	//todo:@str get path
	if (!lf_fmis_config_mgr::singleton().read_config_file(path))
	{
		return 1;
	}
	lf_fmis_config_info config = lf_fmis_config_mgr::singleton().get_tasksvr_info();
	if (config.ip.empty()||config.port.empty())
	{
		return 1;
	}
	lf_http_server http_svr(FMIS_THREAD_NUM);
	http_svr.RegisterDefaultHandler(&lf_fmis_http_dispatch_cb::default_http_handler_callback);
	http_svr.RegisterHandler(LF_FMIS_NAME, &lf_fmis_http_dispatch_cb::fmis_http_handler_callback);
	http_svr.Init(config.port);
	http_svr.Start();
	while (http_svr.IsRunning()) {
		usleep(1);
	}
	return 0;
}