#ifndef LF_TOKEN_MGR_H
#define LF_TOKEN_MGR_H
#include"util/lf_singleton.h"
#include"util/lf_lock.h"
#include<map>
namespace LF
{
	struct lf_token_info
	{
		lf_string uid;
		lf_string username;
		lf_string token;
		uint64_t period_validity;
		uint64_t create_time;
	};
	class lf_token_mgr:public lf_singleton<lf_token_mgr>
	{
	public:
		lf_string gen_token(const lf_string& name,const lf_string& password);
		bool add_token(const lf_token_info& token_info);
		bool is_online_by_token(const lf_string& token);
		bool is_online_by_name(const lf_string& name);
		lf_string get_uid_by_token(const lf_string& token);
		void del_token_by_token(const lf_string& token);
		void del_token_by_name(const lf_string& token);
	private:
		typedef std::map<lf_string, lf_token_info> name_TokenMap;
		typedef std::map<lf_string, lf_token_info> token_TokenMap;
		name_TokenMap _name_token;
		token_TokenMap _token_token;
		lf_lock _mutex;
		lf_token_info _token_info;
	};
}
#endif // !LF_TOKEN_MGR_H

