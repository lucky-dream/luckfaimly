#ifndef LF_BILL_META_H
#define LF_BILL_META_H
#include"util/lf_base_def.h"
namespace LF
{
#define MAX_MASK_DEFAULT_32 0XFFFFFFFF     //32位最大掩码
#define MAX_MASK_DEFAULT_64 0XFFFFFFFFFFFFFFFF  //64位最大掩码
#define MAX_NUM_64 0XFFFFFFFFFFFFFFFF   //64位最大值
#define MAX_RETURN_RECODE_COUNT 10000   //数据库单次返回最大值
	enum LF_BILL_PAYMENT_MASK
	{
		LF_PTYPE_PAY_OUT = 0X0,    //支出
		LF_PTYPE_PAY_IN = 0X1,   //收入
		LF_PTYPE_ZI_FU_BAO = 0X2, //支付宝
		LF_PTYPE_WEI_XIN = 0X4, //微信
		LF_PTYPE_YIN_HANG_KA = 0X8, //银行卡
		LF_PTYPE_OTHER = 0X80000000 //其他
	};
	enum LF_BILL_TYPE
	{
		LF_BTYPE_GROUP_BILL_CAST = 0X1, //组账单清算
		LF_BTYPE_FOOD_AND_BEVERAGE = 0X2, //餐饮
		LF_BTYPE_TRANSPORTATION = 0X4, //交通
		LF_BTYPE_DAILY_USE = 0X8,  //生活日用
		LF_BTYPE_COMMUNICATION = 0X10,  //通讯
		LF_BTYPE_COSTUME = 0X20,   //服饰
		LF_BTYPE_HOUSING_PAYMENT = 0X40, //住房缴费
		LF_BTYPE_CULTURAL_CONSUMPTION = 0X80, //文娱消费
		LF_BTYPE_OTHER = 0X80000000 //其他
	};
	struct lf_owner_bill_meta
	{
		lf_string _owner_bill_id; //个人帐单id
		lf_string _owner_id;   //所属用户id
		uint32_t _owner_bill_type;		//个人帐单类型
		uint32_t _ptype;				//支付类型
		uint64_t _create_date;       //账单创建日期
		uint64_t _sum;            //账单金额
		lf_string _sign;        //账单描述
	};
	typedef std::vector<lf_owner_bill_meta> OwnerBillList;
	struct lf_group_bill_meta
	{
		lf_string _group_bill_id;  //组账单id
		lf_string _group_id;  //所属组id
		lf_string _owner_id;  //支付者id
		uint32_t _group_bill_type;		//个人帐单类型
		uint32_t _ptype;				//支付类型
		uint64_t _create_date;       //账单创建日期
		uint64_t _sum;            //账单金额
		lf_string _sign;        //账单描述
		uint32_t _status;   //结算状态，0：未结算；1：已结算。
	};
	typedef std::vector<lf_group_bill_meta> GroupBillList;
}
#endif // !LF_BILL_META_H

