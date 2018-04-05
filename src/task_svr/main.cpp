#include"util/lf_base_def.h"
#include"net/lf_http_server.h"
#include"task_svr/lf_tasksvr_config.h"
#include"task_svr/lf_task_http_dispatch_cb.h"



#define TASK_THREAD_NUM 4

using namespace LF;
int main(int argc, char* argv[])
{
	lf_string path("./lf_service.conf");
	//todo:@str get path
	if (!lf_tasksvr_config_mgr::singleton().read_config_file(path))
	{
		return 1;
	}
	lf_tasksvr_config_info config = lf_tasksvr_config_mgr::singleton().get_tasksvr_info();
	if (config.ip.empty()||config.port.empty())
	{
		return 1;
	}
	lf_http_server http_svr(4);
	http_svr.RegisterDefaultHandler(&lf_task_http_dispatch_cb::default_http_handler_callback);
	http_svr.RegisterHandler(LF_TASKSVR_NAME, &lf_task_http_dispatch_cb::task_http_handler_callback);
	http_svr.Init(config.port);
	http_svr.Start();
	while (http_svr.IsRunning()) {
		usleep(1);
	}
	return 0;
}