/*
 * load.h
 *
 *  Created on: 2016年8月28日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_LOAD_H_
#define SEGM_LOAD_H_

#include "all.h"

namespace segm {
namespace load {

class Item : segm::Item {
private:
	All a_;
protected:
	Result2 z_2__(bool src_is_file, Qv &qv, List &ls, Ret &ret);
public:
	const keyword::Item& kw__() {return keyword::LOAD;}
	All* a__() {return &a_;}

	Result2 z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {return z_2__(true, qv, ls, ret);}

	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}

Result2 load__(Ret &ret2, arg::List &args, arg::NameList *nl, All *a, const keyword::Item& kw_by, bool use_part, size_t &i2, Qv &qv, List &ls, Ret &ret);

} /* namespace segm */

#endif /* SEGM_LOAD_H_ */
