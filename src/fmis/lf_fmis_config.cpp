#include"fmis/lf_fmis_config.h"
#include"net/lf_proxy_conf.h"
#include"dbmgr/lf_db_mgr.h"
#include <fstream>
#include"rapidjson/document.h"
#define _CHECK_JSON(Doc,Key,Type) (((Doc).HasMember(Key)?true:false)&&(Doc)[Key].Is##Type())
namespace LF
{
	OBJ_SINGLETON_INIT(lf_fmis_config_mgr);
	lf_fmis_config_mgr g_lf_fmis_config_mgr;
	static bool parse_database_config(const rapidjson::Document::Object& db_obj)
	{
		if (!(_CHECK_JSON(db_obj, "ip", String)
			&& _CHECK_JSON(db_obj, "port", Uint)
			&& _CHECK_JSON(db_obj, "user", String)
			&& _CHECK_JSON(db_obj, "password", String)
			&& _CHECK_JSON(db_obj, "db_name", String)))
		{
			return false;
		}
		lf_db_info db_info;
		db_info._host = db_obj["ip"].GetString();
		db_info._port = db_obj["port"].GetUint();
		db_info._user_name = db_obj["user"].GetString();
		db_info._password = db_obj["password"].GetString();
		db_info._dbname = db_obj["db_name"].GetString();
		if (!lf_db_module::init(db_info))
		{
			return false;
		}
		return true;
	}

	bool lf_fmis_config_mgr::read_config_file(const lf_string & path)
	{
		std::ifstream fd(path, std::ios::out | std::ios::binary | std::ios::ate);
		if (!fd.is_open())
		{
			return false;
		}
		int count = fd.tellg();
		char* m_data = new char[count + 1];
		fd.seekg(0, std::ios::beg);
		fd.read(m_data, count);
		m_data[count] = '\0';
		int m_data_len = count + 1;

		rapidjson::Document doc;
		doc.Parse(m_data, m_data_len);
		if (doc.HasParseError())
		{
			return false;
		}
		if (!_CHECK_JSON(doc, "fmis",Object))
		{
			return false;
		}
		
		rapidjson::Document::Object svr_obj = doc["fmis"].GetObject();
		if (!(_CHECK_JSON(svr_obj, "ip", String)
			&&  _CHECK_JSON(svr_obj, "port", String)
			&& _CHECK_JSON(svr_obj, "db", Object)))
		{
			return false;
		}
		_tasksvr.ip = svr_obj["ip"].GetString();
		_tasksvr.port = svr_obj["port"].GetString();
		rapidjson::Document::Object& db_obj = svr_obj["db"].GetObject();
		if (!parse_database_config(db_obj))
		{
			return false;
		}
		return true;
	}


}