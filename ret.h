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

using Tag_List = std::vector<std::string>;

class Ret_Item {
public:
	std::string val_;
	Tag_List tags_;
	char typ_ = 0;
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
	void push__(char typ, Sptr_ val2);
	void push2__(int i);
	void push_tag__(const std::string &s) {buf_.tags_.push_back(s);}

	void one__(bool auto1 = true);
};

#endif /* RET_H_ */
