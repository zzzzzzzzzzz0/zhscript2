/*
 * def.h
 *
 *  Created on: 2016年9月3日
 *      Author: zzzzzzzzzzz
 */

#ifndef DEF_H_
#define DEF_H_

#include "var.h"

namespace def {

class Item : public var::Item {
public:
	bool is_no_arg_ = false;
	size_t qian_arg_ = 0;
	arg::NameList arg_names_;
};

class List : public var::List {
};

} /* namespace def */

#endif /* DEF_H_ */
