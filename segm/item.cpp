/*
 * item.cpp
 *
 *  Created on: 2016年8月20日
 *      Author: zzzzzzzzzzz
 */

#include "item.h"

namespace segm {

std::string item2str__(Item* item);
std::string Item::str__()  {
	 return item2str__(this);
}

} /* namespace segm */
