#ifndef LF_FMIS_SERVICE_HANDLER_H
#define LF_FMIS_SERVICE_HANDLER_H
#include"util/lf_base_def.h"
namespace LF
{
	class lf_fmis_service_handler
	{
	public:
		//查询个人账单记录
		static bool query_owner_bill(const lf_string& uid,const lf_string& param,lf_string& out_json);
		//添加个人账单记录
		static bool add_owner_bill(const lf_string& uid, const lf_string& param, lf_string& out_json);
		//删除个人帐单记录
		static bool del_owner_bill(const lf_string& uid,const lf_string& param,lf_string& out_json);
		//将个人帐单同步到组
		static bool sync_owner_bill_to_group(const lf_string& uid, const lf_string& param, lf_string& out_json);
		//查询组账单
		static bool query_group_bill(const lf_string& uid, const lf_string& param, lf_string& out_json);
		//计算组账单
		static bool compute_group_bill(const lf_string& uid, const lf_string& param, lf_string& out_json);
		//删除组账单
		static bool del_group_bill(const lf_string& uid, const lf_string& param, lf_string& out_json);
	private:

	}; 
}
#endif // !LF_FMIS_SERVICE_HANDLER_H

