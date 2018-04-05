#ifndef LF_USER_REGISTER_CACHE_H
#define LF_USER_REGISTER_CACHE_H
#include"util/lf_singleton.h"
#include<memory>
#include<map>
namespace LF
{
	struct lf_user_info
	{
		lf_string _name;
		lf_string _password;
		lf_string _email;
		Uint32 _sex;
		lf_string _sign;
		Uint64 _ctime;
	};
	typedef std::shared_ptr<lf_user_info> UserInfoPtr;
	class lf_user_register_cache:public lf_singleton<lf_user_register_cache>
	{
	public:
		void clear_timeout();
		bool add_recode(const UserInfoPtr& user_info);
		bool has_recode(const lf_string& name);
		bool del_recode(const lf_string& name);
		UserInfoPtr get_user_info(const lf_string& name);
	private:
		typedef std::map<lf_string, UserInfoPtr> UserInfoMap;
		UserInfoMap _users;
	};
}
#endif // !LF_USER_REGISTER_CACHE_H

