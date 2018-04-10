#include "dbmgr/lf_db_transaction_by_mysql.h"
#include"util/lf_error_code.h"
#include "mysql.h"
namespace LF
{
	uint32_t lf_db_transaction::start_transaction(lf_db_object* db)
	{
		if (db==nullptr)
		{
			return LF_ERROR_CODE::LF_SYSTEM_DB_CONNECT_ERROR;
		}
		MYSQL* m_mysql = db->mysql();
		if (m_mysql == nullptr)
		{
			return LF_ERROR_CODE::LF_SYSTEM_DB_ERROR;
		}
		int32_t ret;
		unsigned long *row_len;
		MYSQL_RES* res;
		MYSQL_ROW row;
		char sql[32] = "start transaction";
		//strcat(sql, id.c_str());
		int len = strlen(sql);
		// 执行查询
		ret = mysql_real_query(m_mysql, sql, len);
		if (ret != 0) {
			//US_WARN("mysql_real_query failed:\nError %u (%s)\n",
			//	mysql_errno(mysql), mysql_error(mysql));
			//todo:@str set log
			return LF_ERROR_CODE::LF_SYSTEM_DB_ERROR;
		}
		return 0;
	}

	uint32_t lf_db_transaction::rollback(lf_db_object* db)
	{
		if (db==nullptr)
		{
			return LF_ERROR_CODE::LF_SYSTEM_DB_CONNECT_ERROR;
		}
		MYSQL* m_mysql = db->mysql();
		if (m_mysql == nullptr)
		{
			return LF_ERROR_CODE::LF_SYSTEM_DB_ERROR;
		}
		int32_t ret;
		unsigned long *row_len;
		MYSQL_RES* res;
		MYSQL_ROW row;
		char sql[32] = "rollback";
		//strcat(sql, id.c_str());
		int len = strlen(sql);
		// 执行查询
		ret = mysql_real_query(m_mysql, sql, len);
		if (ret != 0) {
			//US_WARN("mysql_real_query failed:\nError %u (%s)\n",
			//	mysql_errno(mysql), mysql_error(mysql));
			//todo:@str set log
			return LF_ERROR_CODE::LF_SYSTEM_DB_ERROR;
		}
		return 0;
	}

	uint32_t lf_db_transaction::commit(lf_db_object* db)
	{
		if (db == nullptr)
		{
			return LF_ERROR_CODE::LF_SYSTEM_DB_CONNECT_ERROR;
		}
		MYSQL* m_mysql = db->mysql();
		if (m_mysql == nullptr)
		{
			return LF_ERROR_CODE::LF_SYSTEM_DB_ERROR;
		}
		int32_t ret;
		unsigned long *row_len;
		MYSQL_RES* res;
		MYSQL_ROW row;
		char sql[32] = "commit";
		//strcat(sql, id.c_str());
		int len = strlen(sql);
		// 执行查询
		ret = mysql_real_query(m_mysql, sql, len);
		if (ret != 0) {
			//US_WARN("mysql_real_query failed:\nError %u (%s)\n",
			//	mysql_errno(mysql), mysql_error(mysql));
			//todo:@str set log
			return LF_ERROR_CODE::LF_SYSTEM_DB_ERROR;
		}
		return 0;
	}
}

