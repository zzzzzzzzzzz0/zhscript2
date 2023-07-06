/*
 * clpars.h
 *
 *  Created on: 2017年6月14日
 *      Author: zzzzzzzzzzz
 */

#ifndef CLPARS_H_
#define CLPARS_H_

#include <string>
#include "arg.h"

class Clpars {
private:
	bool all_is_param_ = false;
public:
	void z__(int argc, const char** argv, int from, arg::List& args);
	void z__(const std::string& s, arg::List& args);
	void z2__(const std::string& s, arg::List& args);
};

#endif /* CLPARS_H_ */
