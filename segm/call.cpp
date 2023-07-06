/*
 * call.cpp
 *
 *  Created on: 2016年9月14日
 *      Author: zzzzzzzzzzz
 */

#include "call.h"
#include "func/call.h"
#include "func/old.h"
#include "../defer.h"
#include "../util.h"
#include "../debug.h"

std::string null_ = "NULL";

namespace segm {
namespace call {

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	Ret ret2;
	const Ret_List& a = ret2.a_;
	func::Info* fi;
	{
		/*//简省先了 从此
		size_t i2 = 0;
		bool is_do = false;
		Result2 r2 = a_.z7__(kw__(), qv, ls, ret2, i2, nullptr, [&](Z7_data1* data1, Result2 &r2) {
			if(is_do)
				return 0;
			segm::Item* i = data1->i_;
			const keyword::Item& kw = i->kw__();
			o__(0, i2, ")");
			if(a.size() > 0) {
				const Ret_Item& ri = a[a.size() - 1];
				o__(0, "{", ri.val_, " ", (int)ri.typ2_);
				if(ri.typ2_ == Typ2::Func) {
					o__(0, "z ");
					fi = static_cast<func::Info*>(ri.val2_.get());
					const std::string &val = ri.val_;
					size_t argc_max = fi->params_.size();
					if(!val.empty()) {
						for(auto c : val)
							if(c == '-')
								argc_max++;
					}
					o__(0, argc_max);
					//data1->argc_max_ = argc_max; is_do = true;
				}
				o__(0, "}");
			}
			o__(0, i->str__());
			o_n__();
			return 0;
		});*/
		KwBy kw_by2 {kw__(), &a_, &kw_by};
		Result2 r2 = a_.z__(kw_by2, qv, ls, ret2);
		ret2.one__();
		if(false__(r2))
			return r2;
	}

	if(a.size() < 1)
		return err__('<');
	bool fi_by_new_ = false;
	defer fi_defer([&]() {
		if(fi_by_new_)
			delete fi;
	});
	func::ParamList fpl2;
	{
		const Ret_Item& ri = a[0];
		for(;;) {
			const std::string &val = ri.val_;
			if(ri.typ2_ == Typ2::Func) {
				fi = static_cast<func::Info*>(ri.val2_.get());
				if(!val.empty()) {
					Result2 r2 = fi->parse2__(val, nullptr, fpl2);
					if(false__(r2))
						return r2;
				}
				break;
			}
			if(startswith__(val, "/") == 2) {
				size_t i = val.find("/", 1);
				if(i != std::string::npos) {
					void* addr;
					for(;;) {
						std::string s = val.substr(1, i - 1);
						if((addr = func::Item::saddr__(s)))
							break;
						if(can_stoi__(s, true)) {
							addr = (void*)std::stoul(s);
							break;
						}
						return err__('x', s.c_str());
					}
					fi = new func::Info();
					fi_by_new_ = true;
					fi->addr_ = addr;
					Result2 r2 = fi->parse__(val.substr(i + 1));
					if(false__(r2))
						return r2;
					break;
				}
			}
			return err__("非函数地址", val);
		}
	}

