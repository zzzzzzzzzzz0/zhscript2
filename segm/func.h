/*
 * func.h
 *
 *  Created on: 2016年9月13日
 *      Author: zzzzzzzzzzz
 */

#ifndef SEGM_FUNC_H_
#define SEGM_FUNC_H_

#include "set.h"
#include "func/param.h"

namespace segm {
namespace func {

using VV = void(*)();
using UV = param::Item2(*)();
using VA = void(*)(...);
using UA = param::Item2(*)(...);

using ParamList = std::vector<param::Item*>;

class Info : public Sptr {
public:
	void *addr_ = nullptr;
	param::Typ ret_ = param::Typ::Void;
	ParamList params_;

	Result2 parse2__(const std::string &s, param::Typ *ret, ParamList &params);
	Result2 parse__(const std::string &s) {return parse2__(s, &ret_, params_);}
	void push__(param::Typ typ, ParamList& params) {params.push_back(new param::Item(typ));}
	void push__(param::Typ typ) {push__(typ, params_);}
	void push__(param::Item2 i, ParamList& params) {params.push_back((param::Item*)new param::UIntValItem(i));}
	void push__(param::Item2 i) {push__(i, params_);}
	static int i__(const std::string &s2);
	static int no_;
};

class Item : set::Item {
private:
	Result2 z_2__(Ret &ret2, Ret &ret3, const KwBy& kw_by, Qv *qv, List &ls, Ret &ret);
public:
	const keyword::Item& kw__() {return keyword::FUNC;}
	static void* saddr__(const std::string &fname);
	static segm::Item *new__() {return (segm::Item*)new Item();}
	static Result2 set__(const std::string& name, Sptr_ info, bool is_priv, Qv *qv2, Ret &ret);
};

}} /* namespace segm */

#endif /* SEGM_FUNC_H_ */
