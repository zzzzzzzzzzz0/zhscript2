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
	bool use_en_ = false;
	size_t i2_ = 0;
protected:
	Result2 z_2__(bool src_is_file, const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);
public:
	const keyword::Item& kw__() {return keyword::LOAD;}
	All* a__() {return &a_;}

	Result2 alt__(segm::Item *&item, bool use_en);
	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {return z_2__(true, kw_by, qv, ls, ret);}

	static segm::Item *new__() {return (segm::Item*)new Item();}
	static int is_return__(Result2 r2);
};

}

Result2 load__(Ret &ret2, arg::List &args, All *a, KwBy& kw_by, Qv *qv, List &ls, Ret &ret,
		size_t &i2, const size_t *end = nullptr, bool auto1 = true, bool use_part = false, size_t argc_max = SIZE_MAX, std::vector<std::string> *dunhao3 = nullptr,
		bool is_through = false);

void full_args__(def::Item* di, const KwBy& kw_by, arg::List& args);
void full_ret2__(def::Item* di, Ret &ret2);

} /* namespace segm */

#endif /* SEGM_LOAD_H_ */
