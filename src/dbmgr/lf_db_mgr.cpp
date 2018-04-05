#include"dbmgr/lf_db_mgr.h"

#define  bulidCount    10    //�������ݿ���������
namespace LF
{
	lf_db_object::lf_db_object(const lf_db_info & db_info)
	{
		connect(db_info);
	}
	lf_db_object::lf_db_object(MYSQL * mysql)
	{
		if (mysql)
		{
			_mysql = mysql;
		}
		else
		{
			_mysql = NULL;
		}
	}
	bool lf_db_object::close()
	{
		mysql_close(_mysql);
		if(_mysql)
		    return false;
	}
	bool lf_db_object::connect(const lf_db_info & db_info)
	{
		MYSQL* mysql;
		mysql_init(mysql);
		mysql = mysql_real_connect(mysql, db_info._host.c_str(), db_info._user_name.c_str(), db_info._password.c_str(),
			db_info._dbname.c_str(), db_info._port, NULL, CLIENT_MULTI_STATEMENTS);
		if (mysql != NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	OBJ_SINGLETON_INIT(lf_db_mgr);
	lf_db_mgr g_lf_db_mgr;
	bool lf_db_mgr::enqueue(lf_db_object* db)
	{
		lf_lock::scoped_lock scoped_mutex(_mutex);
		if (db != NULL)
		{
			_db_conns.push(*db);
		}
		else
		{
			return false;
		}
	}

	lf_db_object * lf_db_mgr::dequeue()
	{
		lf_lock::scoped_lock scoped_mutex(_mutex);
		lf_db_object m_db = _db_conns.front();
		if (m_db.mysql)
		{
			_db_conns.pop(); // ��ȡ��Ԫ�غ󣬳���
			return m_db.mysql;
		}
		else
		{
			//����ͷ����Ԫ��
			return NULL;
		}
	}

	void lf_db_mgr::clear()
	{
		//�ڵ��øú���ʱ����ָ��Żض�����
		
	}

	bool lf_db_module::init(const lf_db_info & db_info)
	{
		if (db_info._host.empty() || db_info._dbname.empty()
			|| db_info._user_name.empty())
		{
			return false;
		}
		for (int i = 0; i < bulidCount; ++i)
		{
			lf_db_object*  m_plf_db_object = new lf_db_object(db_info);
			lf_db_mgr::singleton().enqueue(m_plf_db_object);
		}
		
		return false;
	}
	lf_db_object * lf_db_module::get_conn()
	{
		if (lf_db_mgr::singleton().dequeue())
		{
			return lf_db_mgr::singleton().dequeue();
		}
		else {
			//�����ڶ���û��Ԫ��ʱ���ȴ�����
			return NULL;
		}
		   
	}
	bool lf_db_module::give_back(lf_db_object * db)
	{
		//����
		if(!lf_db_mgr::singleton().enqueue(db))
		    return false;
	}
	bool lf_db_module::destroy()
	{
		lf_db_mgr::singleton().clear();
		return false;
	}
	
	//MYSQL* lf_db_mgr::openDB()  //�ⲿ����
	//{
	//	//�����������������ݿ�ʱ������һ��mysqlָ��
	//	//�������е�����
	//	if (_db_conns.empty())//������Ϊ��ʱ
	//	{
	//		return NULL;
	//	}
	//	else
	//	{
	//		//����������ָ��ʱ
	//		//MYSQL* mysql = _db_conns.front;
	//		//return mysql;
	//	}
	//}
}