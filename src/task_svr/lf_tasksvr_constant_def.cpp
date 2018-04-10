#include"task_svr/lf_tasksvr_constant_def.h"
namespace LF
{
	OBJ_SINGLETON_INIT(lf_task_cmd_map);
	lf_task_cmd_map g_lf_task_cmd_map;
	lf_task_cmd_map::lf_task_cmd_map()
	{
#define XX(cmd,op) cmds.insert(std::make_pair(op,cmd));
		TASK_ENUM_CMD_TYPE(XX)
#undef  XX
	}
	uint32_t lf_task_cmd_map::get_cmd(const lf_string & op)
	{
		auto it = cmds.find(op);
		if (it==cmds.end())
		{
			return lf_task_cmd_type::LF_TASK_CMD_UNKNOW;
		}
		return it->second;
	}
}
