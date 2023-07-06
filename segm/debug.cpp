/*
 * debug.cpp
 *
 *  Created on: 2017年11月5日
 *      Author: zzzzzzzzzzz
 */

#include "debug.h"

namespace segm {

void Debug::head__(int lvl, size_t lvl2, int i3) {
	for(int i = 1; i <= lvl; i++) {
		bool eot = (lvl2 >> i) % 2, is = i == lvl;
		o__(0, eot ? (is ? (i3 == 1 ? '\\' : 'o') : ' ') : '|');
		for(int i2 = 0; i2 < 3; i2++) {
			o__(0, is ? '-' : ' ');
		}
	}
}

void Debug::ptree__(const segm::All* a2, int lvl, size_t lvl2, const char c) {
	if(!a2)
		return;

	const segm::All_List& a = a2->a__();
	size_t end = a.size() - 1;
	size_t i2 = 0;
	size_t lvl3;
	auto fn = [&](const std::string &s, int i3) {
		o_begin__(c);
		head__(lvl, lvl3, i3);
		o__(0, s);
		o_end__(c);
		o_n__();
	};
	for(auto i : a) {
		lvl3 = lvl2 + (i2 == end ? 1 << lvl : 0);
		fn(i->s__(), 1);
		int lvl1 = lvl + 1;
		ptree__(i->a__(), lvl1, lvl3, c);
		if(i->a2__()) {
			fn(i->kw2__(), 2);
			ptree__(i->a2__(), lvl1, lvl3, c);
		}
		if(i->a3__()) {
			fn(i->kw3__(), 3);
			ptree__(i->a3__(), lvl1, lvl3, c);
		}
		i2++;
	}
}

Debug debug2_;

} /* namespace segm */
