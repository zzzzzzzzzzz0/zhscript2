/*
 * if.cpp
 *
 *  Created on: 2016年9月11日
 *      Author: zzzzzzzzzzz
 */

#include "if.h"
#include "item1.h"
#include "../debug.h"

namespace segm {
namespace if_ {

bool Item::continue1__(keyword::Id ret_kw) {
	const keyword::Item* kw = keyword::has__(ret_kw, ret_kw__());
	if(!kw)
		return false;
	a_.push__((Item*)new Item1(kw));
	return true;
}

bool logic__(std::string &left_val, std::string &val, bool &is_left, bool &has_val, keyword::Id kw2, keyword::Id &kw, bool &is_not, bool &result) {
	bool ret = true, clear1 = true, need_bool = false;
	auto fn = [&](bool xiaoyu, bool dengyu, bool dayu) {
		bool first = true, is_num = false;
		int num1_len = 0, num2_len = 0;
		auto is___num = [&](size_t len1, size_t len2) -> int {
			std::string d1 = left_val.substr(0, len1);
			std::string d2 =      val.substr(0, len2);
			long double d = std::stold(d1) - std::stold(d2), d3 = 0.000001;
			if(debug_.o_if_) {
				o__({d1, std::string("-"), d2, std::string("="), std::to_string(d)}, 'x'); o_n__();
			}
			if(d >= -d3 && d <= d3)
				return 0;
			else if(d < d3)
				return -1;
			else
				return 1;
		};
		auto is__num = [&]() {
			switch(is___num(left_val.size(), val.size())) {
			case  0: result = dengyu; break;
			case -1: result = xiaoyu; break;
			case  1: result = dayu; break;
			}
		};
		for(size_t i = 0;; i++) {
			bool b = i >= val.size();
			if(i >= left_val.size()) {
				if(is_num)
					is__num();
				else {
					if(b) {
						result = dengyu;
					} else {
						result = xiaoyu;
					}
				}
				return;
			}
			if(b) {
				if(is_num)
					is__num();
				else
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
				bool is_num1 = true, is_num2 = true;
				if(std::isdigit(c1)) {
					if(c1 == '0' && num1_len == 0);
					else
						num1_len++;
				} else
					is_num1 = false;
				if(std::isdigit(c2)) {
					if(c2 == '0' && num2_len == 0);
					else
						num2_len++;
				} else
					is_num2 = false;
				if(is_num1 && is_num2)
					continue;
				if(!is_num1 && !is_num2) {
					if(num1_len == num2_len) {
						if(num1_len > 0) {
							switch(is___num(i, i)) {
							case  0:
								is_num = false;
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
				} else if(is_num1) {
					result = dayu;
					return;
				} else {
					result = xiaoyu;
					return;
				}

			}
			if(c1 < c2) {
				result = xiaoyu;
				return;
			}
			if(c1 > c2) {
				result = dayu;
				return;
			}
		}
	};
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
		clear1 = false;
		break;
	}
	if(debug_.o_if_ && clear1) {
		o__({std::to_string(result), keyword::MAOHAO.val_, left_val, keyword::has__(kw, &keyword::ALL_IF)->val_, val}, 'x');
		o_n__();
	}
	switch(kw2) {
	case keyword::Id::And:
	case keyword::Id::Or:
	case keyword::Id::No:
		if(kw == keyword::NO)
			need_bool = true;
		kw = keyword::NO;
		break;
	default:
		break;
	}
	switch(kw2) {
	case keyword::Id::Not:
		is_not = !is_not;
		break;
	default:
		if(need_bool) {
			result = !(val.empty() || val == "0" || val == "false");
			if(debug_.o_if_) {o__({std::to_string(result), keyword::MAOHAO.val_, val}, 'x'); o_n__();}
			clear1 = true;
		}
		if(clear1) {
			if(is_not) {
				if(debug_.o_if_) {o__({keyword::NOT.val_}, 'x'); o_n__();}
				result = !result;
			}
		}
		switch(kw2) {
		case keyword::Id::And:
			ret = result;
			break;
		case keyword::Id::Or:
			ret = !result;
			break;
		case keyword::Id::No:
			break;
		default:
			kw = kw2;
			break;
		}
		if(is_left) {
			if(has_val)
				left_val = val;
			is_left = false;
		}
		val.clear();
		has_val = false;
		if(clear1) {
			is_not = false;
			is_left = true;
		}
		break;
	}
	return ret;
}

Result2 Item::z_2__(All *a, Qv &qv, List &ls, Ret &ret, bool &result) {
	std::string val, left_val;
	bool is_not = false, is_left = true, has_val = false;
	keyword::Id kw = keyword::NO;
	for(auto i : a->a__()) {
		if(keyword::has__(i->kw__(), ret_kw__())) {
			if(!logic__(left_val, val, is_left, has_val, i->kw__(), kw, is_not, result))
				return Ok(true);
		} else if(i->kw__() == keyword::BEGIN) {
			Result2 r2 = z_2__(i->a__(), qv, ls, ret, result);
			if(false__(r2))
				return r2;
		} else {
			Ret ret2;
			{
				Result2 r2 = i->z__(kw__(), qv, ls, ret2);
				if(false__(r2))
					return r2;
			}
			ret2.one__();
			for(auto s : ret2.a_) {
				val += s.val_;
			}
			has_val = true;
		}
	}
	logic__(left_val, val, is_left, has_val, keyword::NO, kw, is_not, result);
	return Ok(true);
}

Result2 Item::z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
	bool result = false;
	{
		Result2 r2 = z_2__(&a_, qv, ls, ret, result);
		if(false__(r2))
			return r2;
	}
	if(debug_.o_if_) {o__({std::to_string(result)}, 'x'); o_n__();}
	if(result) {
		Result2 r2 = a2_.z__(kw__(), qv, ls, ret);
		if(false__(r2))
			return r2;
	} else {
		Result2 r2 = a3_.z__(kw__(), qv, ls, ret);
		if(false__(r2))
			return r2;
	}
	return Ok(true);
}

}} /* namespace segm */
