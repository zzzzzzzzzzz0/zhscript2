/*
 * dl.h
 *
 *  Created on: 2016年9月13日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_DL_H_
#define SEGM_DL_H_

#include "all.h"

namespace segm {
namespace dl {

class Info : public Sptr {
public:
	void *handle_ = nullptr;
	Info(void *handle) : handle_(handle) {}
	~Info() {free__();}
	void free__();
};

class Item : segm::Item {
private:
	All a_;
public:
	const keyword::Item& kw__() {return keyword::DL;}
	All* a__() {return &a_;}

	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);

	static segm::Item *new__() {return (segm::Item*)new Item();}
};

}} /* namespace segm */

#endif /* SEGM_DL_H_ */
