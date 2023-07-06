/*
 * Lib.h
 *
 *  Created on: 2016年8月19日
 *      Author: zzzzzzzzzzz
 */

#ifndef LIB_H_
#define LIB_H_

#include "segm/mod.h"
#include "clpars.h"

class Lib {
private:
	arg::List args_;
	segm::List ls_;
	Clpars clpars_;
public:
	Lib();

	void cmdline_parse__(int argc, const char** argv, int from);
	void cmdline_parse__(const std::string& s) {clpars_.z__(s, args_);}
	void set_path__(const char* s) {ls_.file_.known_path2_add__(s);}
	bool has_src__() {return !args_.src_.empty();}

	arg::List *args__() {return &args_;}
	segm::List *ls__() {return &ls_;}

	Qv* new_main_qu__();
};

#endif /* LIB_H_ */
