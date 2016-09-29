/*
 * eval.h
 *
 *  Created on: 2016年8月25日
 *      Author: zzzzzzzzzzz
 */

#ifndef EVAL_H_
#define EVAL_H_

#include <vector>
#include <string>
#include "result.h"

namespace eval {

using Result2 = Result<bool, unsigned char>;

enum class Typ {N, O};

class Item {
public:
	Typ typ_;
	long double val_;
	char val2_;
	Item(long double val) : typ_(Typ::N), val_(val) {}
	Item(char val) : typ_(Typ::O), val2_(val) {}
};

class List {
private:
	std::vector<Item*> a_;
	void z5__(char o, long double val, long double& ret);
	void z4__(Item* i, size_t& ii, char& o, long double& ret);
	void z2__(char chk, size_t& ii, long double& ret);
public:
	~List();
	void clear__() {a_.clear();}
	void add__(std::string& s) {
		if(!s.empty()) {
			a_.push_back(new Item(std::stold(s)));
			s.clear();
		}
	}

	Result2* parse__(const std::string& s);
	long double z__() {
		long double ret = 0;
		size_t ii = 0;
		z2__(' ', ii, ret);
		return ret;
	}
	void pn__();
};

} /* namespace eval */

#endif /* EVAL_H_ */
