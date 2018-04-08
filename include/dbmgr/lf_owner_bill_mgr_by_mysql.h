#ifndef LF_OWNER_BILL_MGR_H
#define LF_OWNER_BILL_MGR_H
#include"util/lf_base_def.h"
#include"dbmgr/lf_db_mgr.h"
#include"dbmgr/lf_bill_meta.h"
namespace LF 
{
	//�����˵���ѯ��ѡ��
	struct lf_owner_bill_query_options
	{
		lf_string _obid; //�����˵�id����ѡ��Ĭ�ϲ���id����
		Uint32 _type;	 //��Դ���ͣ������ʽ������ֵ����������ѡ��Ĭ�Ϸ��ز�������
		Uint32 _ptype;	//֧����ʽ�������ʽ������ֵ����������ѡ��Ĭ�Ϸ��ز���֧����ʽ
		Uint64 _sdate;	//��ѯ��ʼ���ڣ���ѡ��Ĭ�Ϸ��ز�����ʼ����
		Uint64 _edate;	//��ѯ�������ڣ���ѡ��Ĭ�Ϸ��ز��޽�������
		lf_string _keyword;	 // ��sign���ؼ��ֲ�ѯ����ѡ��Ĭ�Ϸ��ز��ޡ�sign���ؼ���
		Uint64 _summin;		 //�����Сֵ����ѡ��Ĭ�Ϸ��ز�����С���
		Uint64 _summax;		 //������ֵ����ѡ��Ĭ�Ϸ��ز��������
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

