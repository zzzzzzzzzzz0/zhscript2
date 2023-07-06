/*
 * base2.h
 *
 *  Created on: 2016年9月10日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_FOR_BASE2_H_
#define SEGM_FOR_BASE2_H_

#include "../all.h"
#include "../../is.h"

namespace segm {
namespace for_ {

class Base2 : segm::Item {
protected:
	All a_;
	std::string name_;
	bool has_fix_ = false;
	virtual int is__() = 0;
	virtual const keyword::Item& for__() = 0;
	virtual void z_2__(const std::string &name, const KwBy& kw_by, List &ls, bool &is_true);
public:
	All* a__() {return &a_;}
	Result2 alt__(segm::Item *&item, bool use_en);
	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);
	void fix_name__(const char* name) {
		name_ = name;
		has_fix_ = true;
	}
};

}} /* namespace segm */

#endif /* SEGM_FOR_BASE2_H_ */
