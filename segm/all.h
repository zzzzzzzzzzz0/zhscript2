/*
 * all.h
 *
 *  Created on: 2016年8月20日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_ALL_H_
#define SEGM_ALL_H_

#include "item.h"
#include "mod.h"

namespace segm {

class IntRet : public Sptr {
public:
	long val_;
	IntRet(long val) : val_(val) {}
};
class UIntRet : public Sptr {
public:
	unsigned long val_;
	UIntRet(unsigned long val) : val_(val) {}
};

using All_List = std::vector<Item*>;

class Z7_data1 {
public:
	Item* i_;
	size_t argc_max_;
};
using Z7_fn1 = std::function<int(Z7_data1*, Result2&)>;
//using Z7_fn2 = std::function<void()>;

class All {
private:
	All_List a_;
public:
	~All();
	const All_List& a__() const {return a_;}

	void push__(Item* i) {a_.push_back(i);}
	bool push1__(keyword::Id kw, const keyword::List *all_kw = nullptr);

	Result2 z7__(KwBy& kw_by, Qv *qv, List &ls, Ret &ret, size_t &i2, const size_t *end = nullptr,
			Z7_fn1 fn1 = nullptr,
			bool use_part = false, bool use_part2 = false, size_t argc_max = SIZE_MAX,
			std::vector<std::string> *dunhao3 = nullptr);
	Result2 z__(KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
		size_t i2 = 0;
		return z7__(kw_by, qv, ls, ret, i2);
	}

	static const keyword::List var_power_kw_;
};

bool can_cache__(All* a, bool in_var, std::string &s, Tag_List& tags, size_t to = std::string::npos, bool in_tag = false);
std::string item2str__(Item* item);

using Is_my_tag = std::function<bool(const std::string&)>;
char qv4tags__(const std::string& s2, bool use_en, List& ls, ModList* mods, Is_my_tag is_my_tag, Qv **qv2);
Result2 qv4tags__(const Tag_List& tags, bool use_en, List &ls, ModList* mods, Is_my_tag is_my_tag, Qv **qv2, bool is_test = false);

Result2 mem4tags__(const All &a1, std::function<Result2(size_t, const std::string&)> fn, std::function<Result2(size_t)> fn2, size_t &ret_i2);
Result2 atoi__(const All &a, size_t i, KwBy& kw_by, Qv *qv, List &ls, std::function<Result2(const std::string&)> fn);

} /* namespace segm */

#endif /* SEGM_ALL_H_ */
