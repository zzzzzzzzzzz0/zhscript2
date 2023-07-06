/*
 * Print.cpp
 *
 *  Created on: 2016年8月19日
 *      Author: zzzzzzzzzzz
 */

#include <iostream>
#include "print.h"
#include "load.h"

#ifdef ver_ex_print_
void print__(const std::string &s);
#endif

namespace segm {
namespace print {

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	{
		def::Item* di;
		if(qv->for_def__([&](def::Item* i) {
			if(i->name_ == keyword::PRINT) {
				di = i;
				return true;
			}
			return false;
		})) {
			arg::List args;
			full_args__(di, kw_by, args);
			Ret ret2;
			full_ret2__(di, ret2);
			size_t i2 = 0;
			KwBy kw_by2 {kw__(), &a_, &kw_by};
			return load__(ret2, args, &a_, kw_by2, qv, ls, ret, i2, nullptr, true, true, di->argc_ - di->back_arg_, nullptr, di->is_through_);
		}
	}
	Ret ret2;
	{
		KwBy kw_by2 {kw__(), &a_, &kw_by};
		Result2 r2 = a_.z__(kw_by2, qv, ls, ret2);
		ret2.one__();
		if(false__(r2))
			return r2;
	}
	if(ret2.a_.size() > 0) {
		const std::string &s2 = ret2.a_[0].val_;
#ifdef ver_ex_print_
		print__(s2);
#else
		std::cout << s2;
#endif
		for_kwby__(kw_by, [&](const keyword::Item& kw) {
			switch(kw) {
			case keyword::Id::Print:
			case keyword::Id::Exec:
			case keyword::Id::Set:
			case keyword::Id::Equ:
			case keyword::Id::Guandaojie:
				ret.push__(s2);
				return true;
			default:
				return false;
			}
		});
	}
#ifndef ver_ex_print_
	if(ret2.a_.size() > 1) {
		std::cout.flush();
	}
#endif
	return Ok(true);
}

}} /* namespace segm */
