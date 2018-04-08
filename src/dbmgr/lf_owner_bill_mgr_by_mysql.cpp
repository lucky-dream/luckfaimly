#include"dbmgr/lf_owner_bill_mgr_by_mysql.h"
#include"util/lf_error_code.h"
namespace LF
{
	static lf_string get_bill_table_name_by_uid(const lf_string& uid)
	{
		return lf_string("obill_").append(uid);
	}
	static Uint32 create_owner_bill_table(lf_db_object * db, const lf_string& table_name)
	{
		//create table if not exists obill3 like owner_bill_eg;
	}
	Uint32 lf_owner_bill_mgr::add_recode(lf_db_object * db, lf_owner_bill_meta meta)
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
		char sql[2048] = "insert into ";
		
		return 0;
	}
	Uint32 lf_owner_bill_mgr::del_recode(lf_db_object * db, const lf_string & bill_id)
	{
		return Uint32();
	}
	bool lf_owner_bill_mgr::has_recode(lf_db_object * db, const lf_string & bill_id)
	{
		return false;
	}
	Uint32 lf_owner_bill_mgr::find_recode(lf_db_object * db, const lf_string & bill_id, lf_owner_bill_meta & meta)
	{
		return Uint32();
	}
	Uint32 lf_owner_bill_mgr::find_recode(lf_db_object * db, const lf_owner_bill_query_options & filter_options, OwenrBillList & out_list)
	{
		return Uint32();
	}
}