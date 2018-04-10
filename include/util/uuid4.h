/**
 * Copyright (c) 2016 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#ifndef UUID4_H
#define UUID4_H
#include<string>
namespace LF
{
#define UUID4_VERSION "0.1.0"
#define UUID4_LEN 37

	enum {
		UUID4_ESUCCESS = 0,
		UUID4_EFAILURE = -1
	};
	class lf_uuid_generator
	{
	public:
		static  std::string uuid_generate();
	private:

	};
}


#endif
