/*
 * Ret.h
 *
 *  Created on: 2016年8月19日
 *      Author: zzzzzzzzzzz
 */

#ifndef RET_H_
#define RET_H_

#include <string>
#include <vector>
#include "sptr.h"
#include "tag.h"
#include "arg.h"

class Ret_Item {
public:
	std::string val_;
	Tag_List tags_;
	Typ2 typ2_ = Typ2::No;
	Sptr_ val2_;
};

using Ret_List = std::vector<Ret_Item>;

class Ret {
private:
	Ret_Item buf_;
	bool has_push_ = false;
	int has_push2_ = 0;
public:
	Ret_List a_;

	void push__(const std::string &s);
	void push__(Typ2 typ2, Sptr_ val2);
	void push__(const Tag_List &tags);
	void push__(const arg::Item &i);
	void push2__(int i);
	void push_tag__(const std::string &s) {buf_.tags_.push_back(s);}
	void push__(Ret &s, size_t from = 0, size_t to = SIZE_MAX);

	void one__(bool auto1 = true, Ret* s = nullptr);
	void dunhao__() {
		one__(false);
		push2__(1);
	}
	void clear_push2__() {has_push2_ = 0;}
	void back__(size_t hold);
};

#endif /* RET_H_ */
