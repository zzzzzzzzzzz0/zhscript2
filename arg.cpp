/*
 * arg.cpp
 *
 *  Created on: 2016年8月23日
 *      Author: zzzzzzzzzzz
 */

#include "arg.h"

namespace arg {

void List::parse__(const std::string& s) {
	if(s.length() >= 1 && s[0] == '-') {
		push__(s);
		return;
	}
	if(src_.empty()) {
		src_ = s;
		return;
	}
	push__(s);
}

void List::push__(const std::string& s) {
	a_.push_back(std::make_shared<Item>(Item {val_:s}));
}

const std::string& List::all__() {
	if(!has_mk_all_) {
		all_ = mk_all__(a_, 0, a_.size() - 1);
		has_mk_all_ = true;
	}
	return all_;
}

std::string List::mk_all__(List_List a, size_t from, size_t to) {
	std::string all;
	size_t len = a.size();
	if(len > 0) {
		if(to >= len)
			to = len - 1;
		for(size_t i2 = from; i2 <= to; i2++) {
			auto i = a[i2];
			if(i2 > from)
				all += ' ';
			std::string s;
			bool b = false;
			for(auto r : i->val_) {
				if(!b) {
					if(!(	(r >= '0' && r <= '9') ||
							(r >= 'a' && r <= 'z') ||
							(r >= 'A' && r <= 'Z') ||
							r == '.' || r == '-' || r == '_')) {
						b = true;
						s = '"' + s;
					}
				}
				if(r == '"')
					s += '\\';
				s += r;
			}
			if(b)
				s += '"';
			all += s.empty() ? R"("")" : s;
		}
	}
	return all;
}

} /* namespace arg */
