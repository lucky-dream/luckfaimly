#ifndef LF_GROUP_BILL_MGR_H
#define LF_GROUP_BILL_MGR_H
#include"util/lf_base_def.h"
#include"dbmgr/lf_db_mgr.h"
#include"dbmgr/lf_bill_meta.h"
namespace LF
{
	//个人账单查询可选项
	struct lf_group_bill_query_options
	{
		lf_string _gbid; //组账单id，可选（默认不限id）；
		lf_string _gname; //组名，必选
		Uint32 _status;  //结算状态，1：未结算；2：已结算。可选，默认不限结算状态
		lf_string _owner;   //账单所属者名。可选，默认不限账单所属者
		Uint32 _type;	 //资源类型，掩码格式（具体值待定），可选，默认返回不限类型
		Uint32 _ptype;	//支付方式，掩码格式（具体值待定），可选，默认返回不限支付方式
		Uint64 _sdate;	//查询起始日期，可选，默认返回不限起始日期
		Uint64 _edate;	//查询结束日期，可选，默认返回不限结束日期
		lf_string _keyword;	 // “sign”关键字查询，可选，默认返回不限“sign”关键字
		Uint64 _summin;		 //金额最小值，可选，默认返回不限最小金额
		Uint64 _summax;		 //金额最大值，可选，默认返回不限最大金额
		lf_group_bill_query_options()
			:_gbid(""), _type(0XFFFFFFFF), _ptype(0XFFFFFFFF),
			_sdate(0), _edate(0XFFFFFFFFFFFFFFFF), _keyword(""),
			_summin(0), _summax(0XFFFFFFFFFFFFFFFF),_gname(""),
			_status(0XFFFFFFFF),_owner("")
		{}
	};
	class lf_group_bill_mgr
	{
	public:
		static Uint32 add_recode(lf_db_object* db, lf_group_bill_meta meta);
		static Uint32 del_recode(lf_db_object* db, const lf_string& bill_id);
		static bool has_recode(lf_db_object* db, const lf_string& bill_id);
		static Uint32 find_recode(lf_db_object* db, const lf_string& bill_id, lf_group_bill_meta& meta);
		static Uint32 find_recode(lf_db_object* db, const lf_group_bill_query_options& filter_options, GroupBillList& out_list);
		static Uint32 get_bill_status(lf_db_object* db, const lf_string& bill_id, Uint32& bill_status);
		static Uint32 update_bill_status(lf_db_object* db, const lf_string& bill_id, const Uint32& bill_status);
	private:

	};

}
#endif // !LF_GROUP_BILL_MGR_H
