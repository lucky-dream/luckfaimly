#include"util/lf_error_code.h"
namespace LF {
#define ALL_USER_ERROR_MSG(XX) {USER_MSG_CODE_ERROR_MAP(XX)}
#define XX(num, name, string) string,
	static char*	user_error_msg[LF_ERROR_CODE::LF_USER_ERROR_END&0XFF] = ALL_USER_ERROR_MSG(XX);
#undef ALL_USER_ERROR_MSG

#define ALL_SYSTEM_ERROR_MSG(XX) {SYSTEM_MSG_CODE_ERROR_MAP(XX)}
	static char*	system_error_msg[LF_ERROR_CODE::LF_SYSTEM_ERROR_END&0XFF] = ALL_SYSTEM_ERROR_MSG(XX);
#undef ALL_SYSTEM_ERROR_MSG
#undef XX
	const char* lf_error_code::get_error_msg(uint32_t err_code)
	{
		uint32_t Err_code  = err_code & 0XFFFF;
		switch (Err_code >> 8)
		{
		case 0X1:
			if (Err_code >= LF_ERROR_CODE::LF_USER_ERROR_END)
			{
				break;
			}
			return user_error_msg[Err_code & 0XFF];
		case 0X2:
			if (Err_code >= LF_ERROR_CODE::LF_SYSTEM_ERROR_END)
			{
				break;
			}
			return system_error_msg[Err_code & 0XFF];
		default:
			break;
		}
		return "Invalid error code.";
	}
	bool lf_error_code::get_error_msg(uint32_t err_code, lf_string &err_msg)
	{
		uint32_t Err_code = err_code & 0XFFFF;
		switch (Err_code >> 8)
		{
		case 0X1:
			if (Err_code >= LF_ERROR_CODE::LF_USER_ERROR_END)
			{
				break;
			}
			err_msg.assign(user_error_msg[Err_code & 0XFF]);
			return true;
		case 0X2:
			if (Err_code >= LF_ERROR_CODE::LF_SYSTEM_ERROR_END)
			{
				break;
			}
			err_msg.assign(system_error_msg[Err_code & 0XFF]);
			return true;
		default:
			break;
		}
		err_msg.assign("Invalid error code.");
		return false;
	}
}//!end lf
