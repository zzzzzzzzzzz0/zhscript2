/*
 * Print.cpp
 *
 *  Created on: 2016年8月19日
 *      Author: zzzzzzzzzzz
 */

#include <iostream>
#include "print.h"

namespace segm {
namespace print {

Result2 Item::z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
	Ret ret2;
	{
		Result2 r2 = a_.z__(kw__(), qv, ls, ret2);
		if(false__(r2))
			return r2;
	}
	ret2.one__();
	for(auto s : ret2.a_) {
		std::cout << s.val_;
		switch(kw_by) {
		case keyword::Id::Print:
		case keyword::Id::Exec:
		case keyword::Id::Set:
		case keyword::Id::Equ:
			ret.push__(s.val_);
			break;
		default:
			break;
		}
	}
	return Ok(true);
}

}} /* namespace segm */
