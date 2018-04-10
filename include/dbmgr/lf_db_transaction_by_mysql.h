#ifndef LF_DB_TRANSACTION_BY_MYSQL
#define LF_DB_TRANSACTION_BY_MYSQL
#include"util/lf_base_def.h"
#include"dbmgr/lf_db_mgr.h"
namespace LF
{
	class lf_db_transaction
	{
	public:
		virtual uint32_t start_transaction(lf_db_object* db);
		
		virtual uint32_t rollback(lf_db_object* db);
		
		virtual uint32_t commit(lf_db_object* db);
	private:
	};

}
#endif // !LF_DB_TRANSACTION_BY_MYSQL

