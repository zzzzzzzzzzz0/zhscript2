/*
 * item.cpp
 *
 *  Created on: 2016年8月20日
 *      Author: zzzzzzzzzzz
 */

#include "item.h"

namespace segm {

std::string item2str__(Item* item);
std::string Item::str__()  {
	 return item2str__(this);
}

bool for_kwby__(const KwBy& kw_by, std::function<bool(const keyword::Item&)> fn) {
	for(const KwBy* i = &kw_by; i; i = i->up_) {
		if(fn(i->kw_))
			return true;
		switch(i->kw_) {
		case keyword::Id::For:
		case keyword::Id::Begin:
			continue;
		default: break;
		}
		break;
	}
	return false;
}

} /* namespace segm */
