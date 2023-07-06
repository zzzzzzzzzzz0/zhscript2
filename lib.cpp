/*
 * Lib.cpp
 *
 *  Created on: 2016年8月19日
 *      Author: zzzzzzzzzzz
 */

#include "lib.h"

void Lib::cmdline_parse__(int argc, const char** argv, int from) {
	if(from > 0) {
		set_path__(argv[0]);
		ls_.qv_top_.var_get2__(keyword::SHELL)->val_ =
		ls_.qv_top_.var_get2__(keyword::SHELL.val_en_)->val_ = ls_.file_.good_path__(argv[0]);
	}
	clpars_.z__(argc, argv, from, args_);
}

Lib::Lib() {
	ls_.qv_top_.var_get2__(keyword::SYSTEM)->val_ =
	ls_.qv_top_.var_get2__(keyword::SYSTEM.val_en_)->val_ =
#ifdef var_system_
			var_system_
#elif ver_mac_mini_
			"mac"
#else
			"linux"
#endif
			;
	ls_.qv_top_.def_get2__(keyword::LF)->val_ =
	ls_.qv_top_.def_get2__(keyword::LF.val_en_)->val_ = keyword::YUANYANG_BEGIN + "\r" + keyword::YUANYANG_END;
	ls_.qv_top_.def_get2__(keyword::CR)->val_ =
	ls_.qv_top_.def_get2__(keyword::CR.val_en_)->val_ = keyword::YUANYANG_BEGIN + "\n" + keyword::YUANYANG_END;
	ls_.qv_top_.def_get2__(keyword::TAB)->val_ =
	ls_.qv_top_.def_get2__(keyword::TAB.val_en_)->val_ = keyword::YUANYANG_BEGIN + "\t" + keyword::YUANYANG_END;
	ls_.qv_top_.def_get2__(keyword::ESC)->val_ = keyword::YUANYANG_BEGIN + "\x1b" + keyword::YUANYANG_END;
}

Qv* Lib::new_main_qu__() {
	Qv* qv = new Qv("主", &ls_.qv_top_);
	qv->mods_ = &ls_.mods_;
	qv->args_ = &args_;
	ls_.qv_main_ = qv;
	return qv;
}
