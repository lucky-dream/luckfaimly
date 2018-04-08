#ifndef LF_FMIS_SERVICE_HANDLER_H
#define LF_FMIS_SERVICE_HANDLER_H
#include"util/lf_base_def.h"
namespace LF
{
	class lf_fmis_service_handler
	{
	public:
		//��ѯ�����˵���¼
		static bool query_owner_bill(const lf_string& uid,const lf_string& param,lf_string& out_json);
		//��Ӹ����˵���¼
		static bool add_owner_bill(const lf_string& uid, const lf_string& param, lf_string& out_json);
		//ɾ�������ʵ���¼
		static bool del_owner_bill(const lf_string& uid,const lf_string& param,lf_string& out_json);
		//�������ʵ�ͬ������
		static bool sync_owner_bill_to_group(const lf_string& uid, const lf_string& param, lf_string& out_json);
		//��ѯ���˵�
		static bool query_group_bill(const lf_string& uid, const lf_string& param, lf_string& out_json);
		//�������˵�
		static bool compute_group_bill(const lf_string& uid, const lf_string& param, lf_string& out_json);
		//ɾ�����˵�
		static bool del_group_bill(const lf_string& uid, const lf_string& param, lf_string& out_json);
	private:

	}; 
}
#endif // !LF_FMIS_SERVICE_HANDLER_H

