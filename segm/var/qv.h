/*
 * qv.h
 *
 *  Created on: 2017年3月21日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_VAR_QV_H_
#define SEGM_VAR_QV_H_

#include "base.h"

namespace segm {
namespace var {
namespace qv {

class Item : Base {
public:
	Item(Tag_List &tags) {
		tags_ = std::move(tags);
	}

	std::string s__();
	std::string str__() {return s__();}

	static segm::Item* mk__(const std::string &name, bool use_en, Tag_List& tags);
	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);
};

}}} /* namespace segm */

#endif /* SEGM_VAR_QV_H_ */
