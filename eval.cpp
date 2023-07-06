/*
 * eval.cpp
 *
 *  Created on: 2016年8月25日
 *      Author: zzzzzzzzzzz
 */

#include "eval.h"
#ifdef ver_no_std_to_string_
#include "util.h"
#endif

namespace eval {

List::~List() {
	for(auto i : a_) {
		delete i;
	}
}

void List::add__(std::string& s) {
	if(!s.empty()) {
		a_.push_back(new Item(std::stold(s)));
		s.clear();
	}
}

Result2 List::parse__(const std::string& s) {
	std::string s2;
	for(auto c : s) {
		if((c >= '0' && c <= '9') || c == '.') {
			s2 += c;
		} else {
			switch(c) {
			case '+': case '-': case '*': case '/': case '%': case '^':
			case '(': case ')':
				add__(s2);
				a_.push_back(new Item(c));
				break;
			default:
				return Result2::Err(c);
			}
		}
	}
	add__(s2);
	return Result2::Ok(true);
}

Item* List::item__() {
	return i_ < a_.size() ? a_[i_] : nullptr;
}

void List::next__() {
	i_++;
}

long double List::z2__() {
	long double ret = z3__();
	for(;;) {
		Item* i = item__();
		if(!i)
			return ret;
		switch(i->val2_) {
		case '+': case '-':
			break;
		default:
			return ret;
		}
		next__();
		if(i->val2_ == '+')
			ret += z3__();
		else
			ret -= z3__();
	}
}

long double List::z3__() {
	long double ret = z4__();
	for(;;) {
		Item* i = item__();
		if(!i)
			return ret;
		switch(i->val2_) {
		case '*': case '/': case '%':
			break;
		default:
			return ret;
		}
		next__();
		switch(i->val2_) {
		case '*': ret *= z4__(); break;
		case '/': ret /= z4__(); break;
		case '%': {
			long long i2 = (long long)z4__();
			if(!i2)
				throw "求余不能0";
			ret = (long long)ret % i2;
			break; }
		}
	}
}

long double List::z4__() {
	long double ret = z5__();
	for(;;) {
		Item* i = item__();
		if(!i)
			return ret;
		switch(i->val2_) {
		case '^':
			break;
		default:
			return ret;
		}
		next__();
		switch(i->val2_) {
		case '^': {
			long double i2 = ret;
			long len = z4__();
			for(long i = 0; i < len; i++)
				ret *= i2;
			break; }
		}
	}
}

long double List::z5__() {
	Item* i = item__();
	if(!i)
		throw "缺";
	if(i->typ_ == Typ::N) {
		next__();
		return i->val_;
	}
	switch(i->val2_) {
	case '(': {
		next__();
		long double ret = z2__();
		if(item__()->val2_ != ')')
			throw "应是“)”";
		next__();
		return ret; }
	case '-':
		next__();
		return -z3__();
	case '+':
		next__();
		return z3__();
	}
	throw "错遇";
}

} /* namespace eval */
