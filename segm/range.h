/*
 * for.h
 *
 *  Created on: 2016年8月26日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_RANGE_H_
#define SEGM_RANGE_H_

#include "for/base.h"

namespace segm {
namespace range {

class Item : for_::Base {
private:
	bool use_count__() {return false;}
	Result2 z_2__(segm::Item* item, Qv &qv, List &ls, Ret &ret) {
		for(;;) {
			Result2 r2 = item->z__(kw__(), qv, ls, ret);
			if(is__(IS_BREAK2, r2))
				break;
			if(is__(IS_CONTINUE2, r2))
				continue;
			if(false__(r2))
				return r2;
			break;
		}
		return Ok(true);
	}
public:
	const keyword::Item& kw__() {return keyword::RANGE;}
	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_FOR_H_ */
