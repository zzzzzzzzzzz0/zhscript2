/*
 * base.h
 *
 *  Created on: 2016年9月10日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_FOR_BASE_H_
#define SEGM_FOR_BASE_H_

#include "../all.h"

namespace segm {
namespace for_ {

class Base : segm::Item {
private:
	All a_;

	size_t count_ = std::string::npos;
	std::string name_;
	bool has_fix_ = false;
	void mk_name_count__(Ret &ret2);
	virtual bool use_count__() {return true;}
protected:
	bool is__(int i, Result2 r2) {
		return r2->val_->val_ == i && (r2->val_->err_.empty() || r2->val_->err_ == name_);
	}
	virtual Result2 z_2__(segm::Item* item, Qv &qv, List &ls, Ret &ret);
public:
	All* a__() {return &a_;}

	void alt__(segm::Item *&item);
	Result2 z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret);
};

}} /* namespace segm */

#endif /* SEGM_FOR_BASE_H_ */
