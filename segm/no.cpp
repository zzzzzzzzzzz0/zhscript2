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

bool Item::sub__(const std::string& s, size_t &from, Ret &ret) {
	size_t i = val_.find(s, from);
	if(i != std::string::npos) {
		ret.push__(val_.substr(from, i - from));
		ret.dunhao__();
		from = i + s.length();
		return true;
	}
	return false;
}

const Z2_Data* Item::need_use_z2__(const KwBy& kw_by, const All* a, size_t i2, Qv *qv, Ret &ret) {
	switch(kw_by.kw_) {
	case keyword::Id::Def: case keyword::Id::VarBegin: case keyword::Id::TagBegin:
		break;
	default:
		return mk_z2data(0, a, i2, qv);
	}
	return nullptr;
}

bool Item::dunhao3__(def::Item* item, size_t i4, size_t i5, const All* a) {
	const All_List &al = a->a__();
	bool in_val = true;
	size_t i9 = 0;
	for(size_t i3 = item->back_arg_; i3 < item->dunhao3_.size(); i3++) {
		auto s = item->dunhao3_[i3];
		if(s.empty()) {
			++i9;
			if(i9 == 1 && in_val)
				continue;
			if(i9 > 1)
				in_val = false;
		}
		if(in_val) {
			size_t i6 = val_.find(s, i5);
			if(i6 != std::string::npos) {
				i5 = i6 + s.length();
				i9 = 0;
				continue;
			}
			in_val = false;
		}
		//for(bool b = true; b;) {
			if(++i4 >= al.size())
				return false;
			segm::Item* i = al[i4];
			switch(i->kw__()) {
			case keyword::Id::Juhao:
			case keyword::Id::Douhao:
				return i3 >= item->dunhao3_.size() - 1;
			case keyword::Id::Dunhao:
				if(!s.empty())
					return false;
				//b = false;
				break;
			case keyword::Id::No: {
				Item* i2 = (Item*)i;
				i5 = 0;
				size_t i7 = i3, i10 = 0;
				for(;;) {
					if(s.empty()) {
						i3 = i7;
						if(++i10 > 1) {
							break;
						}
					} else
						i10 = 0;
					if(i10 == 0) {
						size_t i6 = i2->val_.find(s, i5);
						if(i6 != std::string::npos) {
							i5 = i6 + s.length();
							i3 = i7;
							//b = false;
						} else
							break;
					}
					if(++i7 >= item->dunhao3_.size()) {
						//break;
						return true;
					}
					s = item->dunhao3_[i7];
				}
				break; }
			default: break;
			}
		//}
	}
	return true;
}

const Z2_Data* Item::mk_z2data(size_t from, const All* a, size_t i2, Qv *qv) {
	Z2_Data* zd = nullptr;
	size_t len;
	for(size_t i = from; i < val_.size(); i++) {
		if(qv->for_def__([&](def::Item* item) {
			if(startswith__(val_, i, item->name2_, len)) {
				//if(debug_.o_liucheng_) o__('d', item->name2_);
				bool ok = true;
				if(item->dunhao3_.size()) {
					ok = dunhao3__(item, i2, i + len, a);
				}
				if(!ok)
					return false;
				zd = new Z2_Data{i, i + len, from, item};
				return true;
			}
			return false;
		}))
			break;
	}
	return zd;
}

Result2 Item::z2__(const Z2_Data* zd, All* a, size_t &i2, const size_t *end, const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	def::Item* di = zd->di_;
	arg::List args;
	full_args__(di, kw_by, args);
	Ret ret2;
	auto zd_i_from_app = [&]() {
		if(zd->i_ > zd->from_) {
			ret.push__(val_.substr(zd->from_, zd->i_ - zd->from_));
		}
	};
	if(di->argc_ == 0) {
		a = nullptr;
		args.src_ = di->val_;
		zd_i_from_app();
	} else {
		full_ret2__(di, ret2);
		if(di->back_arg_ > 0) {
			ret.one__();
		}
		zd_i_from_app();
		if(di->back_arg_ > 0) {
			ret.one__();
			size_t i = 0;
			if(ret.a_.size() < di->back_arg_) {
				for(; i < di->back_arg_ - ret.a_.size(); i++)
					ret2.a_.insert(ret2.a_.begin() + 1, Ret_Item {});
			}
			for(; i < di->back_arg_; i++) {
				ret2.a_.insert(ret2.a_.begin() + 1, ret.a_[ret.a_.size() - 1]);
				ret.a_.pop_back();
			}
			ret.back__(1);
		}
		bool b2 = true;
		if(zd->i2_ < val_.size()) {
			const Z2_Data* zd2 = mk_z2data(zd->i2_, a, i2, qv);
			if(zd2) {
				Result2 r2 = z2__(zd2, a, i2, end, kw_by, qv, ls, ret2);
				delete zd2;
				if(false__(r2)) return r2;
				b2 = false;
			}
		}
		size_t i = zd->i2_;
		if(di->dunhao3_.size()) {
			size_t i9 = 0;
			for(size_t i3 = di->back_arg_; i3 < di->dunhao3_.size(); i3++) {
				auto s = di->dunhao3_[i3];
				if(s.empty()) {
					++i9;
					if(i9 > 1)
						break;
					continue;
				}
				size_t i4 = val_.find(s, i);
				if(i4 == std::string::npos)
					break;
				ret2.push__(val_.substr(i, i4 - i));
				ret2.one__();
				i = i4 + s.length();
				i9 = 0;
			}
		}
		if(b2) {
			if(i < val_.size()) {
				ret2.push__(val_.substr(i));
			}
		}
		i2++;
	}
	//简省先了就在 argc_max
	Result2 r2;
	{
		KwBy kw_by2 {kw__(), a, &kw_by};
		r2 = load__(ret2, args, a, kw_by2, qv, ls, ret, i2, end, true, true, di->argc_ - di->back_arg_, &di->dunhao3_, di->is_through_);
	}
	if(di->argc_ == 0) {
		if(zd->i2_ < val_.size()) {
			const Z2_Data* zd2 = mk_z2data(zd->i2_, a, i2, qv);
			if(zd2) {
				r2 = z2__(zd2, a, i2, end, kw_by, qv, ls, ret);
				delete zd2;
			} else
				ret.push__(val_.substr(zd->i2_));
		}
	}
	return r2;
}

}} /* namespace segm */
