/*
 * exit.cpp
 *
 *  Created on: 2016年10月24日
 *      Author: zzzzzzzzzzz
 */

#include "exit.h"
#include "../util.h"

namespace segm {
namespace exit {

using on_exit___ = void (*)(const char *name);
static on_exit___ on_exit_ = nullptr;
extern "C" void l4_on_exit__(on_exit___ p) {on_exit_ = p;}

void Item::z_2__(const std::string &name, const KwBy& kw_by, List &ls, bool &is_true) {
	if(name.empty()) {
		ls.is_exit_ = true;
		ls.exit_code_ = 0;
		is_true = false;
	} else if(can_stoi__(name)) {
		ls.is_exit_ = true;
		ls.exit_code_ = std::stoi(name);
		is_true = false;
	}
	if(on_exit_)
		on_exit_(name.c_str());
}

}} /* namespace segm */
