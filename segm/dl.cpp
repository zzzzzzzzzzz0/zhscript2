/*
 * dl.cpp
 *
 *  Created on: 2016年9月13日
 *      Author: zzzzzzzzzzz
 */

#include <dlfcn.h>
#include "dl.h"

namespace segm {
namespace dl {

void Info::free__() {
	if(handle_) {
		dlclose(handle_);
		handle_ = nullptr;
	}
}

Result2 Item::z__(const KwBy& kw_by, Qv *qv, List &ls, Ret &ret) {
	Ret ret2;
	{
		KwBy kw_by2 {kw__(), &a_, &kw_by};
		Result2 r2 = a_.z__(kw_by2, qv, ls, ret2);
		ret2.one__();
		if(false__(r2))
			return r2;
	}

	std::string err;
	for(auto s : ret2.a_) {
		const std::string &name = s.val_;
		void *handle = dlopen(name.c_str(), RTLD_LAZY);
		const char* dlerr = dlerror();
		if(dlerr) {
			if(!err.empty())
				err += '\n';
			err += dlerr;
		} else {
			ret.push__(name);
			ret.push__(Typ2::Dl, std::make_shared<Info>(handle));
			return Ok(true);
		}
	}
	return Err(err);
}

}} /* namespace segm */
