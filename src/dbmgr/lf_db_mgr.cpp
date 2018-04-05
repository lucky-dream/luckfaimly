#include"dbmgr/lf_db_mgr.h"
namespace LF
{
	lf_db_object::lf_db_object(const lf_db_info & db_info)
	{
	}
	lf_db_object::lf_db_object(MYSQL * _mysql)
	{
	}
	bool lf_db_object::close()
	{
		return false;
	}
	bool lf_db_object::connect(const lf_db_info & db_info)
	{
		return false;
	}

	OBJ_SINGLETON_INIT(lf_db_mgr);
	lf_db_mgr g_lf_db_mgr;
	bool lf_db_mgr::enqueue(lf_db_object * db)
	{
		return false;
	}
	lf_db_object * lf_db_mgr::dequeue()
	{
		return nullptr;
	}
	void lf_db_mgr::clear()
	{
	}

	bool lf_db_module::init(const lf_db_info & db_info)
	{
		return false;
	}
	lf_db_object * lf_db_module::get_conn()
	{
		return nullptr;
	}
	bool lf_db_module::give_back(lf_db_object * db)
	{
		return false;
	}
	bool lf_db_module::destroy()
	{
		return false;
	}
}