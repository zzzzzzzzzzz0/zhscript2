/*
 * var.h
 *
 *  Created on: 2016年8月29日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_VAR_H_
#define SEGM_VAR_H_

#include "var/base.h"

namespace segm {
namespace var {

class Item : Base {
private:
	All a_;
protected:
	virtual bool is_test() {return false;}
public:
	All* a__() {return &a_;}

	bool can_up__() {return false;}
	Result2 alt__(segm::Item *&item, bool use_en) {return alt2__(item, use_en, false);}
	Result2 alt2__(segm::Item *&item, bool use_en, bool is_test);
	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);
	static Result2 z_2__(const Ret_List &rl, bool is_test, bool also_val, bool use_up, const char* val2, const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);

	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_VAR_H_ */
