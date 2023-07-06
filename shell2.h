/*
 * shell2.h
 *
 *  Created on: 2017年6月22日
 *      Author: zzzzzzzzzzz
 */

#ifndef SHELL2_H_
#define SHELL2_H_

#include "qv.h"

extern "C" {

void mk_suidao__(Qv *qv, const char *name, unsigned long fnaddr, int ret, size_t argc, ...);

}

#endif /* SHELL2_H_ */
