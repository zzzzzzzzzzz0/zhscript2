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
	Tag_List tags_;
public:
	Item(int i, Tag_List &tags) : i_(i), tags_(std::move(tags)) {}

	std::string s__();
	std::string str__() {return s__();}

	static segm::Item* mk__(const std::string &name, Tag_List& tags);
	static bool mk_i__(const std::string &name, int &i);
	static void z2__(int i, Qv *qv2, List &ls, Ret &ret);
	Result2 z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret);
};

}}} /* namespace segm */

#endif /* SEGM_VAR_ARG_H_ */
