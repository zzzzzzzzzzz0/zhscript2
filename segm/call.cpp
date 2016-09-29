/*
 * call.cpp
 *
 *  Created on: 2016年9月14日
 *      Author: zzzzzzzzzzz
 */

#include "call.h"
#include "func.h"
#include "func/call.h"
#include "func/old.h"
#include "../defer.h"
#include "../util.h"

namespace segm {
namespace call {

Result2 Item::z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
	Ret ret2;
	{
		Result2 r2 = a_.z__(kw__(), qv, ls, ret2);
		if(false__(r2))
			return r2;
	}
	ret2.one__();

	const Ret_List& a = ret2.a_;
	if(a.size() < 1)
		return err__('<');
	func::Info* fi;
	{
		const Ret_Item& ri = a[0];
		if(ri.typ_ != 'f')
			return err__("非函数地址");
		fi = static_cast<func::Info*>(ri.val2_.get());
	}

	size_t siz = 2048;
	char *buf = new char[siz];
	buf[0] = 0;
	defer defer([&]() {
		delete buf;
	});
	int err_ret = 0;
	char* addr_ret = nullptr;
	func::param::CallEx ce;

	func::param::List2 params;
	{
		size_t len2 = a.size();
		size_t i2 = 1;
		size_t len = fi->params_.size();
		for(size_t ic = 0; ic < len; ic++) {
			auto i = fi->params_[ic];
			switch(i->typ_) {
			case func::param::Typ::Buf:
				params.push_back((func::param::Item2)buf);
				continue;
			case func::param::Typ::Siz:
				params.push_back((func::param::Item2)buf);
				params.push_back(siz);
				continue;
			case func::param::Typ::AddrRet:
				params.push_back((func::param::Item2)&addr_ret);
				continue;
			case func::param::Typ::Err:
				params.push_back((func::param::Item2)&err_ret);
				continue;
			case func::param::Typ::Callback:
			{
				Result2 r2 = i->z__(qv, ls, params, ce);
				if(false__(r2))
					return r2;
				continue;
			}
			case func::param::Typ::IntVal:
				params.push_back(((func::param::IntValItem*)i)->val_);
				continue;
			case func::param::Typ::UIntVal:
				params.push_back(((func::param::UIntValItem*)i)->val_);
				continue;
			case func::param::Typ::StringVal:
				params.push_back((func::param::Item2)((func::param::StringValItem*)i)->val_.c_str());
				continue;
			case func::param::Typ::Z:
				params.push_back(len2 - i2);
				for(;i2 < len2;) {
					params.push_back((func::param::Item2)a[i2++].val_.c_str());
				}
				continue;
			default:
				break;
			}

			if(i2 >= len2)
				return err__('<');
			const std::string &s = a[i2++].val_;

			switch(i->typ_) {
			case func::param::Typ::Int:
				if(!can_stoi__(s))
					return err__('x', s.c_str());
				params.push_back(std::stoul(s));
				break;
			case func::param::Typ::Char:
				if(s.size() != 1)
					return err__('x', s.c_str());
				params.push_back(s[0]);
				break;
			case func::param::Typ::Chars:
				params.push_back((func::param::Item2)s.c_str());
				break;
			default:
				break;
			}
		}
		if(i2 < len2) {
			return err__('>');
		}
	}

	bool by_ce = false;
	ce.z_ = [&](Ret &ret4) {
		by_ce = true;
	};

	func::param::Item2 ret3 = 0;
	if(!func::call__(fi, params, ret3))
		return err__('>');
	switch(fi->ret_) {
	case func::param::Typ::Int:
		ret.push__(std::to_string(ret3));
		break;
	case func::param::Typ::Void:
		break;
	default:
		return err__("返回类型不支持");
	}

	if(addr_ret) {
		ret.push__(addr_ret);
		delete addr_ret;
	}
	if(buf[0])
		ret.push__(buf);
	if(err_ret) {
		switch(err_ret) {
		case jieshiqi_err_go_ + keyword_end_:
		case jieshiqi_err_go_ + keyword_break_:
		case jieshiqi_err_go_ + keyword_continue_:
			return Ok2(jieshiqi_err_go_ - err_ret, "");
		case jieshiqi_err_:
			if(by_ce)
				break;
		default:
			return err__(buf, " 错误码", std::to_string(err_ret).c_str());
		}
	}
	if(by_ce)
		return ce.r2_;
	return Ok(true);
}

}} /* namespace segm */
