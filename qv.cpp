/*
 * qv.cpp
 *
 *  Created on: 2016年8月29日
 *      Author: zzzzzzzzzzz
 */

#include <algorithm>
#include "qv.h"

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

var::Item* Qv::var_get__(const std::string& name, bool can_priv2, VarTyp vt, bool auto_new, bool use_up) {
	var::Item* i;
	{
		bool for_mods = false;
		ModList* mods = mods_;
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
		}
		for(;qv;) {
			i = fn(qv);
			if(i != nullptr)
				return i;
			if(!use_up)
				break;
			if(!can_priv2)
				can_priv = false;
			if(!for_mods) {
				for_mods = true;
				if(mods) {
					if(std::find_if(mods->begin(), mods->end(), [&](auto qv2) {
						i = fn(qv2);
						return i != nullptr;
					}) != mods->end())
						return i;
				}
			}
			qv = qv->up_;
		}
	}
	if(auto_new) {
		switch(vt) {
		case VarTyp::Var:
			i = new var::Item();
			vars_.a_.push_back(i);
			break;
		case VarTyp::Def:
			i = new def::Item();
			defs_.a_.push_back(i);
			break;
		}
		i->name_ = name;
	}
	return i;
}

bool Qv::for_def__(std::function<bool(def::Item*)> fn) {
	bool for_mods = false;
	ModList* mods = mods_;
	Qv* qv = this;
	auto for2 = [&](Qv *qv) -> bool {
		auto i = std::find_if(defs_.a_.begin(), defs_.a_.end(), [&](var::Item* item) {
			//dynamic
			return fn(static_cast<def::Item*>(item));
		});
		return i != defs_.a_.end();
	};
	for(;qv;) {
		if(for2(qv))
			return true;
		if(!for_mods) {
			for_mods = true;
			if(mods) {
				if(std::find_if(mods->begin(), mods->end(), [&](auto qv2) {
					return for2(qv2);
				}) != mods->end())
					return true;
			}
		}
		qv = qv->up_;
	}
	return false;
}
