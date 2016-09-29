/*
 * no.cpp
 *
 *  Created on: 2016年8月22日
 *      Author: zzzzzzzzzzz
 */

#include "no.h"
#include "load.h"
#include "../util.h"
#include "../debug.h"

namespace segm {
namespace no {

const Z2_Data* Item::need_use_z2(const keyword::Item& kw_by, Qv &qv) {
	Z2_Data* zd = nullptr;
	switch(kw_by) {
	case keyword::Id::Def: case keyword::Id::VarBegin: case keyword::Id::TagBegin:
		break;
	default:
		size_t i2;
		for(size_t i = 0; i < val_.size(); i++) {
			if(qv.for_def__([&](def::Item* item) {
				if(startswith__(val_, i, item->name_, i2)) {
					if(debug_.o_liucheng_) o__({item->name_}, 'd');
					zd = static_cast<Z2_Data*>(std::make_shared<Z2_Data>(i, i + i2, item).get());
					return true;
				}
				return false;
			}))
				break;
		}
		break;
	}
	return zd;
}
Result2 Item::z2__(const Z2_Data* zd, All* a, size_t &i2, Qv &qv, List &ls, Ret &ret) {
	Ret ret2;
	arg::List args;
	args.src_is_file_ = false;
	def::Item* di = (def::Item*)zd->v_;
	ret2.push__(di->val_);
	ret2.one__();
	args.src2_ = di->name_;
	if(di->is_no_arg_) {
		a = nullptr;
		if(zd->i_ > 0) {
			ret.push__(val_.substr(0, zd->i_));
		}
	} else {
		if(zd->i_ > 0) {
			ret.push__(val_.substr(0, zd->i_));
			ret.one__();
		}
		if(di->qian_arg_ > 0) {
			if(ret.a_.size() < di->qian_arg_) {
				return err__('<');
			}
			for(size_t i = 0; i < di->qian_arg_; i++) {
				ret2.a_.insert(ret2.a_.begin() + 1, ret.a_[ret.a_.size() - 1]);
				ret.a_.pop_back();
			}
		}
		if(zd->i2_ < val_.size()) {
			ret2.push__(val_.substr(zd->i2_));
		}
		i2++;
	}
	Result2 r2 = load__(ret2, args, &di->arg_names_, a, keyword::DEF, true, i2, qv, ls, ret);
	if(di->is_no_arg_) {
		if(zd->i2_ < val_.size()) {
			ret.push__(val_.substr(zd->i2_));
		}
	}
	return r2;
}

}} /* namespace segm */
