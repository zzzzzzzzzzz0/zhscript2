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
	Item(long double val) : typ_(Typ::N), val_(val), val2_(0) {}
	Item(char val) : typ_(Typ::O), val_(0), val2_(val) {}
};

class List {
private:
	std::vector<Item*> a_;
	size_t i_;
	Item* item__();
	void next__();
	long double z2__();
	long double z3__();
	long double z4__();
	long double z5__();
public:
	~List();
	void clear__() {a_.clear();}
	void add__(std::string& s);

	Result2 parse__(const std::string& s);
	long double z__() {
		i_ = 0;
		return z2__();
	}
};

} /* namespace eval */

#endif /* EVAL_H_ */
