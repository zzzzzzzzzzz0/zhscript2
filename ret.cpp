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

void Ret::push__(Typ2 typ2, Sptr_ val2) {
	buf_.typ2_ = typ2;
	buf_.val2_ = val2;
	has_push_ = true;
}

void Ret::push__(const Tag_List &tags) {
	for(const std::string &s : tags) {
		push_tag__(s);
	}
}

void Ret::push__(const arg::Item &i) {
	push__(i.val_);
	push__(i.tags_);
}

void Ret::push2__(int i) {
	if(i == 1 && has_push2_ == -1) {
		clear_push2__();
		return;
	}
	has_push2_ = i;
}

void Ret::push__(Ret &s, size_t from, size_t to) {
	s.one__();
	bool one = false;
	for(size_t i2 = from; i2 <= to && i2 < s.a_.size(); ++i2) {
		auto i = s.a_[i2];
		if(i2 == from) {
			if(buf_.typ2_ == Typ2::No) {
				push__(i.val_);
				push__(i.typ2_, i.val2_);
				continue;
			}
		}
		if(!one) {
			one = true;
			one__();
		}
		a_.push_back(std::move(i));
	}
}

void Ret::one__(bool auto1, Ret* s) {
	if(has_push_ || has_push2_ > 0 || (!auto1 && has_push2_ >= 0)) {
		(s ? s : this)->a_.push_back(std::move(buf_));
		buf_.typ2_ = Typ2::No;
		has_push_ = false;
		clear_push2__();
	}
}

void Ret::back__(size_t hold) {
	size_t i = a_.size();
	if(i > hold) {
		Ret_Item& ri = a_[--i];
		buf_.val_ = ri.val_ + buf_.val_;
		buf_.typ2_ = ri.typ2_;
		buf_.val2_ = ri.val2_;
		a_.pop_back();
	}
}
