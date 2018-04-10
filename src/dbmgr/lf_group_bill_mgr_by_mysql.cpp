#include"dbmgr/lf_group_bill_mgr_by_mysql.h"
#include"util/lf_error_code.h"
#include"util/uuid4.h"
namespace LF
{
	static lf_string get_bill_table_name_by_gid(const lf_string& gid)
	{
		return lf_string("gbill_").append(gid);
	}
	static uint32_t create_group_bill_table(lf_db_object * db, const lf_string& table_name)
	{
		//create table if not exists gbill3 like group_bill_eg;
		if (db == nullptr)
		{
			return LF_ERROR_CODE::LF_SYSTEM_DB_CONNECT_ERROR;
		}
		MYSQL* m_mysql = db->mysql();
		if (m_mysql == nullptr)
		{
			return LF_ERROR_CODE::LF_SYSTEM_DB_ERROR;
		}
		char sql[128] = "create table if not exists ";
		strcat(sql, table_name.c_str());
		strcat(sql, " like group_bill_eg");
		int len = strlen(sql);
		// 执行sql语句
		mysql_real_query(m_mysql, sql, len);
		return true;
	}
	uint32_t lf_group_bill_mgr::add_recode(lf_db_object * db, lf_group_bill_meta meta)
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
		meta._group_bill_id = lf_uuid_generator::uuid_generate();
		if (meta._group_bill_id.empty())
		{
			return LF_ERROR_CODE::LF_SYSTEM_DB_ERROR;
		}
		int32_t ret;
		lf_string table_name = get_bill_table_name_by_gid(meta._group_id);
		ret = create_group_bill_table(db, table_name);
		if (ret != 0)
		{
			return ret;
		}
		char sql[2048] = "insert into ";
		strcat(sql, table_name.c_str());
		strcat(sql, "(id,gid,owner,status,btype,ptype,cdate,sum,sign) values('");
		int len = strlen(sql);
		char* pbuf = (char*)sql + len;
		//------- id -------//
		ret = mysql_real_escape_string(m_mysql, pbuf,
			(const char*)(meta._group_bill_id.data()), meta._group_bill_id.size());
		pbuf[ret] = '\'';
		pbuf[++ret] = ',';
		pbuf[++ret] = '\'';
		pbuf = pbuf + ret + 1;
		//------- gid ------//
		ret = mysql_real_escape_string(m_mysql, pbuf,
			meta._group_id.data(), meta._group_id.size());
		pbuf[ret] = '\'';
		pbuf[++ret] = ',';
		pbuf[++ret] = '\'';
		pbuf = pbuf + ret + 1;
		//------- owner ------//
		ret = mysql_real_escape_string(m_mysql, pbuf,
			meta._owner_id.data(), meta._owner_id.size());
		pbuf[ret] = '\'';
		pbuf[++ret] = ',';
		pbuf[++ret] = '\'';
		pbuf = pbuf + ret + 1;
		//------ status ------//
		ret = mysql_real_escape_string(m_mysql, pbuf,
			(const char*)(std::to_string(meta._status).data()),
			std::to_string(meta._status).size());
		pbuf[ret] = '\'';
		pbuf[++ret] = ',';
		pbuf[++ret] = '\'';
		pbuf = pbuf + ret + 1;
		//------ btype ------//
		ret = mysql_real_escape_string(m_mysql, pbuf,
			(const char*)(std::to_string(meta._group_bill_type).data()),
			std::to_string(meta._group_bill_type).size());
		pbuf[ret] = '\'';
		pbuf[++ret] = ',';
		pbuf[++ret] = '\'';
		pbuf = pbuf + ret + 1;
		//------ ptype ---------//
		ret = mysql_real_escape_string(m_mysql, pbuf,
			(const char*)(std::to_string(meta._ptype).data()),
			std::to_string(meta._ptype).size());
		pbuf[ret] = '\'';
		pbuf[++ret] = ',';
		pbuf[++ret] = '\'';
		pbuf = pbuf + ret + 1;
		//------ cdate ---------//
		ret = mysql_real_escape_string(m_mysql, pbuf,
			(const char*)(std::to_string(meta._create_date).data()),
			std::to_string(meta._create_date).size());
		pbuf[ret] = '\'';
		pbuf[++ret] = ',';
		pbuf[++ret] = '\'';
		pbuf = pbuf + ret + 1;
		//------ sum ---------//
		ret = mysql_real_escape_string(m_mysql, pbuf,
			(const char*)(std::to_string(meta._sum).data()),
			std::to_string(meta._sum).size());
		pbuf[ret] = '\'';
		pbuf[++ret] = ',';
		pbuf[++ret] = '\'';
		pbuf = pbuf + ret + 1;
		//------ sign ---------//
		ret = mysql_real_escape_string(m_mysql, pbuf,
			(const char*)(meta._sign.data()), meta._sign.size());
		pbuf[ret] = '\'';
		pbuf[++ret] = ')';

