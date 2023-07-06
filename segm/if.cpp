/*
 * if.cpp
 *
 *  Created on: 2016年9月11日
 *      Author: zzzzzzzzzzz
 */

#include "if.h"
#include "../util.h"
#include "../debug.h"

extern std::string null_;

namespace segm {
namespace if_ {

const keyword::List Item::power_kw_ = {
		&keyword::DENGYU, &keyword::XIAOYUDENGYU, &keyword::XIAOYU, &keyword::DAYUDENGYU, &keyword::DAYU,
		&keyword::NOT, &keyword::AND, &keyword::OR,
};

bool Item::is_kw2__(keyword::Id ret_kw) {
	return a_.push1__(ret_kw, &power_kw_);
}

bool logic__(std::string &left_val, std::string &val, bool &is_left, bool &has_val, keyword::Id kw2, keyword::Id &kw, bool &is_not, bool &result) {
	auto fn = [&](bool xiaoyu, bool dengyu, bool dayu) {
		if(can_stod__(left_val) && can_stod__(val)) {
			long double d1 = std::stold(left_val);
			long double d2 = std::stold(val);
			if(debug_.o_if_) {
				o__('x', left_val, " - ", val); o_n__();
			}
			if(d1 < d2) {
				result = xiaoyu;
				return;
			}
			if(d1 > d2) {
				result = dayu;
				return;
			}
			result = dengyu;
			return;
		}
		if(left_val < val) {
			result = xiaoyu;
			return;
		}
		if(left_val > val) {
			result = dayu;
			return;
		}
		result = dengyu;
		/*auto cmp_num = [&](size_t len1, size_t len2) -> int {
			std::string d1 = left_val.substr(0, len1);
			std::string d2 =      val.substr(0, len2);
#ifdef ver_clang_3_8_arm64_v8a_
			//Generate Signed APK...release 时减法 fatal error: error in backend: Cannot select:
			long double _d1 = std::stold(d1);
			long double _d2 = std::stold(d2);
			if(_d1 == _d2)
				return 0;
			else if(_d1 < _d2)
#else
			long double d3 = 0.000001;
			long double d = std::stold(d1) - std::stold(d2);
			if(debug_.o_if_) {
				o__('x', d1, " - ", d2, "=", d); o_n__();
			}
			if(d >= -d3 && d <= d3)
				return 0;
			else if(d < d3)
#endif
				return -1;
			else
				return 1;
		};
		bool is_num = false, is_num1 = false, is_num2 = false;
		int num1_len = 0, num2_len = 0;
		auto is__num = [&]() -> bool {
			if(!is_num || !is_num1 || !is_num2) {
				return false;
			}
			switch(cmp_num(left_val.size(), val.size())) {
			case  0: result = dengyu; break;
			case -1: result = xiaoyu; break;
			case  1: result = dayu; break;
			}
			return true;
		};
		bool first = true;
		for(size_t i = 0;; i++) {
			bool b = i >= val.size();
			if(i >= left_val.size()) {
				if(!is__num()) {
					if(b) {
						result = dengyu;
					} else {
						result = xiaoyu;
					}
				}
				return;
			}
			if(b) {
				if(!is__num())
					result = dayu;
				return;
			}
			unsigned char c1 = left_val[i], c2 = val[i];
			if(first) {
				first = false;
				bool b1 = false, b2 = false;

				if(c1 == '-' || c1 == '+') {
					is_num = true;
					b1 = true;
				} else if(std::isdigit(c1))
					is_num = true;
				if(c2 == '-' || c2 == '+') {
					is_num = true;
					b2 = true;
				} else if(std::isdigit(c2))
					is_num = true;
				if(b1 && b2)
					continue;
			}
			if(is_num) {
				if(std::isdigit(c1)) {
					if(c1 == '0' && num1_len == 0);
					else
						num1_len++;
					is_num1 = true;
				} else
					is_num1 = false;
				if(std::isdigit(c2)) {
					if(c2 == '0' && num2_len == 0);
					else
						num2_len++;
					is_num2 = true;
				} else
					is_num2 = false;
				if(is_num1 && is_num2)
					continue;
				if(!is_num1 && !is_num2) {
					if(num1_len == num2_len) {
						if(num1_len > 0) {
							switch(cmp_num(i, i)) {
							case  0:
								break;
							case -1: result = xiaoyu; return;
							case  1: result = dayu; return;
							}
						}
					} else if(num1_len > num2_len) {
						result = dayu;
						return;
					} else {
						result = xiaoyu;
						return;
					}
				}
				is_num = false;
			}
			if(c1 < c2) {
				result = xiaoyu;
				return;
			}
			if(c1 > c2) {
				result = dayu;
				return;
			}
		}*/
	};
	bool ret = true;
	switch(kw) {/*
	case keyword::Id::Dengyu:       result = left_val == val; break;
	case keyword::Id::Xiaoyudengyu: result = left_val <= val; break;
	case keyword::Id::Xiaoyu:       result = left_val <  val; break;
	case keyword::Id::Dayudengyu:   result = left_val >= val; break;
	case keyword::Id::Dayu:         result = left_val >  val; break;*/
	case keyword::Id::Dengyu:       fn(false, true , false); break;
	case keyword::Id::Xiaoyudengyu: fn(true , true , false); break;
	case keyword::Id::Xiaoyu:       fn(true , false, false); break;
	case keyword::Id::Dayudengyu:   fn(false, true , true); break;
	case keyword::Id::Dayu:         fn(false, false, true); break;
	default:
		break;
	}
	if(debug_.o_if_ && kw != keyword::NO) {
		o__('x', result, keyword::MAOHAO.val_,
				keyword::TEXT_BEGIN.val_, left_val, keyword::TEXT_END.val_,
				keyword::has__(kw, &Item::power_kw_)->val_,
				keyword::TEXT_BEGIN.val_, val, keyword::TEXT_END.val_);
		o_n__();
	}
	switch(kw2) {
	case keyword::Id::And:
	case keyword::Id::Or:
	case keyword::Id::No:
		if(debug_.o_if_) {
			switch(kw2) {
			case keyword::Id::And:
				o__('x', keyword::AND.val_);
				break;
			case keyword::Id::Or:
				o__('x', keyword::OR.val_);
				break;
			default:
				break;
			}
			o_n__();
		}
		if(kw == keyword::NO) {
			result = !(val.empty() || val == "0" || val == "false" || val == null_);
			if(debug_.o_if_) {
				o__('x', result, keyword::MAOHAO.val_, "bool", keyword::TEXT_BEGIN.val_, val, keyword::TEXT_END.val_);
				o_n__();
			}
			left_val = val;
		}
		if(is_not) {
			result = !result;
			if(debug_.o_if_) {o__('x', keyword::NOT.val_); o_n__();}
		}
		switch(kw2) {
		case keyword::Id::And:
			ret = result;
			break;
		case keyword::Id::Or:
			ret = !result;
			break;
		default:
			break;
		}
		val.clear();
		has_val = false;
		is_not = false;
		is_left = true;
		kw = keyword::NO;
		break;
	case keyword::Id::Not:
		is_not = !is_not;
		break;
	default:
		if(is_left) {
			if(has_val)
				left_val = val;
			is_left = false;
		}
		val.clear();
		has_val = false;
		kw = kw2;
		break;
	}
	return ret;
}

Result2 Item::z_2__(All *a, std::string &left_val, bool &result, KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	std::string val;
	bool is_not = false, is_left = true, has_val = false;
	keyword::Id kw = keyword::NO;
	Ret ret2;
	size_t i2 = 0;
	auto fn = [&]() {
		ret2.one__();
		if(ret2.a_.size() > 0) {
			val += ret2.a_[0].val_;
			has_val = true;
		}
		ret2.a_.clear();
	};
	bool over = false;
	Result2 r2 = a->z7__(kw_by, qv, ls, ret2, i2, nullptr, [&](Z7_data1 *data1, Result2 &r2) {
		segm::Item* i = data1->i_;
		over = false;
		if(keyword::has__(i->kw__(), &power_kw_)) {
			fn();
			if(!logic__(left_val, val, is_left, has_val, i->kw__(), kw, is_not, result)) {
				over = true;
				return -1;
			}
			return 1;
		}
		if(i->kw__() == keyword::BEGIN) {
			Ret ret3;
			r2 = z_2__(i->a__(), left_val, result, kw_by, qv, ls, ret3);
			if(false__(r2))
				return -2;
			over = true;
			val = left_val;
			return 1;
		}
		return 0;
	});
	if(false__(r2))
		return r2;
	if(!over) {
		fn();
		logic__(left_val, val, is_left, has_val, keyword::NO, kw, is_not, result);
	}
	return Ok(true);
}

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	bool result = false;
	std::string left_val;
	{
		KwBy kw_by2 {kw__(), &a_, &kw_by};
		Result2 r2 = z_2__(&a_, left_val, result, kw_by2, qv, ls, ret);
		if(false__(r2))
			return r2;
	}
	if(debug_.o_if_) {o__('x', result); o_n__();}
	if(result) {
		KwBy kw_by2 {kw__(), &a2_, &kw_by};
		Result2 r2 = a2_.z__(kw_by2, qv, ls, ret);
		if(false__(r2))
			return r2;
	} else {
		KwBy kw_by2 {kw__(), &a3_, &kw_by};
		Result2 r2 = a3_.z__(kw_by2, qv, ls, ret);
		if(false__(r2))
			return r2;
	}
	return Ok(true);
}

}} /* namespace segm */
