#ifndef LF_BILL_META_H
#define LF_BILL_META_H
#include"util/lf_base_def.h"
namespace LF
{
#define MAX_MASK_DEFAULT_32 0XFFFFFFFF     //32λ�������
#define MAX_MASK_DEFAULT_64 0XFFFFFFFFFFFFFFFF  //64λ�������
#define MAX_NUM_64 0XFFFFFFFFFFFFFFFF   //64λ���ֵ
#define MAX_RETURN_RECODE_COUNT 10000   //���ݿⵥ�η������ֵ
	enum LF_BILL_PAYMENT_MASK
	{
		LF_PTYPE_PAY_OUT = 0X0,    //֧��
		LF_PTYPE_PAY_IN = 0X1,   //����
		LF_PTYPE_ZI_FU_BAO = 0X2, //֧����
		LF_PTYPE_WEI_XIN = 0X4, //΢��
		LF_PTYPE_YIN_HANG_KA = 0X8, //���п�
		LF_PTYPE_OTHER = 0X80000000 //����
	};
	enum LF_BILL_TYPE
	{
		LF_BTYPE_GROUP_BILL_CAST = 0X1, //���˵�����
		LF_BTYPE_FOOD_AND_BEVERAGE = 0X2, //����
		LF_BTYPE_TRANSPORTATION = 0X4, //��ͨ
		LF_BTYPE_DAILY_USE = 0X8,  //��������
		LF_BTYPE_COMMUNICATION = 0X10,  //ͨѶ
		LF_BTYPE_COSTUME = 0X20,   //����
		LF_BTYPE_HOUSING_PAYMENT = 0X40, //ס���ɷ�
		LF_BTYPE_CULTURAL_CONSUMPTION = 0X80, //��������
		LF_BTYPE_OTHER = 0X80000000 //����
	};
	struct lf_owner_bill_meta
	{
		lf_string _owner_bill_id; //�����ʵ�id
		lf_string _owner_id;   //�����û�id
		uint32_t _owner_bill_type;		//�����ʵ�����
		uint32_t _ptype;				//֧������
		uint64_t _create_date;       //�˵���������
		uint64_t _sum;            //�˵����
		lf_string _sign;        //�˵�����
	};
	typedef std::vector<lf_owner_bill_meta> OwnerBillList;
	struct lf_group_bill_meta
	{
		lf_string _group_bill_id;  //���˵�id
		lf_string _group_id;  //������id
		lf_string _owner_id;  //֧����id
		uint32_t _group_bill_type;		//�����ʵ�����
		uint32_t _ptype;				//֧������
		uint64_t _create_date;       //�˵���������
		uint64_t _sum;            //�˵����
		lf_string _sign;        //�˵�����
		uint32_t _status;   //����״̬��0��δ���㣻1���ѽ��㡣
	};
	typedef std::vector<lf_group_bill_meta> GroupBillList;
}
#endif // !LF_BILL_META_H

