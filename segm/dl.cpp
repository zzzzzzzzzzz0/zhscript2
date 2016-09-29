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

Result2 Item::z__(const keyword::Item& kw_by, Qv &qv, List &ls, Ret &ret) {
	Ret ret2;
	{
		Result2 r2 = a_.z__(kw__(), qv, ls, ret2);
		if(false__(r2))
			return r2;
	}
	ret2.one__();

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
			ret.push__('l', std::make_shared<Info>(handle));
			return Ok(true);
		}
	}
	return Err(err);
}

}} /* namespace segm */
