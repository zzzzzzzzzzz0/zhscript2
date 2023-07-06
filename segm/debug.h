/*
 * debug.h
 *
 *  Created on: 2017年11月5日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_DEBUG_H_
#define SEGM_DEBUG_H_

#include "all.h"
#include "../debug.h"

namespace segm {

class Debug {
private:
	void head__(int lvl, size_t lvl2, int i3);
	void ptree__(const segm::All* a, int lvl, size_t lvl2, const char c);
public:
	void ptree__(const segm::All* a, bool has_cache) {ptree__(a, 0, 0, has_cache ? 'C' : 'c');}
};

extern Debug debug2_;

} /* namespace segm */

#endif /* SEGM_DEBUG_H_ */
