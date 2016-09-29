/*
 * Lib.h
 *
 *  Created on: 2016年8月19日
 *      Author: zzzzzzzzzzz
 */

#ifndef LIB_H_
#define LIB_H_

#include "qv.h"
#include "ret.h"
#include "result2.h"

class Lib {
private:
	arg::List args_;
	bool all_is_param_ = false;
public:
	void cmdline_parse__(int argc, const char** argv);
	void cmdline_parse__(const std::string& s);
	void cmdline_parse2__(const std::string& s);
	bool has_src__() {return !args_.src_.empty();}
	Result2 z__(Ret &ret);
	Result2 z__(const std::string &s, Ret &ret);
};

#endif /* LIB_H_ */