	return z_2__(fi, fpl2, ret2, 1, kw_by, qv, ls, ret);
}

Result2 Item::z_2__(func::Info* fi, func::ParamList& fpl2, Ret &ret2, size_t from, const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	const Ret_List& a = ret2.a_;
	size_t siz = 2048;
	char *buf = new char[siz];
	buf[0] = 0;
	defer defer([&]() {
		delete buf;
	});
	int err_ret = 0;
	char* addr_ret = nullptr;
	Ret ret5;
	std::vector<std::string> ret6;
	func::param::CallEx ce;

	func::param::List2 params;
	{
		size_t len2 = a.size();
		size_t i2 = from;
		auto fn = [&](const func::ParamList &fpl) {
			auto fn2 = [&](auto i) {
				const Ret_Item& ri = a[i2++];
				const std::string &s = ri.val_;

				if(s == null_) {
					params.push_back(0);
					return Ok(true);
				}
				switch(i->typ_) {
				case func::param::Typ::Char:
					if(s.size() >= 1)
						params.push_back(s[0]);
					else {
						//return err__('x', s.c_str());
						params.push_back('\0');
					}
					return Ok(true);
				case func::param::Typ::Chars:
					params.push_back((func::param::Item2)s.c_str());
					return Ok(true);
				case func::param::Typ::Z:
					switch(ri.typ2_) {
					case Typ2::Addr:
						params.push_back(static_cast<UIntRet*>(ri.val2_.get())->val_);
						return Ok(true);
					default:
						params.push_back((func::param::Item2)s.c_str());
						return Ok(true);
					}
				default:
					switch(ri.typ2_) {
					case Typ2::Int:
						params.push_back(static_cast<IntRet*>(ri.val2_.get())->val_);
						return Ok(true);
					case Typ2::UInt:
					case Typ2::Addr:
						params.push_back(static_cast<UIntRet*>(ri.val2_.get())->val_);
						return Ok(true);
					case Typ2::Func:
						params.push_back((func::param::Item2)static_cast<func::Info*>(ri.val2_.get())->addr_);
						return Ok(true);
					default:
						if(!can_stoi__(s, true))
							return err__('x', s.c_str());
						params.push_back(std::stoul(s));
						return Ok(true);
					}
				}
			};
			for(auto i : fpl) {
				switch(i->typ_) {
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
						Result2 r2 = fn2(i);
						if(false__(r2))
							return r2;
					}
					continue;
				case func::param::Typ::Callback:
				{
					Result2 r2 = i->z__(qv, ls, params, ce);
					if(false__(r2))
						return r2;
					continue;
				}
				case func::param::Typ::VectorAddr:
					params.push_back((func::param::Item2)&ret6);
					continue;
				case func::param::Typ::Ret:
					params.push_back((func::param::Item2)&ret5);
					continue;
				case func::param::Typ::Trace:
					params.push_back((func::param::Item2)&kw_by);
					continue;
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
				default:
					break;
				}

				if(i2 >= len2)
					return err__('<');
				Result2 r2 = fn2(i);
				if(false__(r2))
					return r2;
			}
			return Ok(true);
		};
		Result2 r2 = fn(fi->params_);
		if(false__(r2))
			return r2;
		r2 = fn(fpl2);
		if(false__(r2))
			return r2;
		if(i2 > len2)
			return err__('<');
		else if(i2 < len2)
			return err__('>');
	}

	bool by_ce = false;
	ce.ret_ = [&]() {by_ce = true;};

	func::param::Item2 ret3 = 0;
	if(!func::call__(fi, params, ret3))
		return err__('>');
	switch(fi->ret_) {
	case func::param::Typ::Int:
	case func::param::Typ::Long:
	{
		long ret4 = ret3;
		if(fi->ret_ == func::param::Typ::Int)
			ret4 = (int)ret4;
		ret.push__(std::to_string(ret4));
		ret.push__(Typ2::Int, std::make_shared<IntRet>(ret4));
		break;
	}
	case func::param::Typ::UInt:
	case func::param::Typ::ULong:
	case func::param::Typ::Addr:
		if(fi->ret_ == func::param::Typ::UInt)
			ret3 = (unsigned)ret3;
		ret.push__(std::to_string(ret3));
		ret.push__(fi->ret_ == func::param::Typ::Addr ? Typ2::Addr : Typ2::UInt, std::make_shared<UIntRet>(ret3));
		break;
	case func::param::Typ::Chars:
		ret.push__(ret3 ? (const char*)ret3 : null_);
		break;
	case func::param::Typ::Not:
		ret.push__(ret3 ? "0" : "1");
		break;
	case func::param::Typ::Void:
		break;
	default:
		return err__("返回类型不支持");
	}

	{
		bool first = true;
		for(auto i : ret6) {
			if(first)
				first = false;
			else
				ret.one__();
			ret.push__(i);
		}
	}
	ret.push__(ret5);
	if(addr_ret) {
		ret.push__(addr_ret);
		delete addr_ret;
	}
	if(buf[0])
		ret.push__(buf);
	if(err_ret) {
		switch(err_ret) {
		case jieshiqi_err_go_ + keyword_end_:
			ls.is_exit_ = true;
		case jieshiqi_err_go_ + keyword_exit_:
		case jieshiqi_err_go_ + keyword_break_:
		case jieshiqi_err_go_ + keyword_continue_:
			return Ok2(jieshiqi_err_go_ - err_ret);
		default:
			if(false__(ce.r2_)) {
				if(ce.r2_->val_.val_ < 0)
					return ce.r2_;
				if(err_ret >= jieshiqi_err_)
					return ce.r2_;
			}
			return err__(buf, " 错误码", std::to_string(err_ret).c_str());
		}
	}
	if(by_ce)
		return ce.r2_;
	return Ok(true);
}

}} /* namespace segm */
