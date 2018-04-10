#include"dbmgr/lf_user_mgr_by_mysql.h"
#include"util/lf_error_code.h"
namespace LF
{
	uint32_t lf_user_mgr::find_name(const lf_string & uid, lf_db_object * db, lf_string & uname)
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
		char sql[2048] = "select name from user where id='";
		int len = strlen(sql);
		char* pbuf = (char*)sql + len;
		//------- id -------//
		ret = mysql_real_escape_string(m_mysql, pbuf,
			(const char*)(uid.data()), uid.size());
		pbuf[ret] = '\'';
		// ִ��sql���
		ret = mysql_real_query(m_mysql, sql, (pbuf + ret + 1) - sql);
		if (ret != 0) {
			//US_WARN("mysql_real_query failed:\nError %u (%s)\n",
			//	mysql_errno(mysql), mysql_error(mysql));
			//todo:@str set log
			printf("err:%s\n", mysql_error(m_mysql));
			return LF_ERROR_CODE::LF_SYSTEM_DB_ERROR;
		}
		MYSQL_RES* res;
		MYSQL_ROW row;
		unsigned long *row_len;
		// ��ȡ���ؽ��
		res = mysql_store_result(m_mysql);
		if (res == NULL) {
			return LF_ERROR_CODE::LF_SYSTEM_DB_NOT_FOUND;
		}
		if ((row = mysql_fetch_row(res)) != NULL &&
			(row_len = mysql_fetch_lengths(res)) != NULL)
		{
			uname.assign(row[0], row_len[0]);
			mysql_free_result(res);
			return 0;
		}
		mysql_free_result(res);
		return LF_ERROR_CODE::LF_SYSTEM_DB_NOT_FOUND;
	}
	uint32_t lf_user_mgr::find_id(const lf_string & uname, lf_db_object * db, lf_string & uid)
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
		char sql[2048] = "select id from user where name='";
		int len = strlen(sql);
		char* pbuf = (char*)sql + len;
		//------- name -------//
		ret = mysql_real_escape_string(m_mysql, pbuf,
			(const char*)(uname.data()), uname.size());
		pbuf[ret] = '\'';
		// ִ��sql���
		ret = mysql_real_query(m_mysql, sql, (pbuf + ret + 1) - sql);
		if (ret != 0) {
			//US_WARN("mysql_real_query failed:\nError %u (%s)\n",
			//	mysql_errno(mysql), mysql_error(mysql));
			//todo:@str set log
			printf("err:%s\n", mysql_error(m_mysql));
			return LF_ERROR_CODE::LF_SYSTEM_DB_ERROR;
		}
		MYSQL_RES* res;
		MYSQL_ROW row;
		unsigned long *row_len;
		// ��ȡ���ؽ��
		res = mysql_store_result(m_mysql);
		if (res == NULL) {
			return LF_ERROR_CODE::LF_SYSTEM_DB_NOT_FOUND;
		}
		if ((row = mysql_fetch_row(res)) != NULL &&
			(row_len = mysql_fetch_lengths(res)) != NULL)
		{
			uid.assign(row[0], row_len[0]);
			mysql_free_result(res);
			return 0;
		}
		mysql_free_result(res);
		return LF_ERROR_CODE::LF_SYSTEM_DB_NOT_FOUND;
	}
	uint32_t lf_group_mgr::find_name(const lf_string & gid, lf_db_object * db, lf_string & gname)
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
		char sql[2048] = "select groupname from groups where groupid='";
		int len = strlen(sql);
		char* pbuf = (char*)sql + len;
		//------- id -------//
		ret = mysql_real_escape_string(m_mysql, pbuf,
			(const char*)(gid.data()), gid.size());
		pbuf[ret] = '\'';
		// ִ��sql���
		ret = mysql_real_query(m_mysql, sql, (pbuf + ret + 1) - sql);
		if (ret != 0) {
			//US_WARN("mysql_real_query failed:\nError %u (%s)\n",
			//	mysql_errno(mysql), mysql_error(mysql));
			//todo:@str set log
			printf("err:%s\n", mysql_error(m_mysql));
			return LF_ERROR_CODE::LF_SYSTEM_DB_ERROR;
		}
		MYSQL_RES* res;
		MYSQL_ROW row;
		unsigned long *row_len;
		// ��ȡ���ؽ��
		res = mysql_store_result(m_mysql);
		if (res == NULL) {
			return LF_ERROR_CODE::LF_SYSTEM_DB_NOT_FOUND;
		}
		if ((row = mysql_fetch_row(res)) != NULL &&
			(row_len = mysql_fetch_lengths(res)) != NULL)
		{
			gname.assign(row[0], row_len[0]);
			mysql_free_result(res);
			return 0;
		}
		mysql_free_result(res);
		return LF_ERROR_CODE::LF_SYSTEM_DB_NOT_FOUND;
	}
	uint32_t lf_group_mgr::find_id(const lf_string & gname, lf_db_object * db, lf_string & gid)
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
		char sql[2048] = "select groupid from groups where groupname='";
		int len = strlen(sql);
		char* pbuf = (char*)sql + len;
		//------- name -------//
		ret = mysql_real_escape_string(m_mysql, pbuf,
			(const char*)(gname.data()), gname.size());
		pbuf[ret] = '\'';
		// ִ��sql���
		ret = mysql_real_query(m_mysql, sql, (pbuf + ret + 1) - sql);
		if (ret != 0) {
			//US_WARN("mysql_real_query failed:\nError %u (%s)\n",
			//	mysql_errno(mysql), mysql_error(mysql));
			//todo:@str set log
			printf("err:%s\n", mysql_error(m_mysql));
			return LF_ERROR_CODE::LF_SYSTEM_DB_ERROR;
		}
		MYSQL_RES* res;
		MYSQL_ROW row;
		unsigned long *row_len;
		// ��ȡ���ؽ��
		res = mysql_store_result(m_mysql);
		if (res == NULL) {
			return LF_ERROR_CODE::LF_SYSTEM_DB_NOT_FOUND;
		}
		if ((row = mysql_fetch_row(res)) != NULL &&
			(row_len = mysql_fetch_lengths(res)) != NULL)
		{
			gid.assign(row[0], row_len[0]);
			mysql_free_result(res);
			return 0;
		}
		mysql_free_result(res);
		return LF_ERROR_CODE::LF_SYSTEM_DB_NOT_FOUND;
	}
}