/*
 * attr.h
 *
 *  Created on: 2019年1月20日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_VAR_ATTR_H_
#define SEGM_VAR_ATTR_H_

#include "base.h"

namespace segm {
namespace var {
namespace attr {

class Item : Base {
private:
	std::string s_;
public:
	Item(Tag_List &tags) {
		tags_ = std::move(tags);
	}

	std::string s__();
	std::string str__() {return s__();}

	static segm::Item* mk__(const std::string &name, bool use_en, Tag_List& tags);
	static bool mk_s__(const std::string &name, bool use_en, std::string &ret);
	static bool z2__(const std::string &s, Qv *qv2, const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);
	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);
};

}}} /* namespace segm */

#endif /* SEGM_VAR_ATTR_H_ */
