#include"dbmgr/lf_group_bill_mgr_by_mysql.h"
namespace LF
{
	static lf_string get_bill_table_name_by_gid(const lf_string& gid)
	{
		return lf_string("gbill_").append(gid);
	}
	static Uint32 create_group_bill_table(lf_db_object * db, const lf_string& table_name)
	{
		//create table if not exists obill3 like owner_bill_eg;
	}
	Uint32 lf_group_bill_mgr::add_recode(lf_db_object * db, lf_group_bill_meta meta)
	{
		return Uint32();
	}
	Uint32 lf_group_bill_mgr::del_recode(lf_db_object * db, const lf_string & bill_id)
	{
		return Uint32();
	}
	bool lf_group_bill_mgr::has_recode(lf_db_object * db, const lf_string & bill_id)
	{
		return false;
	}
	Uint32 lf_group_bill_mgr::find_recode(lf_db_object * db, const lf_string & bill_id, lf_group_bill_meta & meta)
	{
		return Uint32();
	}
	Uint32 lf_group_bill_mgr::find_recode(lf_db_object * db, const lf_group_bill_query_options & filter_options, GroupBillList & out_list)
	{
		return Uint32();
	}
	Uint32 lf_group_bill_mgr::get_bill_status(lf_db_object * db, const lf_string & bill_id, Uint32 & bill_status)
	{
		return Uint32();
	}
	Uint32 lf_group_bill_mgr::update_bill_status(lf_db_object * db, const lf_string & bill_id, const Uint32 & bill_status)
	{
		return Uint32();
	}
}