/*
 * Equname.h
 *
 *  Created on: 2021年2月4日
 *      Author: zzzzzzzzzzz
 */

#ifndef EQUNAME_H_
#define EQUNAME_H_

#include <string>
class Ret;

class Equ_name {
public:
	bool equ_;
	bool equ__(const std::string& s, const std::string& name, Ret &ret) const;
	static bool is__(const std::string& s);
};

#endif /* EQUNAME_H_ */
