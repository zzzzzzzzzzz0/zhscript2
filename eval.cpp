/*
 * eval.cpp
 *
 *  Created on: 2016年8月25日
 *      Author: zzzzzzzzzzz
 */

#include <iostream>
#include "eval.h"

namespace eval {

List::~List() {
	for(auto i : a_) {
		delete i;
	}
}

void List::pn__() {
	std::cout << std::endl;
	for(auto i : a_) {
		std::cout << "Item { val: ";
		switch(i->typ_) {
		case Typ::N:
			std::cout << i->val_;
			break;
		case Typ::O:
			std::cout << "'" << i->val2_ << "'";
			break;
		}
		std::cout << " }" << std::endl;
	}
}

Result2* List::parse__(const std::string& s) {
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

void List::z5__(char o, long double val, long double& ret) {
	switch(o) {
	case '*': ret *= val; break;
	case '/': ret /= val; break;
	case '%': ret = (long long)ret % (long long)val; break;
	case '^': {
		long double f = ret;
		size_t max = val;
		for(size_t i = 1; i < max; i++) {
			ret *= f;
		}
		break;
	}
	case '-': ret -= val; break;
	default: ret += val; break;
	}
}
void List::z4__(Item* i, size_t& ii, char& o, long double& ret) {
	switch(i->typ_) {
	case Typ::O:
		switch(i->val2_) {
		case '(': {
			long double ret2 = 0;
			ii += 1;
			z2__(')', ii, ret2);
			z5__(o, ret2, ret);
			break;
		}
		default:
			o = i->val2_;
			break;
		}
		break;
	case Typ::N: {
		switch(o) {
		case '*': case '/':
			z5__(o, i->val_, ret);
			break;
		default: {
			long double ret2 = i->val_;
			ii += 1;
			z2__('+', ii, ret2);
			z5__(o, ret2, ret);
			break;
		}}
		break;
	}}
}
void List::z2__(char chk, size_t& ii, long double& ret) {
	char o = ' ';
	for(; ii < a_.size();) {
		Item* i = a_[ii];
		if(i->typ_ == Typ::O) {
			switch(chk) {
			case '+':
				switch(i->val2_) {
				case '+': case '-':
					ii -= 1;
					return;
				}
				break;
			case ')':
				switch(i->val2_) {
				case ')':
					return;
				}
				break;
			}
		}
		z4__(i, ii, o, ret);
		ii += 1;
	}
}

} /* namespace eval */