		// 执行sql语句
		ret = mysql_real_query(m_mysql, sql, (pbuf + ret + 1) - sql);
		if (ret != 0) {
			//US_WARN("mysql_real_query failed:\nError %u (%s)\n",
			//	mysql_errno(mysql), mysql_error(mysql));
			//todo:@str set log
			printf("err:%s\n", mysql_error(m_mysql));
			return LF_ERROR_CODE::LF_SYSTEM_DB_ERROR;
		}
		return 0;
	}
	uint32_t lf_group_bill_mgr::del_recode(const lf_string& gid, lf_db_object * db, const lf_string & bill_id)
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
		lf_string table_name = get_bill_table_name_by_gid(gid);
		//ret = create_group_bill_table(db, table_name);
		//if (ret != 0)
		//{
		//	return ret;
		//}
		char sql[2048] = "delete from ";
		strcat(sql, table_name.c_str());
		strcat(sql, " where id='");
		int len = strlen(sql);
		char* pbuf = (char*)sql + len;
		//------- id -------//
		ret = mysql_real_escape_string(m_mysql, pbuf,
			(const char*)(bill_id.data()), bill_id.size());
		pbuf[ret] = '\'';
		// 执行sql语句
		ret = mysql_real_query(m_mysql, sql, (pbuf + ret + 1) - sql);
		if (ret != 0) {
			//US_WARN("mysql_real_query failed:\nError %u (%s)\n",
			//	mysql_errno(mysql), mysql_error(mysql));
			//todo:@str set log
			printf("err:%s\n", mysql_error(m_mysql));
			return LF_ERROR_CODE::LF_SYSTEM_DB_ERROR;
		}
		return 0;
	}
	bool lf_group_bill_mgr::has_recode(const lf_string& gid, lf_db_object * db, const lf_string & bill_id)
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
		lf_string table_name = get_bill_table_name_by_gid(gid);
		//ret = create_group_bill_table(db, table_name);
		//if (ret != 0)
		//{
		//	return ret;
		//}
		char sql[2048] = "select count(*) from ";
		strcat(sql, table_name.c_str());
		strcat(sql, " where id='");
		int len = strlen(sql);
		char* pbuf = (char*)sql + len;
		//------- id -------//
		ret = mysql_real_escape_string(m_mysql, pbuf,
			(const char*)(bill_id.data()), bill_id.size());
		pbuf[ret] = '\'';
		// 执行sql语句
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
		// 获取返回结果
		res = mysql_store_result(m_mysql);
		if (res == NULL) {
			return LF_ERROR_CODE::LF_SYSTEM_DB_NOT_FOUND;
		}
		uint32_t count = 0;
		if ((row = mysql_fetch_row(res)) != NULL &&
			(row_len = mysql_fetch_lengths(res)) != NULL)
		{
			count = std::stol(row[0]);
		}
		mysql_free_result(res);
		return (count == 1);
	}
	static uint32_t gbill_db_to_meta(MYSQL_ROW row, unsigned long *row_len, lf_group_bill_meta & meta)
	{
		if (row == nullptr || row_len == nullptr || *row == nullptr)
		{
			return LF_ERROR_CODE::LF_SYSTEM_DB_NOT_FOUND;
		}
		//if (row_len[0] <= 0 || row_len[1] <= 0 || row_len[2] <= 0 || row_len[3] <= 0)
		//{
		//	return LF_ERROR_CODE::LF_SYSTEM_DB_NOT_FOUND;
		//}
		//------ id ------//
		meta._group_bill_id.assign(row[0], row_len[0]);
		//------ gid ------//
		meta._group_id.assign(row[1], row_len[1]);
		//------ owner ------//
		meta._owner_id.assign(row[2], row_len[2]);
		//------ status -----//
		meta._status = std::stoi(row[3]);
		//------ btype -------//
		meta._group_bill_type = std::stoi(row[4]);
		//------ ptype -------//
		meta._ptype = std::stoi(row[5]);
		//------ cdate -------//
		meta._create_date = std::stoll(row[6]);
		//------ sum -------//
		meta._sum = std::stoll(row[7]);
		//------ sign -------//
		meta._sign.assign(row[8], row_len[8]);
		return 0;
	}
	uint32_t lf_group_bill_mgr::find_recode(const lf_string& gid, lf_db_object * db, const lf_string & bill_id, lf_group_bill_meta & meta)
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
		lf_string table_name = get_bill_table_name_by_gid(gid);
		//ret = create_owner_bill_table(db, table_name);
		//if (ret != 0)
		//{
		//	return ret;
		//}
		char sql[2048] = "select * from ";
		strcat(sql, table_name.c_str());
		strcat(sql, " where id='");
		int len = strlen(sql);
		char* pbuf = (char*)sql + len;
		//------- id -------//
		ret = mysql_real_escape_string(m_mysql, pbuf,
			(const char*)(bill_id.data()), bill_id.size());
		pbuf[ret] = '\'';
		// 执行sql语句
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
		// 获取返回结果
		res = mysql_store_result(m_mysql);
		if (res == NULL) {
			return LF_ERROR_CODE::LF_SYSTEM_DB_NOT_FOUND;
		}
		if ((row = mysql_fetch_row(res)) != NULL &&
			(row_len = mysql_fetch_lengths(res)) != NULL)
		{
			ret = gbill_db_to_meta(row, row_len, meta);
			mysql_free_result(res);
			return ret;
		}
		mysql_free_result(res);
		return 0;
	}
	uint32_t lf_group_bill_mgr::find_recode(const lf_string& gid, lf_db_object * db, const lf_group_bill_query_options & filter_options, GroupBillList & out_list)
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
		lf_string table_name = get_bill_table_name_by_gid(gid);
		//ret = create_owner_bill_table(db, table_name);
		//if (ret != 0)
		//{
		//	return ret;
		//}
		char sql[2048] = "select * from ";
		strcat(sql, table_name.c_str());
		strcat(sql, " where id='");
		int len = strlen(sql);
		char* pbuf = (char*)sql + len;
		//------- id -------//
		if (!filter_options._gbid.empty())
		{
			ret = mysql_real_escape_string(m_mysql, pbuf,
				(const char*)(filter_options._gbid.data()), filter_options._gbid.size());
			pbuf[ret] = '\'';
		}
		//------- uid -------//
		if (!filter_options._uid.empty())
		{
			strcat(sql, " and owner&");
			len = strlen(sql);
			pbuf = (char*)sql + len;
			ret = mysql_real_escape_string(m_mysql, pbuf,
				(const char*)(filter_options._uid.data()),
				filter_options._uid.size());
		}
		//------- status -------//
		if (GBILL_STATUS_ALL_MASK != filter_options._status)
		{
			strcat(sql, " and status&");
			len = strlen(sql);
			pbuf = (char*)sql + len;
			ret = mysql_real_escape_string(m_mysql, pbuf,
				(const char*)(std::to_string(filter_options._status).data()),
				std::to_string(filter_options._status).size());
		}
		//------- btype -------//
		if (MAX_MASK_DEFAULT_32 != filter_options._btype)
		{
			strcat(sql, " and btype&");
			len = strlen(sql);
			pbuf = (char*)sql + len;
			ret = mysql_real_escape_string(m_mysql, pbuf,
				(const char*)(std::to_string(filter_options._btype).data()),
				std::to_string(filter_options._btype).size());
		}
		//------- ptype -------//
		if (MAX_MASK_DEFAULT_32 != filter_options._ptype)
		{
			//((ptype&1)=($filter_options._ptype&1))*((ptype>>1)&($filter_options._ptype>>1))
			len = strlen(sql);
			sprintf(sql + len, " and ((ptype&1)=(%d&1))*((ptype>>1)&(%d>>1))", filter_options._ptype, filter_options._ptype);
			len = strlen(sql);
			pbuf = (char*)sql + len;
			ret = mysql_real_escape_string(m_mysql, pbuf,
				(const char*)(std::to_string(filter_options._ptype).data()),
				std::to_string(filter_options._ptype).size());
		}
		//------- sdate -------//
		if (0 != filter_options._sdate)
		{
			strcat(sql, " and cdate>=");
			len = strlen(sql);
			pbuf = (char*)sql + len;
			ret = mysql_real_escape_string(m_mysql, pbuf,
				(const char*)(std::to_string(filter_options._sdate).data()),
				std::to_string(filter_options._sdate).size());
		}
		//------- edate -------//
		if (MAX_NUM_64 != filter_options._edate)
		{
			strcat(sql, " and cdate<=");
			len = strlen(sql);
			pbuf = (char*)sql + len;
			ret = mysql_real_escape_string(m_mysql, pbuf,
				(const char*)(std::to_string(filter_options._edate).data()),
				std::to_string(filter_options._edate).size());
		}
		//------- summin -------//
		if (0 != filter_options._summin)
		{
			strcat(sql, " and sum>=");
			len = strlen(sql);
			pbuf = (char*)sql + len;
			ret = mysql_real_escape_string(m_mysql, pbuf,
				(const char*)(std::to_string(filter_options._summin).data()),
				std::to_string(filter_options._summin).size());
		}
		//------- summax -------//
		if (MAX_NUM_64 != filter_options._summax)
		{
			strcat(sql, " and sum<=");
			len = strlen(sql);
			pbuf = (char*)sql + len;
			ret = mysql_real_escape_string(m_mysql, pbuf,
				(const char*)(std::to_string(filter_options._summax).data()),
				std::to_string(filter_options._summax).size());
		}
		//------- keyword -------//
		if (!filter_options._keyword.empty())
		{
			strcat(sql, " and sign regexp '");
			len = strlen(sql);
			pbuf = (char*)sql + len;
			std::string regexp;
			regexp.assign(".*").append(filter_options._keyword).append(".*");
			ret = mysql_real_escape_string(m_mysql, pbuf,
				(const char*)(regexp.data()), regexp.size());
		}
		//------- begin&count -------//
		uint32_t count = filter_options._count>MAX_RETURN_RECODE_COUNT ?
			MAX_RETURN_RECODE_COUNT : filter_options._count;
		len = strlen(sql);
		sprintf(sql + len, " limit %d,%d", filter_options._begin, count);
		len = strlen(sql);
		// 执行sql语句
		ret = mysql_real_query(m_mysql, sql, len);
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
		// 获取返回结果
		res = mysql_store_result(m_mysql);
		if (res == NULL) {
			return LF_ERROR_CODE::LF_SYSTEM_DB_NOT_FOUND;
		}
		while ((row = mysql_fetch_row(res)) != NULL &&
			(row_len = mysql_fetch_lengths(res)) != NULL)
		{
			lf_group_bill_meta meta;
			ret = gbill_db_to_meta(row, row_len, meta);
			if (ret != 0)
			{
				break;
			}
			out_list.push_back(meta);
		}
		mysql_free_result(res);
		return 0;
	}
	uint32_t lf_group_bill_mgr::get_bill_status(const lf_string& gid, lf_db_object * db, const lf_string & bill_id, uint32_t & bill_status)
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
		lf_string table_name = get_bill_table_name_by_gid(gid);
		//ret = create_owner_bill_table(db, table_name);
		//if (ret != 0)
		//{
		//	return ret;
		//}
		char sql[2048] = "select status from ";
		strcat(sql, table_name.c_str());
		strcat(sql, " where id='");
		int len = strlen(sql);
		char* pbuf = (char*)sql + len;
		//------- id -------//
		ret = mysql_real_escape_string(m_mysql, pbuf,
			(const char*)(bill_id.data()), bill_id.size());
		pbuf[ret] = '\'';
		// 执行sql语句
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
		// 获取返回结果
		res = mysql_store_result(m_mysql);
		if (res == NULL) {
			return LF_ERROR_CODE::LF_SYSTEM_DB_NOT_FOUND;
		}
		if ((row = mysql_fetch_row(res)) != NULL &&
			(row_len = mysql_fetch_lengths(res)) != NULL)
		{
			bill_status = std::stol(row[0]);
			mysql_free_result(res);
			return 0;
		}
		mysql_free_result(res);
		return LF_ERROR_CODE::LF_SYSTEM_DB_NOT_FOUND;
	}
	uint32_t lf_group_bill_mgr::update_bill_status(const lf_string& gid, lf_db_object * db, const lf_string & bill_id, const uint32_t & bill_status)
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
		lf_string table_name = get_bill_table_name_by_gid(gid);
		//ret = create_owner_bill_table(db, table_name);
		//if (ret != 0)
		//{
		//	return ret;
		//}
		char sql[2048] = "update ";
		strcat(sql, table_name.c_str());
		strcat(sql, " set status=");
		int len = strlen(sql);
		char* pbuf = (char*)sql + len;
		//------- status -------//
		ret = mysql_real_escape_string(m_mysql, pbuf,
			(const char*)(std::to_string(bill_status).data()), std::to_string(bill_status).size());
		strcat(sql, " where id=");
		//------- id -------//
		len = strlen(sql);
		pbuf = (char*)sql + len;
		ret = mysql_real_escape_string(m_mysql, pbuf,
			(const char*)(bill_id.data()), bill_id.size());
		pbuf[ret] = '\'';
		// 执行sql语句
		ret = mysql_real_query(m_mysql, sql, (pbuf + ret + 1) - sql);
		if (ret != 0) {
			//US_WARN("mysql_real_query failed:\nError %u (%s)\n",
			//	mysql_errno(mysql), mysql_error(mysql));
			//todo:@str set log
			printf("err:%s\n", mysql_error(m_mysql));
			return LF_ERROR_CODE::LF_SYSTEM_DB_ERROR;
		}
		return 0;
	}
}