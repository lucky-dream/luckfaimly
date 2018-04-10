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
		uint32_t _btype;	 //��Դ���ͣ������ʽ������ֵ����������ѡ��Ĭ�Ϸ��ز�������
		uint32_t _ptype;	//֧����ʽ�������ʽ������ֵ����������ѡ��Ĭ�Ϸ��ز���֧����ʽ
		uint64_t _sdate;	//��ѯ��ʼ���ڣ���ѡ��Ĭ�Ϸ��ز�����ʼ����
		uint64_t _edate;	//��ѯ�������ڣ���ѡ��Ĭ�Ϸ��ز��޽�������
		lf_string _keyword;	 // ��sign���ؼ��ֲ�ѯ����ѡ��Ĭ�Ϸ��ز��ޡ�sign���ؼ���
		uint64_t _summin;		 //�����Сֵ����ѡ��Ĭ�Ϸ��ز�����С���
		uint64_t _summax;		 //������ֵ����ѡ��Ĭ�Ϸ��ز��������
		uint32_t _begin;       //������ʼλ�ã���ѡ��Ĭ��Ϊ0
		uint32_t _count;		 //���η�������������ѡ��Ĭ��Ϊ10000
		lf_owner_bill_query_options()
			:_obid(""), _btype(MAX_MASK_DEFAULT_32),_ptype(MAX_MASK_DEFAULT_32),
			_sdate(0),_edate(MAX_NUM_64), _keyword(""),
			_summin(0),_summax(MAX_NUM_64),_begin(0),_count(MAX_RETURN_RECODE_COUNT)
		{}
	};
	class lf_owner_bill_mgr
	{
	public:
		static uint32_t add_recode(lf_db_object* db,lf_owner_bill_meta meta);
		static uint32_t del_recode(const lf_string& uid,lf_db_object* db,const lf_string& bill_id);
		static bool has_recode(const lf_string& uid,lf_db_object* db, const lf_string& bill_id);
		static uint32_t find_recode(const lf_string& uid, lf_db_object* db, const lf_string& bill_id, lf_owner_bill_meta& meta);
		static uint32_t find_recode(const lf_string& uid, lf_db_object* db, const lf_owner_bill_query_options& filter_options,OwnerBillList& out_list);
	private:

	};
}
#endif // !LF_OWNER_BILL_MGR_H

