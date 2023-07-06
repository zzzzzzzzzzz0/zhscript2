/*
 * args.h
 *
 *  Created on: 2016年9月7日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_VAR_ARGS_H_
#define SEGM_VAR_ARGS_H_

#include "base.h"

namespace segm {
namespace var {
namespace args {

class Item : Base {
private:
	int i_, i2_;
	bool is_test_;
public:
	Item(int i, int i2, Tag_List &tags, bool is_test) : i_(i), i2_(i2), is_test_(is_test) {
		tags_ = std::move(tags);
	}

	std::string s__();
	std::string str__() {return s__();}

	static segm::Item* mk__(const std::string &name, bool use_en, Tag_List& tags, bool is_test);
	static bool mk_i__(const std::string &name, bool use_en, int &i, int &i2);
	static void z2__(int i, int i2, const KwBy& kw_by, Qv *qv2, List &ls, Ret &ret);
	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);

	static int stoi__(const std::string &s);
	std::string itos__(int i);
};

}}} /* namespace segm */

#endif /* SEGM_VAR_ARGS_H_ */
