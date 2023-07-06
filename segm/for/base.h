/*
 * base.h
 *
 *  Created on: 2016年9月10日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_FOR_BASE_H_
#define SEGM_FOR_BASE_H_

#include "../all.h"

namespace segm {
namespace for_ {

class Base : segm::Item {
private:
	size_t count_ = std::string::npos;
	std::string name_;
	bool has_fix_ = false;
	bool count_fix_ = true, name_fix_ = true;
	size_t count_i_ = std::string::npos, name_i_ = std::string::npos;
	bool use2__() {return count_i_ != std::string::npos || name_i_ != std::string::npos;}
	void mk_name_count__(Ret &ret2, std::string &name1, size_t &count1);
	virtual bool use_count__() {return true;}
protected:
	All a_;

	size_t from_ = std::string::npos;
	bool is__(int i, const std::string &name1, Result2 r2) {
		return r2->val_.val_ == i && (r2->val2_.empty() || r2->val2_ == name1);
	}
	virtual Result2 z_2__(const std::string &name1, size_t count1, KwBy& kw_by, Qv *qv, List &ls, Ret &ret);
public:
	All* a__() {return &a_;}

	const keyword::List *end_kw_2__() {return nullptr;}
	Result2 alt__(segm::Item *&item, bool use_en);
	Result2 z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);
};

}} /* namespace segm */

#endif /* SEGM_FOR_BASE_H_ */
