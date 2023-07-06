/*
 * func.cpp
 *
 *  Created on: 2016年9月13日
 *      Author: zzzzzzzzzzz
 */

#include <dlfcn.h>
#include "func.h"
#include "dl.h"
#include "func/param.h"
#include "func/param/callback.h"
#include "../util.h"

namespace segm {
namespace func {

int Info::no_ = -100;

Result2 Info::parse2__(const std::string &s, param::Typ *ret, ParamList &params) {
	size_t i = 0, i1 = ret ? 1 : 0;
	param::Typ typ = param::Typ::Void;
	for(size_t ic = 0; ic < s.size(); ic++) {
		char c = s[ic];
		auto fn1 = [&](char c2, param::Typ typ2) {
			if(ic + 1 < s.size() && s[ic + 1] == c2) {
				ic++;
				typ = typ2;
				return true;
			}
			return false;
		};

		switch(c) {
		case '-':
			i++;
			continue;
		case 'i':
			typ = param::Typ::Int;
			if(fn1('u', param::Typ::UInt)) break;
			break;
		case 'l':
			typ = param::Typ::Long;
			if(fn1('u', param::Typ::ULong)) break;
			break;
		case 'c':
			typ = param::Typ::Char;
			if(fn1('*', param::Typ::Chars)) break;
			if(fn1('&', param::Typ::CharAddr)) break;
			break;
		case '&':
			typ = param::Typ::Addr;
			break;
		case 'n':
			typ = param::Typ::Not;
			break;
		case 'Z':
			typ = param::Typ::Z;
			break;
		case '$':
		{
			if(++ic >= s.size()) {
				params.push_back((param::Item*)new param::CallbackItem(-1));
				continue;
			}
			c = s[ic];
			std::string s2;
			if(c == '{') {
				if(++ic >= s.size())
					return err__('<');
				c = s[ic++];
				size_t pos = s.find('}', ic);
				if(pos == std::string::npos)
					return err__('<');
				s2 = s.substr(ic, pos - ic);
				ic = pos;
			} else {
				size_t pos = s.find('-', ic);
				if(pos == std::string::npos)
					pos = s.size();
				s2 = s.substr(ic, pos - ic);
				ic = pos - 1;
				int i2;
				if(s2.empty())
					i2 = -1;
				else {
					i2 = i__(s2);
					if(i2 == no_) {
						c = s2[0];
						s2 = s2.substr(1);
					}
				}
				if(i2 != no_) {
					params.push_back((param::Item*)new param::CallbackItem(i2));
					continue;
				}
			}
			switch(c) {
			case '*':
				params.push_back((param::Item*)new param::StringValItem(s2));
				continue;
			case 'l':
				if(can_stoi__(s2, true)) {
					params.push_back((param::Item*)new param::IntValItem(std::stol(s2)));
					continue;
				}
				break;
			case 'u':
				if(can_stoi__(s2)) {
					push__(std::stoul(s2), params);
					continue;
				}
				break;
			}
			return err__(bad__(c), s2);
		}
		case 'V':
			typ = param::Typ::VectorAddr;
			break;
		case 'R':
			typ = param::Typ::Ret;
			break;
		case 'T':
			typ = param::Typ::Trace;
			break;
		case 'B':
			typ = param::Typ::Buf;
			break;
		case 'S':
			typ = param::Typ::Siz;
			break;
		case 'A':
			typ = param::Typ::AddrRet;
			break;
		case 'E':
			typ = param::Typ::Err;
			break;
		default:
			return err__(bad__(c));
		}
		if(i == 0) {
			if(ret) {
				*ret = typ;
				continue;
			}
		}
		if(i == params.size() + i1) {
			push__(typ, params);
			continue;
		}
		return err__("分隔符有误");
	}
	return Ok(true);
}

int Info::i__(const std::string &s2) {
	//-1
	if(s2 == "this") return 0;
	if(s2 == "qv") return 1;
	if(s2 == "varnew") return 2;
	if(s2 == "var") return 3;
	//4
	if(s2 == "forvar") return 5;
	if(s2 == "cbx") return 6;
	if(s2 == "qvnew") return 7;
	if(s2 == "qvdel") return 8;
	if(s2 == "cb") return 9;
	//10
	if(s2 == "ce") return 11;
	if(s2 == "varnew2") return 12;
	//13
	if(s2 == "up") return 14;
	if(s2 == "forvar2") return 15;
	//16
	if(s2 == "main") return 17;
	if(s2 == "trace") return 18;
	if(s2 == "cba") return 19;
	if(s2 == "err") return 20;
	if(s2 == "errclear") return 21;
	if(s2 == "errinfo") return 22;
	if(s2 == "errout") return 23;
	//24
	if(s2 == "forqv") return 25;
	if(s2 == "mksuidao") return 26;
	if(s2 == "defnew") return 27;
	if(s2 == "aliasnew") return 28;
	if(s2 == "ex") return 29;
	if(s2 == "cbx2") return 30;
	if(s2 == "cbx3") return 31;
	if(s2 == "cbx4") return 32;
	if(can_stoi__(s2))
		return std::stoi(s2);
	return no_;
}

void* Item::saddr__(const std::string &fname) {
	if(startswith__(fname, "$") == 2) {
		int i = Info::i__(fname.substr(1));
		if(i != Info::no_) {
			param::Item2 i2 = param::ex__(i);
			if(i2) {
				return (void*)i2;
			}
		}
	}
	return nullptr;
}

Result2 Item::set__(const std::string& name, Sptr_ info, bool is_priv, Qv *qv2, Ret &ret) {
	if(qv2) {
		bool is_new;
		var::Item* v = qv2->var_get__(name, false, nullptr, VarTyp::Func, true, &is_new, false);
		if(is_new) {
			v->is_priv_ = is_priv;
		}
		v->typ2_ = Typ2::Func;
		v->val2_ = info;
	} else
		ret.push__(Typ2::Func, info);

	return Ok(true);
}

Result2 Item::z_2__(Ret &ret2, Ret &ret3, const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	const Ret_List& a = ret3.a_;
	size_t len = a.size();
	if(len < 2)
		return err__('<');

	Qv *qv2 = nullptr;
	std::string name;
	bool is_priv = false;
	const Ret_List& a2 = ret2.a_;
	if(a2.size() > 0) {
		Tag_List *tags = nullptr;
		Result2 r2 = name1__(ret2, name, tags);
		if(false__(r2))
			return r2;

		qv2 = qv;
		r2 = qv4tags__(*tags, qv->args_->use_en_, ls, qv2->mods_, [&](const std::string &s) {
			return is__(s, qv->args_->use_en_, is_priv);
		}, &qv2);
		if(false__(r2))
			return r2;
	}

	void *addr;
	{
		std::string fname = a[0].val_;
		for(;;) {
			if(fname == "&") {
				const std::string &s = a[1].val_;
				if(!can_stoi__(s, true))
					return err__('x', s.c_str());
				addr = (void*)std::stoul(s);
				break;
			}
			if(fname.empty()) {
				if(a2.size() > 0) {
					fname = a2[0].val_;
				}
			}
			const Ret_Item& ri = a[1];
			if(ri.typ2_ == Typ2::Dl) {
				dl::Info* dli = static_cast<dl::Info*>(ri.val2_.get());
				addr = dlsym(dli->handle_, fname.c_str());
				const char* dlerr = dlerror();
				if(dlerr)
					return err__(dlerr);
				break;
			}
			if(ri.val_.empty())
				if((addr = saddr__(fname)))
					break;
			return err__("非动态库句柄");
		}
	}

	auto info = std::make_shared<Info>();
	info->addr_ = addr;
	if(len > 2) {
		Result2 r2 = info->parse__(a[2].val_);
		if(false__(r2))
			return r2;
	}

	return set__(name, info, is_priv, qv2, ret);
}

}} /* namespace segm */
