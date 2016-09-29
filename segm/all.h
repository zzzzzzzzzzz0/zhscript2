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

using All_List = std::vector<Item*>;

class All {
private:
	All_List a_;
public:
	virtual ~All();
	const All_List& a__() const {return a_;}

	void push__(Item* i) {a_.push_back(i);}

	Result2 z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret);
	Result2 z2__(const keyword::Item& kw_by, bool use_part, size_t &i2, Qv &qv, List &ls, Ret &ret);
};

bool can_cache__(All* a, bool in_var, std::string &s, Tag_List& tags, size_t to = std::string::npos, bool in_tag = false);
std::string item2str__(Item* item);

using Is_my_tag = std::function<bool(const std::string&)>;
int qv4tags__(const std::string& s2, List& ls, ModList* mods, Is_my_tag is_my_tag, Qv *&qv2);
Result2 qv4tags__(const Tag_List& tags, List &ls, ModList* mods, Is_my_tag is_my_tag, Qv *&qv2);

} /* namespace segm */

#endif /* SEGM_ALL_H_ */
