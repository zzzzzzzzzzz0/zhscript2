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

Result2 Info::parse2__(const std::string &s, param::Typ *ret, ParamList &params) {
	size_t i = 0, i1 = ret ? 1 : 0;
	param::Typ typ = param::Typ::Void;
	for(size_t ic = 0; ic < s.size(); ic++) {
		char c = s[ic];
		switch(c) {
		case '-':
			i++;
			continue;
		case 'i':
			typ = param::Typ::Int;
			break;
		case 'c':
			typ = param::Typ::Char;
			if(ic + 1 < s.size() && s[ic + 1] == '*') {
				ic++;
				typ = param::Typ::Chars;
			}
			break;
		case '&':
			typ = param::Typ::Addr;
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
		case 'Z':
			typ = param::Typ::Z;
			break;
		case '$':
			if(++ic >= s.size()) {
				params.push_back((param::Item*)new param::CallbackItem(-1));
				continue;
			}
			c = s[ic];
			size_t pos;
			if(c == '{') {
				if(++ic >= s.size())
					return err__('<');
				c = s[ic++];
				pos = s.find('}', ic);
				if(pos == std::string::npos)
					return err__('<');
				std::string s2 = s.substr(ic, pos - ic);
				switch(c) {
				case '*':
					params.push_back((param::Item*)new param::StringValItem(s2));
					break;
				case 'l':
					if(!can_stoi__(s2, true))
						return err__(s2);
					params.push_back((param::Item*)new param::IntValItem(std::stol(s2)));
					break;
				case 'u':
					if(!can_stoi__(s2))
						return err__(s2);
					params.push_back((param::Item*)new param::UIntValItem(std::stoul(s2)));
					break;
				default:
					return err__(bad__(c));
				}
				pos++;
			} else {
				pos = s.find('-', ic);
				if(pos == std::string::npos)
					pos = s.size();
				std::string s2 = s.substr(ic, pos - ic);
				int i2;
				if(s2.empty())
					i2 = -1;
				else {
					if(!can_stoi__(s2))
						return err__(s2);
					i2 = std::stoi(s2);
				}
				params.push_back((param::Item*)new param::CallbackItem(i2));
			}
			ic = pos - 1;
			continue;
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
			params.push_back(new param::Item(typ));
			continue;
		}
		return err__("分隔符有误");
	}
	return Ok(true);
}

Result2 Item::z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
	Ret ret2;
	{
		Result2 r2 = a_.z__(kw__(), qv, ls, ret2);
		if(false__(r2))
			return r2;
	}
	ret2.one__();

	const Ret_List& a = ret2.a_;
	size_t len = a.size();
	if(len < 2)
		return err__('<');

	dl::Info* dli;
	{
		const Ret_Item& ri = a[1];
		if(ri.typ_ != 'l')
			return err__("非动态库句柄");
		dli = static_cast<dl::Info*>(ri.val2_.get());
	}

	void *addr = dlsym(dli->handle_, a[0].val_.c_str());
	const char* dlerr = dlerror();
	if(dlerr) {
		return err__(dlerr);
	}

	auto info = std::make_shared<Info>();
	info->addr_ = addr;
	if(len > 2) {
		Result2 r2 = info->parse__(a[2].val_);
		if(false__(r2))
			return r2;
	}

	ret.push__('f', info);
	return Ok(true);
}

}} /* namespace segm */
