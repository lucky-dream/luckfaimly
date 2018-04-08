#ifndef LF_OWNER_BILL_MGR_H
#define LF_OWNER_BILL_MGR_H
#include"util/lf_base_def.h"
#include"dbmgr/lf_db_mgr.h"
#include"dbmgr/lf_bill_meta.h"
namespace LF 
{
	//个人账单查询可选项
	struct lf_owner_bill_query_options
	{
		lf_string _obid; //个人账单id，可选（默认不限id）；
		Uint32 _type;	 //资源类型，掩码格式（具体值待定），可选，默认返回不限类型
		Uint32 _ptype;	//支付方式，掩码格式（具体值待定），可选，默认返回不限支付方式
		Uint64 _sdate;	//查询起始日期，可选，默认返回不限起始日期
		Uint64 _edate;	//查询结束日期，可选，默认返回不限结束日期
		lf_string _keyword;	 // “sign”关键字查询，可选，默认返回不限“sign”关键字
		Uint64 _summin;		 //金额最小值，可选，默认返回不限最小金额
		Uint64 _summax;		 //金额最大值，可选，默认返回不限最大金额
		lf_owner_bill_query_options()
			:_obid(""), _type(0XFFFFFFFF),_ptype(0XFFFFFFFF),
			_sdate(0),_edate(0XFFFFFFFFFFFFFFFF), _keyword(""),
			_summin(0),_summax(0XFFFFFFFFFFFFFFFF)
		{}
	};
	class lf_owner_bill_mgr
	{
	public:
		static Uint32 add_recode(lf_db_object* db,lf_owner_bill_meta meta);
		static Uint32 del_recode(lf_db_object* db,const lf_string& bill_id);
		static bool has_recode(lf_db_object* db, const lf_string& bill_id);
		static Uint32 find_recode(lf_db_object* db, const lf_string& bill_id, lf_owner_bill_meta& meta);
		static Uint32 find_recode(lf_db_object* db, const lf_owner_bill_query_options& filter_options,OwenrBillList& out_list);
	private:

	};
}
#endif // !LF_OWNER_BILL_MGR_H

