#ifndef LF_DB_MGR_H
#define LF_DB_MGR_H
#include"util/lf_singleton.h"
#include"util/lf_lock.h"
#include"mysql.h"
#include<memory>
#include<queue>
namespace LF
{
	struct lf_db_info
	{
		lf_string _host;
		Uint32 _port;
		lf_string _user_name;
		lf_string _password;
		lf_string _dbname;
		//const char * unix_socket;
		//unsigned long clientflag;        //һ������£�unix_socket����Ϊ�գ� 
		                               //clientflag ��ΪCLIENT_MULTI_STATEMENTS ����֧��ͬʱ��ѯ������䣬���֮��ͨ���ֺŷָ�
	};

	class lf_db_object
	{
	public:
		lf_db_object(const lf_db_info& db_info);
		lf_db_object(MYSQL* mysql);
		bool close();
		MYSQL* mysql() {
			return _mysql;
		}
		
	private:
		bool connect(const lf_db_info& db_info);
		MYSQL* _mysql;
	};

	class lf_db_mgr :public lf_singleton<lf_db_mgr>
	{
	public:
		bool enqueue(lf_db_object* db);
		lf_db_object* dequeue();
		void clear();
	private:
		typedef std::queue<lf_db_object*> DbConnQue;
		DbConnQue _db_conns;
		lf_lock _mutex;
	};

	class lf_db_module
	{
	public:
		static bool init(const lf_db_info& db_info);
		static lf_db_object* get_conn();
		static bool give_back(lf_db_object* db);
		static bool destroy(); //ģ������
	};

}
#endif // !LF_DB_MGR_H

