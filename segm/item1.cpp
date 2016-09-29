/*
 * item1.cpp
 *
 *  Created on: 2016年9月11日
 *      Author: zzzzzzzzzzz
 */

#include "item1.h"

namespace segm {

Result2 Item1::z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
	switch(*kw_) {
	case keyword::Id::Dunhao:
		ret.one__(false);
		ret.push2__(1);
		break;
	case keyword::Id::Lf : ret.push__("\n"); break;
	case keyword::Id::Cr : ret.push__("\r"); break;
	case keyword::Id::Tab: ret.push__("\t"); break;
	case keyword::Id::Esc: ret.push__("\x1b"); break;
	case keyword::Id::Maohao:
	{
		int debug_liucheng = 1;
	}
	default: break;
	}
	return Ok(true);
}

} /* namespace segm */
