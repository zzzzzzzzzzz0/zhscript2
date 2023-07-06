/*
 * Equname.cpp
 *
 *  Created on: 2021年2月4日
 *      Author: zzzzzzzzzzz
 */

#include "equname.h"
#include "ret.h"

bool Equ_name::equ__(const std::string& s, const std::string& name, Ret &ret) const {
	if(equ_ && is__(s)) {
		ret.push__(name);
		return true;
	}
	return false;
}

bool Equ_name::is__(const std::string& s) {
	return s == "-" || s == "true";
}
