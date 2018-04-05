#include"task_svr/lf_task_service_handler.h"
#include"task_svr/lf_token_mgr.h"
#include"dbmgr/lf_db_mgr.h"
#include"rapidjson/writer.h"
#include"rapidjson/stringbuffer.h"
#include <ctime>
namespace LF
{
	static bool query_password(const lf_string & name,lf_string & password)
	{
		lf_db_object* db_obj = lf_db_module::get_conn();
		lf_string sql("select password from user where name='");
		sql.append(name).append("'");
		if (mysql_query(db_obj->mysql(), sql.c_str()))
		{
			return false;
		}
		MYSQL_RES * res = mysql_store_result(db_obj->mysql());
		if (!res)
		{
			return false;
		}
		if (mysql_num_rows(res) != 1)
		{
			return false;
		}
		MYSQL_ROW row = mysql_fetch_row(res);
		password = row[0];
		lf_db_module::give_back(db_obj);
		return true;
	}

	static bool query_uid(const lf_string & name, lf_string & uid)
	{
		lf_db_object* db_obj = lf_db_module::get_conn();
		lf_string sql("select uid from user where name='");
		sql.append(name).append("'");
		if (mysql_query(db_obj->mysql(), sql.c_str()))
		{
			return false;
		}
		MYSQL_RES * res = mysql_store_result(db_obj->mysql());
		if (!res)
		{
			return false;
		}
		if (mysql_num_rows(res) != 1)
		{
			return false;
		}
		MYSQL_ROW row = mysql_fetch_row(res);
		uid = row[0];
		lf_db_module::give_back(db_obj);
		return true;
	}

	static bool query_email(const lf_string & name, lf_string & email)
	{
		lf_db_object* db_obj = lf_db_module::get_conn();
		lf_string sql("select email from user where name='");
		sql.append(name).append("'");
		if (mysql_query(db_obj->mysql(), sql.c_str()))
		{
			return false;
		}
		MYSQL_RES * res = mysql_store_result(db_obj->mysql());
		if (!res)
		{
			return false;
		}
		if (mysql_num_rows(res) != 1)
		{
			return false;
		}
		MYSQL_ROW row = mysql_fetch_row(res);
		email = row[0];
		lf_db_module::give_back(db_obj);
		return true;
	}

	static void set_err(const Uint32 status, const lf_string err_info, lf_string& outjson)
	{
		rapidjson::StringBuffer s;
		rapidjson::Writer<rapidjson::StringBuffer> writer(s);
		writer.StartObject();
		writer.Key("status");
		writer.Uint(status);
		writer.Key("info");
		writer.String(err_info.c_str());
		writer.EndObject();
		outjson = s.GetString();
	}

	bool lf_task_service_handler::login(const lf_string & name, const lf_string & password, lf_string & out_json)
	{
		lf_string pw,uid,email;
		if (!(lf_token_mgr::singleton().is_online_by_name(name)))
		{
			set_err(404, "User Offline", out_json);
			return false;
		}
		if (!query_password(name, pw))
		{
			set_err(801,"Not Password",out_json);
			return false;
		}
		if (!query_uid(name, uid))
		{
			set_err(801, "Not Uid", out_json);
			return false;
		}
		if (!query_email(name, email))
		{
			set_err(801, "Not Email", out_json);
			return false;
		}
		if (pw != password)
		{
			set_err(404, "Password Error", out_json);
			return false;
		}
		lf_string token = lf_token_mgr::singleton().gen_token(name, password);
		if (token.empty())
		{
			set_err(404, "Not Token", out_json);
			return false;
		}

		Uint64 c_time = time(NULL);
		lf_token_info token_info;
		token_info.uid = uid;
		token_info.token = token;
		token_info.username = name;
		token_info.create_time = c_time;
		token_info.period_validity = 3600;
		if (!(lf_token_mgr::singleton().add_token(token_info)))
		{
			set_err(404, "Add Token Error", out_json);
			return false;
		}
		return true;
	}
	bool lf_task_service_handler::logout(const lf_string & token, lf_string & out_json)
	{
		lf_string uid = lf_token_mgr::singleton().get_uid_by_token(token);
		if (uid.empty())
		{
			return false;
		}
		return false;
	}
	bool lf_task_service_handler::user_register(const lf_string & param, lf_string & out_json)
	{
		return false;
	}
	bool lf_task_service_handler::register_confirm(const lf_string & param, lf_string & out_json)
	{
		return false;
	}
}