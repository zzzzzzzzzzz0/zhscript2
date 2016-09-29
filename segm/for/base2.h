/*
 * base2.h
 *
 *  Created on: 2016年9月10日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_FOR_BASE2_H_
#define SEGM_FOR_BASE2_H_

#include "../all.h"

namespace segm {
namespace for_ {

class Base2 : segm::Item {
private:
	All a_;
	std::string name_;
	bool has_fix_ = false;
protected:
	virtual int is__() = 0;
public:
	All* a__() {return &a_;}
	void alt__(segm::Item *&item);

	Result2 z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret);
};

}} /* namespace segm */

#endif /* SEGM_FOR_BASE2_H_ */
