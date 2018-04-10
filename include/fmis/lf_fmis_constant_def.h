#ifndef LF_FMIS_AONSTANT_DEF_H
#define LF_FMIS_AONSTANT_DEF_H
#include"util/lf_base_def.h"
#include"util/lf_singleton.h"
#include<map>
namespace LF
{
#define TASK_ENUM_CMD_TYPE(XX)  \
	/*	����ö��ֵ				 ����op			 ����*/  \
	XX(LF_FMIS_CMD_OBQ,			"obq",			 "��ѯ�����ʵ�") \
	XX(LF_FMIS_CMD_OBA,			"oba",			 "��Ӹ����ʵ�") \
	XX(LF_FMIS_CMD_OBD,			"obd",			 "ɾ�������˵�") \
	XX(LF_FMIS_CMD_OBG,			"obg",			 "ͬ�������˵�����")  \
	XX(LF_FMIS_CMD_GBQ,			"gbq",			 "��ѯ���˵�")	\
	XX(LF_FMIS_CMD_GBC,			"gbc",			 "�������˵�")  \
	XX(LF_FMIS_CMD_GBD,			"gbd",			 "ɾ�����˵�")

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

