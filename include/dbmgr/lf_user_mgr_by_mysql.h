#ifndef LF_USER_MGR_BY_MYSQL_H
#define LF_USER_MGR_BY_MYSQL_H
#include "util/lf_base_def.h"
#include"dbmgr/lf_db_mgr.h"
namespace LF
{
	class lf_user_mgr
	{
	public:
		static uint32_t find_name(const lf_string& uid, lf_db_object* db, lf_string& uname);
		static uint32_t find_id(const lf_string& uname, lf_db_object* db, lf_string& uid);
	};
	class lf_group_mgr
	{
	public:
		static uint32_t find_name(const lf_string& gid, lf_db_object* db, lf_string& gname);
		static uint32_t find_id(const lf_string& gname, lf_db_object* db, lf_string& gid);
	};
}
#endif // !LF_USER_MGR_BY_MYSQL_H

