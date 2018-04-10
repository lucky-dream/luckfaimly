#ifndef LF_FMIS_AONSTANT_DEF_H
#define LF_FMIS_AONSTANT_DEF_H
#include"util/lf_base_def.h"
#include"util/lf_singleton.h"
#include<map>
namespace LF
{
#define TASK_ENUM_CMD_TYPE(XX)  \
	/*	命令枚举值				 命令op			 描述*/  \
	XX(LF_FMIS_CMD_OBQ,			"obq",			 "查询个人帐单") \
	XX(LF_FMIS_CMD_OBA,			"oba",			 "添加个人帐单") \
	XX(LF_FMIS_CMD_OBD,			"obd",			 "删除个人账单") \
	XX(LF_FMIS_CMD_OBG,			"obg",			 "同步个人账单到组")  \
	XX(LF_FMIS_CMD_GBQ,			"gbq",			 "查询组账单")	\
	XX(LF_FMIS_CMD_GBC,			"gbc",			 "计算组账单")  \
	XX(LF_FMIS_CMD_GBD,			"gbd",			 "删除组账单")

	enum lf_task_cmd_type
	{
		LF_TASK_CMD_UNKNOW,
#define XX(cmd,op) cmd,
		TASK_ENUM_CMD_TYPE(XX)
#undef  XX
	};
	class lf_fmis_cmd_map :public lf_singleton<lf_fmis_cmd_map>
	{
	public:
		lf_fmis_cmd_map();
		uint32_t get_cmd(const lf_string& op);
	private:
		typedef std::map<lf_string, uint32_t> CmdMap;
		CmdMap cmds;
	};
}
#endif // !LF_FMIS_AONSTANT_DEF_H

