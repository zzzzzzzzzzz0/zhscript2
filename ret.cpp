/*
 * Ret.cpp
 *
 *  Created on: 2016年8月19日
 *      Author: zzzzzzzzzzz
 */

#include "ret.h"

void Ret::push__(const std::string &s) {
	buf_.val_ += s;
	has_push_ = true;
}

void Ret::push__(char typ, Sptr_ val2) {
	buf_.typ_ = typ;
	buf_.val2_ = val2;
	has_push_ = true;
}

void Ret::push2__(int i) {
	if(i == 1 && has_push2_ == -1) {
		has_push2_ = 0;
		return;
	}
	has_push2_ = i;
}

void Ret::one__(bool auto1) {
	if(has_push_ || has_push2_ > 0 || (!auto1 && has_push2_ >= 0)) {
		a_.push_back(std::move(buf_));
		has_push_ = false;
		has_push2_ = 0;
	}
}
