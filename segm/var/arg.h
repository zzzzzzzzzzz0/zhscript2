/*
 * arg.h
 *
 *  Created on: 2016年9月1日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_VAR_ARG_H_
#define SEGM_VAR_ARG_H_

#include "base.h"

namespace segm {
namespace var {
namespace arg {

class Item : Base {
private:
	int i_;
	bool is_test_;
public:
	Item(int i, Tag_List &tags, bool is_test) : i_(i), is_test_(is_test) {
		tags_ = std::move(tags);
	}

	std::string s__();
	std::string str__() {return s__();}

	static segm::Item* mk__(const std::string &name, bool use_en, Tag_List& tags, bool is_test);
	static bool mk_i__(const std::string &name, bool use_en, int &i);
	static void z2__(int i, std::function<const char*(const std::string&)> fn_val, Qv *qv2, List &ls, Ret &ret);
	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);
};

}}} /* namespace segm */

#endif /* SEGM_VAR_ARG_H_ */
