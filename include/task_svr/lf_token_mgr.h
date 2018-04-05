#ifndef LF_TOKEN_MGR_H
#define LF_TOKEN_MGR_H
#include"util/lf_singleton.h"
#include"util/lf_lock.h"
#include<map>
namespace LF
{
	class lf_token_mgr:public lf_singleton<lf_token_mgr>
	{
	public:
		lf_string gen_token(const lf_string& name,const lf_string& password);
		bool add_token(const lf_string& uid,const lf_string& token);
		bool is_online(const lf_string& token);
		lf_string get_uid_by_token(const lf_string& token);
		void del_token(const lf_string& token);
	private:
		typedef std::map<lf_string, lf_string> TokenMap;
		TokenMap _tokens;
		lf_lock _mutex;
	};
}
#endif // !LF_TOKEN_MGR_H

