#ifndef LF_TASKSVR_AONSTANT_DEF_H
#define LF_TASKSVR_AONSTANT_DEF_H
#include"util/lf_base_def.h"
#include"util/lf_singleton.h"
#include<map>
namespace LF
{
#define TASK_ENUM_CMD_TYPE(XX)  \
	/*	ÃüÁîÃ¶¾ÙÖµ				 ÃüÁîop			 ÃèÊö*/  \
	XX(LF_TASK_CMD_LOGIN,		"login",		 "µÇÂ½") \
	XX(LF_TASK_CMD_LOGOUT,		"logout",		 "ÍË³ö") \
	XX(LF_TASK_CMD_REGISTER,	"register",		 "×¢²á") \
	XX(LF_TASK_CMD_CONFIRM,		"confirm",		 "×¢²áÈ·ÈÏ") 

	enum lf_task_cmd_type
	{
		LF_TASK_CMD_UNKNOW,
#define XX(cmd,op) cmd,
		TASK_ENUM_CMD_TYPE(XX)
#undef  XX
	};
	class lf_task_cmd_map :public lf_singleton<lf_task_cmd_map>
	{
	public:
		lf_task_cmd_map();
		Uint32 get_cmd(const lf_string& op);
	private:
		typedef std::map<lf_string, Uint32> CmdMap;
		CmdMap cmds;
	};
}
#endif // !LF_TASKSVR_AONSTANT_DEF_H

