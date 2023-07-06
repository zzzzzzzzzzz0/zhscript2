/*
 * reserved.h
 *
 *  Created on: 2016年11月12日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_VAR_RESERVED_H_
#define SEGM_VAR_RESERVED_H_

#include "base.h"

namespace segm {
namespace var {
namespace reserved {

class Item : Base {
private:
	int i_;
	bool is_en_;
	static size_t len__();
public:
	Item(int i, bool is_en) : i_(i), is_en_(is_en) {}

	std::string s__();
	std::string str__() {return s__();}

	static segm::Item* mk__(const std::string &name, Tag_List& tags);
	static bool mk_i__(const std::string &name, int &i, bool &is_en);
	static void z2__(int i, bool is_en, Qv *qv2, List &ls, Ret &ret);
	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);
};

}}} /* namespace segm */

#endif /* SEGM_VAR_RESERVED_H_ */
