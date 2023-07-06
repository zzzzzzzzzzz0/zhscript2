/*
 * l4.h
 *
 *  Created on: 2016年10月2日
 *      Author: zzzzzzzzzzz
 */

#ifndef SHELL_H_
#define SHELL_H_

extern "C" {

void* l4_new__();
void l4_delete__(void* l4);
void l4_cmdline_parse__(void* l4, int argc, const char** argv);
bool l4_has_src__(void* l4);
bool l4_jieshi3__(void* l4, void* qv_up, void* ret);
bool l4_jieshi4__(void* l4, const char* src,bool src_is_file,const char* src2,void* qv_up,int argc,const char**argv, void* ret);

const char* l4_err__(void* l4);
int l4_exit_code__(void* l4);
bool l4_is_end__(void* l4);

}

#endif /* SHELL_H_ */
