/*
 * debug.h
 *
 *  Created on: 2016年8月24日
 *      Author: zzzzzzzzzzz
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include "arg.h"
#include "segm/all.h"

template<typename T>
void o__(std::initializer_list<T> s, const char c = 0);
void o_n__();

class Debug {
private:
	void ptree__(const segm::All* a, int lvl, size_t lvl2, const char c);
	void head__(int lvl, size_t lvl2, int i3);
public:
	bool
	o_ansi_ = false,
	o_tree_ = false,
	o_args_ = false,
	o_path_ = false,
	o_liucheng_ = false,
	o_if_ = false,
	o_ret_ = false;
	bool parse__(const std::string& s);

	void ptree__(const segm::All* a, bool has_cache) {ptree__(a, 0, 0, has_cache ? 'C' : 'c');}
	void o_args__(const arg::List* args);
	void o_args__(int argc, const char** argv, int from);
};

extern Debug debug_;

#endif /* DEBUG_H_ */
