/*
 * qv.cpp
 *
 *  Created on: 2016年8月29日
 *      Author: zzzzzzzzzzz
 */

#include <algorithm>
#include "qv.h"

bool Qv::var_get__(const std::string& name, bool is_test,
		std::function<void(var::Item*, Qv*, bool)> fn2, std::function<bool(Qv*)> fn3,
		VarTyp vt, bool auto_new, bool use_up) {
	{
		Qv* qv = this;
		bool can_priv = true;
		std::function<var::Item*(Qv*)> fn;
		switch(vt) {
		case VarTyp::Var:
			fn = [&](Qv *qv) {
				return qv->vars_.get__(name, can_priv);
			};
			break;
		case VarTyp::Def:
			fn = [&](Qv *qv) {
				return qv->defs_.get__(name, can_priv);
			};
			break;
		case VarTyp::Func:
			fn = [&](Qv *qv) {
				return qv->funcs_.get__(name, can_priv);
			};
			break;
		}
		for(;qv;) {
			var::Item* i = fn(qv);
			if(i != nullptr) {
				fn2(i, qv, false);
				return true;
			}
			if(!use_up)
				break;
			if(fn3 && fn3(qv))
				return true;
			if(!is_test) {
				can_priv = false;
			}
			qv = qv->up_;
		}
		if(use_up)
		{
			ModList* mods = mods_;
			if(mods) {
				if(std::find_if(mods->begin(), mods->end(), [&](Qv *qv2) {
					var::Item* i;
					if((i = fn(qv2))) {
						fn2(i, qv2, false);
						return true;
					}
					return false;
				}) != mods->end())
					return true;
			}
		}
	}
	if(auto_new) {
		var::Item* i;
		switch(vt) {
		case VarTyp::Var: default:
			i = new var::Item();
			vars_.a_.push_back(i);
			break;
		case VarTyp::Def:
			i = new def::Item();
			defs_.a_.push_back(i);
			break;
		case VarTyp::Func:
			i = new var::Item();
			funcs_.a_.push_back(i);
			break;
		}
		i->name_ = name;
		fn2(i, this, true);
		return true;
	}
	return false;
}
var::Item* Qv::var_get__(const std::string& name, bool can_priv2, Qv **qv_var, VarTyp vt, bool auto_new, bool *is_new, bool use_up) {
	var::Item* i;
	if(var_get__(name, can_priv2, [&](var::Item* i2, Qv* qv_var2, bool is_new2) {
		i = i2;
		if(qv_var)
			*qv_var = qv_var2;
		if(is_new)
			*is_new = is_new2;
	}, nullptr, vt, auto_new, use_up))
		return i;
	return nullptr;
}

def::Item* Qv::def_get2__(const std::string& name, size_t argc, size_t back_arg, bool is_priv, bool is_through) {
	bool is_new;
	def::Item* v = (::def::Item*)var_get__(name, false, nullptr, VarTyp::Def, true, &is_new, false);
	if(is_new) {
		v->is_priv_ = is_priv;
	}
	v->argc_ = argc;
	v->back_arg_ = back_arg;
	v->is_through_ = is_through;
	v->name2_ = name;
	return v;
}

bool Qv::for_def__(std::function<bool(def::Item*)> fn) {
	auto for2 = [&](Qv *qv2) -> bool {
		auto a = qv2->defs_.a_;
		return std::find_if(a.begin(), a.end(), [&](var::Item* item) {
			//dynamic
			return fn(static_cast<def::Item*>(item));
		}) != a.end();
	};
	{
		Qv* qv = this;
		for(;qv;) {
			if(for2(qv))
				return true;
			qv = qv->up_;
#ifdef ver_chk_up_
			if(qv && !qv->this__())
				break;
#endif
		}
	}
	ModList* mods = mods_;
	if(mods) {
		if(std::find_if(mods->begin(), mods->end(), [&](Qv *qv2) {
			return for2(qv2);
		}) != mods->end())
			return true;
	}
	return false;
}

Qv::~Qv() {
	if(is_mod_ && defer_) {
		delete defer_;
	}
}

/*template<class varItem, class varList>
varItem* var__get__(Qv* qv,
		std::function<varItem*(const std::string&, Qv*)> vars_get,
		std::function<varItem*(const std::string&)> vars_new,
		const std::string& name, bool auto_new, bool use_up) {
	varItem* i;
	bool for_mods = false;
	ModList* mods = qv->mods_;
	for(;qv;) {
		i = vars_get(name, qv);
		if(i != nullptr)
			return i;
		if(!use_up)
			break;
		if(!for_mods) {
			for_mods = true;
			if(mods) {
				if(std::find_if(mods->begin(), mods->end(), [&](auto qv2) {
					i = vars_get(name, qv2);
					return i != nullptr;
				}) != mods->end())
					return i;
			}
		}
		qv = qv->up_;
	}
	if(auto_new) {
		i = vars_new(name);
	}
	return i;
}*/

/*
	return var__get__(this,
			[](const std::string& name, Qv* qv) -> var::Item* {return qv->vars_.get__(name);},
			[&](const std::string& name) -> var::Item* {
				var::Item* i = new var::Item();
				i->name_ = name;
				vars_.a_.push_back(i);
				return i;
			},
			name, auto_new, use_up);
*/
