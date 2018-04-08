#ifndef LF_GROUP_BILL_MGR_H
#define LF_GROUP_BILL_MGR_H
#include"util/lf_base_def.h"
#include"dbmgr/lf_db_mgr.h"
#include"dbmgr/lf_bill_meta.h"
namespace LF
{
	//�����˵���ѯ��ѡ��
	struct lf_group_bill_query_options
	{
		lf_string _gbid; //���˵�id����ѡ��Ĭ�ϲ���id����
		lf_string _gname; //��������ѡ
		Uint32 _status;  //����״̬��1��δ���㣻2���ѽ��㡣��ѡ��Ĭ�ϲ��޽���״̬
		lf_string _owner;   //�˵�������������ѡ��Ĭ�ϲ����˵�������
		Uint32 _type;	 //��Դ���ͣ������ʽ������ֵ����������ѡ��Ĭ�Ϸ��ز�������
		Uint32 _ptype;	//֧����ʽ�������ʽ������ֵ����������ѡ��Ĭ�Ϸ��ز���֧����ʽ
		Uint64 _sdate;	//��ѯ��ʼ���ڣ���ѡ��Ĭ�Ϸ��ز�����ʼ����
		Uint64 _edate;	//��ѯ�������ڣ���ѡ��Ĭ�Ϸ��ز��޽�������
		lf_string _keyword;	 // ��sign���ؼ��ֲ�ѯ����ѡ��Ĭ�Ϸ��ز��ޡ�sign���ؼ���
		Uint64 _summin;		 //�����Сֵ����ѡ��Ĭ�Ϸ��ز�����С���
		Uint64 _summax;		 //������ֵ����ѡ��Ĭ�Ϸ��ز��������
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
