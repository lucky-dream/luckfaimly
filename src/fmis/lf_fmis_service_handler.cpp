#include"fmis/lf_fmis_service_handler.h"
#include"task_svr/lf_token_mgr.h"
#include"dbmgr/lf_db_mgr.h"
#include"rapidjson/writer.h"
#include"rapidjson/stringbuffer.h"
#include"rapidjson/document.h"
#include"util/lf_error_code.h"
#include <ctime>
#include"dbmgr/lf_db_transaction_by_mysql.h"
#include"dbmgr/lf_owner_bill_mgr_by_mysql.h"
#include"dbmgr/lf_group_bill_mgr_by_mysql.h"
#include"dbmgr/lf_user_mgr_by_mysql.h"
namespace LF
{
	static void set_out_json_by_status(const uint32_t& status,const lf_string& err_info,
		 lf_string & out_json)
	{
		rapidjson::StringBuffer s;
		rapidjson::Writer<rapidjson::StringBuffer> writer(s);
		writer.StartObject();
		writer.Key("status");
		writer.Uint(status);
		if (status)
		{
			writer.Key("info");
			writer.String(err_info.c_str());
		}
		writer.EndObject();
		out_json.assign(s.GetString(),s.GetSize());
	}
	static void writer_owner_bill_info(rapidjson::Writer<rapidjson::StringBuffer>& writer,const lf_owner_bill_meta& meta)
	{
		writer.Key("obid");
		writer.String(meta._owner_bill_id.c_str());
		writer.Key("btype");
		writer.Uint(meta._owner_bill_type);
		writer.Key("ptype");
		writer.Uint(meta._ptype);
		writer.Key("cdate");
		writer.Uint64(meta._create_date);
		writer.Key("sum");
		writer.Uint64(meta._sum);
		writer.Key("sign");
		writer.String(meta._sign.c_str());
	}
	bool lf_fmis_service_handler::query_owner_bill(const lf_string & uid, const lf_string & param, lf_string & out_json)
	{
		uint32_t status = 0;
		lf_string err;
		rapidjson::Document doc;
		doc.Parse(param.c_str(),param.length());
		if (doc.HasParseError())
		{
			_SET_ERR_CODE(err,status,LF_ERROR_CODE::LF_USER_INVALID_JSON);
			set_out_json_by_status(status,err,out_json);
			return false;
		}
		lf_owner_bill_query_options options;
		options._obid = _CHECK_JSON(doc, "obid", String) ?
			doc["obid"].GetString() : options._obid;
		options._btype = _CHECK_JSON(doc, "btype", Uint) ?
			doc["btype"].GetUint() : options._btype;
		options._ptype = _CHECK_JSON(doc, "ptype", Uint) ?
			doc["ptype"].GetUint() : options._ptype;
		options._sdate = _CHECK_JSON(doc, "sdate", Uint64) ?
			doc["sdate"].GetUint64() : options._sdate;
		options._edate = _CHECK_JSON(doc, "edate", Uint64) ?
			doc["edate"].GetUint64() : options._edate;
		options._keyword = _CHECK_JSON(doc, "keyword", String) ?
			doc["keyword"].GetString() : options._keyword;
		options._summin = _CHECK_JSON(doc, "summin", Uint64) ?
			doc["summin"].GetUint64() : options._summin;
		options._summax = _CHECK_JSON(doc, "summax", Uint64) ?
			doc["summax"].GetUint64() : options._summax;
		options._begin = _CHECK_JSON(doc, "begin", Uint) ?
			doc["begin"].GetUint() : options._begin;
		options._count = _CHECK_JSON(doc, "count", Uint) ?
			doc["count"].GetUint() : options._count;
		auto db = lf_db_module::get_conn();
		if (!db)
		{
			_SET_ERR_CODE(err, status, LF_ERROR_CODE::LF_SYSTEM_DB_CONNECT_ERROR);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		OwnerBillList list;
		uint32_t ret = lf_owner_bill_mgr::find_recode(uid,db,options, list);
		lf_db_module::give_back(db);
		if (ret!=0)
		{
			_SET_ERR_CODE(err, status, ret);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		rapidjson::StringBuffer s;
		rapidjson::Writer<rapidjson::StringBuffer> writer(s);
		writer.StartObject();
		writer.Key("status");
		writer.Uint(0);
		writer.Key("list");
		writer.StartArray();
		for (auto it:list)
		{
			writer.StartObject();
			writer_owner_bill_info(writer,it);
			writer.EndObject();
		}
		writer.EndArray();
		writer.EndObject();
		out_json.assign(s.GetString(),s.GetSize());
		return true;
	}
	bool lf_fmis_service_handler::add_owner_bill(const lf_string & uid, const lf_string & param, lf_string & out_json)
	{
		uint32_t status = 0;
		lf_string err;
		rapidjson::Document doc;
		doc.Parse(param.c_str(), param.length());
		if (doc.HasParseError())
		{
			_SET_ERR_CODE(err, status, LF_ERROR_CODE::LF_USER_INVALID_JSON);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		if (!(_CHECK_JSON(doc,"btype",Uint)
			&& _CHECK_JSON(doc, "ptype", Uint)
			&& _CHECK_JSON(doc, "cdate", Uint64)
			&& _CHECK_JSON(doc, "sum", Uint64)
			&& _CHECK_JSON(doc, "sign", String)))
		{
			_SET_ERR_CODE(err, status, LF_ERROR_CODE::LF_USER_JSON_KEY_ERROR);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		lf_owner_bill_meta meta;
		meta._owner_id = uid;
		meta._owner_bill_type = doc["btype"].GetUint();
		meta._ptype = doc["ptype"].GetUint();
		meta._create_date = doc["cdate"].GetUint64();
		meta._sum = doc["sum"].GetUint();
		meta._sign = doc["sign"].GetString();
		auto db = lf_db_module::get_conn();
		if (!db)
		{
			_SET_ERR_CODE(err, status, LF_ERROR_CODE::LF_SYSTEM_DB_CONNECT_ERROR);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		uint32_t ret = lf_owner_bill_mgr::add_recode(db,meta);
		lf_db_module::give_back(db);
		if (ret != 0)
		{
			_SET_ERR_CODE(err, status, ret);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		set_out_json_by_status(status,"",out_json);
		return true;
	}
	bool lf_fmis_service_handler::del_owner_bill(const lf_string & uid, const lf_string & param, lf_string & out_json)
	{
		uint32_t status = 0;
		lf_string err;
		rapidjson::Document doc;
		doc.Parse(param.c_str(), param.length());
		if (doc.HasParseError())
		{
			_SET_ERR_CODE(err, status, LF_ERROR_CODE::LF_USER_INVALID_JSON);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		if (!(_CHECK_JSON(doc, "obid", String)))
		{
			_SET_ERR_CODE(err, status, LF_ERROR_CODE::LF_USER_JSON_KEY_ERROR);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		lf_string obid = doc["obid"].GetString();
		auto db = lf_db_module::get_conn();
		if (!db)
		{
			_SET_ERR_CODE(err, status, LF_ERROR_CODE::LF_SYSTEM_DB_CONNECT_ERROR);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		uint32_t ret = lf_owner_bill_mgr::del_recode(uid,db, obid);
		lf_db_module::give_back(db);
		if (ret != 0)
		{
			_SET_ERR_CODE(err, status, ret);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		set_out_json_by_status(status, "", out_json);
		return true;
	}
	bool lf_fmis_service_handler::sync_owner_bill_to_group(const lf_string & uid, const lf_string & param, lf_string & out_json)
	{
		uint32_t status = 0;
		lf_string err;
		rapidjson::Document doc;
		doc.Parse(param.c_str(), param.length());
		if (doc.HasParseError())
		{
			_SET_ERR_CODE(err, status, LF_ERROR_CODE::LF_USER_INVALID_JSON);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		if (!(_CHECK_JSON(doc, "obid", Uint)))
		{
			_SET_ERR_CODE(err, status, LF_ERROR_CODE::LF_USER_JSON_KEY_ERROR);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		lf_owner_bill_meta ometa;
		uint32_t ret=0;
		auto db = lf_db_module::get_conn();
		if (!db)
		{
			_SET_ERR_CODE(err, status, LF_ERROR_CODE::LF_SYSTEM_DB_CONNECT_ERROR);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		//---------获取gid--------//
		lf_string gid;
		if (_CHECK_JSON(doc, "gname", String))
		{
			ret = lf_group_mgr::find_id(doc["gname"].GetString(), db, gid);
			if (ret != 0)
			{
				lf_db_module::give_back(db);
				_SET_ERR_CODE(err, status, ret);
				set_out_json_by_status(status, err, out_json);
				return false;
			}
		}
		else if (_CHECK_JSON(doc, "gid", String))
		{
			gid = doc["gid"].GetString();
		}
		else
		{
			lf_db_module::give_back(db);
			_SET_ERR_CODE(err, status, LF_ERROR_CODE::LF_USER_JSON_KEY_ERROR);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		//-------查询owner bill meta-------//
		ret = lf_owner_bill_mgr::find_recode(uid,db,doc["obid"].GetString() ,ometa);
		if (ret != 0)
		{
			lf_db_module::give_back(db);
			_SET_ERR_CODE(err, status, ret);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		//-------- 添加group bill meta ---------//
		lf_group_bill_meta gmeta;
		gmeta._create_date = ometa._create_date;
		gmeta._group_bill_type = ometa._owner_bill_type;
		gmeta._group_id = gid;
		gmeta._owner_id = uid;
		gmeta._ptype = ometa._ptype;
		gmeta._sign = ometa._sign;
		gmeta._status = 1;
		gmeta._sum = ometa._sum;
		ret = lf_group_bill_mgr::add_recode(db, gmeta);
		lf_db_module::give_back(db);
		if (ret != 0)
		{
			_SET_ERR_CODE(err, status, ret);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		set_out_json_by_status(status, "", out_json);
		return true;
	}
	static void writer_group_bill_info(rapidjson::Writer<rapidjson::StringBuffer>& writer, const lf_group_bill_meta& meta)
	{
		writer.Key("gbid");
		writer.String(meta._group_bill_id.c_str());
		writer.Key("gid");
		writer.String(meta._group_id.c_str());
		writer.Key("uid");
		writer.String(meta._owner_id.c_str());
		writer.Key("status");
		writer.Uint(meta._status);
		writer.Key("btype");
		writer.Uint(meta._group_bill_type);
		writer.Key("ptype");
		writer.Uint(meta._ptype);
		writer.Key("cdate");
		writer.Uint64(meta._create_date);
		writer.Key("sum");
		writer.Uint64(meta._sum);
		writer.Key("sign");
		writer.String(meta._sign.c_str());
	}
	bool lf_fmis_service_handler::query_group_bill(const lf_string & uid, const lf_string & param, lf_string & out_json)
	{
		uint32_t status = 0;
		lf_string err;
		rapidjson::Document doc;
		doc.Parse(param.c_str(), param.length());
		if (doc.HasParseError())
		{
			_SET_ERR_CODE(err, status, LF_ERROR_CODE::LF_USER_INVALID_JSON);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		lf_group_bill_query_options options;
		options._gbid = _CHECK_JSON(doc, "gbid", String) ?
			doc["gbid"].GetString() : options._gbid;
		options._btype = _CHECK_JSON(doc, "btype", Uint) ?
			doc["btype"].GetUint() : options._btype;
		options._ptype = _CHECK_JSON(doc, "ptype", Uint) ?
			doc["ptype"].GetUint() : options._ptype;
		options._sdate = _CHECK_JSON(doc, "sdate", Uint64) ?
			doc["sdate"].GetUint64() : options._sdate;
		options._edate = _CHECK_JSON(doc, "edate", Uint64) ?
			doc["edate"].GetUint64() : options._edate;
		options._keyword = _CHECK_JSON(doc, "keyword", String) ?
			doc["keyword"].GetString() : options._keyword;
		options._summin = _CHECK_JSON(doc, "summin", Uint64) ?
			doc["summin"].GetUint64() : options._summin;
		options._summax = _CHECK_JSON(doc, "summax", Uint64) ?
			doc["summax"].GetUint64() : options._summax;
		options._begin = _CHECK_JSON(doc, "begin", Uint) ?
			doc["begin"].GetUint() : options._begin;
		options._count = _CHECK_JSON(doc, "count", Uint) ?
			doc["count"].GetUint() : options._count;
		options._status = _CHECK_JSON(doc, "status", Uint) ?
			doc["status"].GetUint() : options._status;
		lf_string gid;
		uint32_t ret;
		auto db = lf_db_module::get_conn();
		if (!db)
		{
			_SET_ERR_CODE(err, status, LF_ERROR_CODE::LF_SYSTEM_DB_CONNECT_ERROR);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		//----------- gid ---------//
		if (_CHECK_JSON(doc, "gid", String))
		{
			gid = doc["gid"].GetString();
		}
		else if(_CHECK_JSON(doc, "gname", String))
		{
			ret = lf_group_mgr::find_id(doc["gname"].GetString(), db, gid);
			if (ret != 0)
			{
				lf_db_module::give_back(db);
				_SET_ERR_CODE(err, status, ret);
				set_out_json_by_status(status, err, out_json);
				return false;
			}
		}
		else
		{
			lf_db_module::give_back(db);
			_SET_ERR_CODE(err, status, LF_ERROR_CODE::LF_USER_JSON_KEY_ERROR);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		//------------ ownerid ---------//
		if (_CHECK_JSON(doc, "uid", String))
		{
			options._uid = doc["uid"].GetString();
		}
		else if (_CHECK_JSON(doc, "uname", String))
		{
			ret = lf_user_mgr::find_id(doc["uname"].GetString(), db, options._uid);
			if (ret != 0)
			{
				lf_db_module::give_back(db);
				_SET_ERR_CODE(err, status, ret);
				set_out_json_by_status(status, err, out_json);
				return false;
			}
		}
		GroupBillList list;
		ret = lf_group_bill_mgr::find_recode(gid, db, options, list);
		lf_db_module::give_back(db);
		if (ret != 0)
		{
			_SET_ERR_CODE(err, status, ret);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		rapidjson::StringBuffer s;
		rapidjson::Writer<rapidjson::StringBuffer> writer(s);
		writer.StartObject();
		writer.Key("status");
		writer.Uint(0);
		writer.Key("list");
		writer.StartArray();
		for (auto it : list)
		{
			writer.StartObject();
			writer_group_bill_info(writer, it);
			writer.EndObject();
		}
		writer.EndArray();
		writer.EndObject();
		out_json.assign(s.GetString(), s.GetSize());
		return true;
	}
	bool lf_fmis_service_handler::compute_group_bill(const lf_string & uid, const lf_string & param, lf_string & out_json)
	{
		return false;
	}
	bool lf_fmis_service_handler::del_group_bill(const lf_string & uid, const lf_string & param, lf_string & out_json)
	{
		uint32_t status = 0;
		lf_string err;
		rapidjson::Document doc;
		doc.Parse(param.c_str(), param.length());
		if (doc.HasParseError())
		{
			_SET_ERR_CODE(err, status, LF_ERROR_CODE::LF_USER_INVALID_JSON);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		if (!(_CHECK_JSON(doc, "gbid", String)))
		{
			_SET_ERR_CODE(err, status, LF_ERROR_CODE::LF_USER_JSON_KEY_ERROR);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		lf_string gbid = doc["gbid"].GetString();
		lf_string gid;
		uint32_t ret = 0;
		auto db = lf_db_module::get_conn();
		if (!db)
		{
			_SET_ERR_CODE(err, status, LF_ERROR_CODE::LF_SYSTEM_DB_CONNECT_ERROR);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		if (_CHECK_JSON(doc, "gname", String))
		{
			ret = lf_group_mgr::find_id(doc["gname"].GetString(), db, gid);
			if (ret != 0)
			{
				lf_db_module::give_back(db);
				_SET_ERR_CODE(err, status, ret);
				set_out_json_by_status(status, err, out_json);
				return false;
			}
		}
		else if (_CHECK_JSON(doc, "gid", String))
		{
			gid = doc["gid"].GetString();
		}
		else
		{
			lf_db_module::give_back(db);
			_SET_ERR_CODE(err, status, LF_ERROR_CODE::LF_USER_JSON_KEY_ERROR);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		ret = lf_group_bill_mgr::del_recode(gid, db, gbid);
		lf_db_module::give_back(db);
		if (ret != 0)
		{
			_SET_ERR_CODE(err, status, ret);
			set_out_json_by_status(status, err, out_json);
			return false;
		}
		set_out_json_by_status(status, "", out_json);
		return true;
	}
}