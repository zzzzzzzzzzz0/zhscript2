/*
 * debug.h
 *
 *  Created on: 2016年8月24日
 *      Author: zzzzzzzzzzz
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include "arg.h"

void o_begin__(const char r);
void o_end__(const char r);
void o_2__();
void o_2__(const char* s);
void o_2__(const std::string &s);
void o_2__(unsigned long s);
void o_2__(char s);
void o_2__(long double s);
void o_2__(bool s);
void o_2__(int s);
void o_2__(unsigned int s);
template<typename T, typename... S>
void o_2__(T t, S... s) {
	o_2__(t);
	o_2__(s...);
}
template<typename... S>
void o__(const char c, S... s) {
	o_begin__(c);
	o_2__(s...);
	o_end__(c);
}
void o_n__();

class Debug {
public:
	bool
	o_ansi_ = false,
	o_tree_ = false,
	o_cache_ = false,
	o_args_ = false,
	o_path_ = false,
	o_liucheng_ = false,
	o_if_ = false,
	o_ret_ = false;
	bool parse__(const std::string& s);

	void o_args__(const arg::List* args);
	void o_args__(int argc, const char** argv, int from);
};

extern Debug debug_;

#endif /* DEBUG_H_ */
