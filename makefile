cflags1=-std=c++1y -Wall -c -fmessage-length=0 -MMD -MP

ifeq ($(o),d)
out=Debug
main=$(out)/main.o
tag=$(out)/zhscript2
cflags2=-O0 -g3
cflags5=-lstdc++fs
endif

ifeq ($(o),r)
out=Release
main=$(out)/main.o
tag=$(out)/zhscript2
cflags2=-O3
cflags5=-lstdc++fs
endif

ifeq ($(o),dl)
out=Debug-l
tag=$(out)/l4.so
cflags2=-O0 -g3
cflags4=-fPIC
cflags3=-shared
cflags5=-lstdc++fs
endif

ifeq ($(o),rl)
out=/tmp/zs2/Release-l
tag=$(out)/l4.so
cflags2=-O3
cflags4=-fPIC
cflags3=-shared
cflags5=-lstdc++fs
endif

ifeq ($(o),r-)
out=/tmp/zs2/Release
main=$(out)/main.o
tag=$(out)/zhscript2
cflags2=-O3
cflags5=-lstdc++fs
endif

#ifeq ($(o),$(filter r2n r-d8,$(o)))
ifeq ($(o),r-d8)
out=/tmp/zs2/Release
main=$(out)/main.o
tag=$(out)/zhscript2
cflags2=-O3
cflags4=-Dver_no_fs_ -Dver_no_cls_ini_ -Dvar_system_=\"debian-linux\"
endif

#ifeq ($(o),$(filter rl2n rl-d8,$(o)))
ifeq ($(o),rl-d8)
out=/tmp/zs2/Release-l
tag=$(out)/l4.so
cflags2=-O3
cflags4=-fPIC -Dver_no_fs_ -Dver_no_cls_ini_ -Dvar_system_=\"debian-linux\"
cflags3=-shared
endif

ifeq ($(o),r3n)
out=/tmp/zs2/Release-3n
main=$(out)/main.o
tag=$(out)/zhscript2
cflags2=-O3
cflags4=-Dver_no_fs_ -Dver_no_cls_ini_ -Dver_no_asm_
endif

ifeq ($(o),rl3n)
out=/tmp/zs2/Release-l3n
tag=$(out)/l4.so
cflags2=-O3
cflags4=-fPIC -Dver_no_fs_ -Dver_no_cls_ini_ -Dver_no_asm_
cflags3=-shared
endif

ifeq ($(o),r1n)
out=/tmp/zs2/Release-1n
main=$(out)/main.o
tag=$(out)/zhscript2
cflags2=-O3
cflags4=-Dver_no_asm_
cflags5=-lstdc++fs
endif

ifndef tag
$(error 可用选择： o={d调试版 | r发布版 | dl动态库调试版 | rl动态库发布版} [x清理 | x1])
endif

all: mkdir $(tag)
	g++ $(cflags3) -o "$(tag)" `find $(out) -name '*.o'` $(cflags5) -ldl


mkdir:
	@mkdir -p $(out)/segm/for $(out)/segm/func/param $(out)/segm/var

$(tag): \
$(out)/segm/for/base.o \
$(out)/segm/for/base2.o \
$(out)/segm/func/param/callback.o \
$(out)/segm/func/param/callstack.o \
$(out)/segm/func/param/qv_for.o \
$(out)/segm/func/call.o \
$(out)/segm/var/arg.o \
$(out)/segm/var/args.o \
$(out)/segm/var/attr.o \
$(out)/segm/var/reserved.o \
$(out)/segm/var/qv.o \
$(out)/segm/alias.o \
$(out)/segm/all.o \
$(out)/segm/call.o \
$(out)/segm/def.o \
$(out)/segm/debug.o \
$(out)/segm/dl.o \
$(out)/segm/eval.o \
$(out)/segm/exec.o \
$(out)/segm/exit.o \
$(out)/segm/func.o \
$(out)/segm/guandaojie.o \
$(out)/segm/if.o \
$(out)/segm/item.o \
$(out)/segm/item1.o \
$(out)/segm/load.o \
$(out)/segm/mod_.o \
$(out)/segm/mod_free.o \
$(out)/segm/mod.o \
$(out)/segm/name.o \
$(out)/segm/no.o \
$(out)/segm/print.o \
$(out)/segm/set.o \
$(out)/segm/switch.o \
$(out)/segm/with.o \
$(out)/segm/tag.o \
$(out)/segm/var.o \
$(out)/arg.o \
$(out)/clpars.o \
$(out)/debug.o \
$(out)/equname.o \
$(out)/eval.o \
$(out)/file.o \
$(out)/keyword.o \
$(out)/lib.o \
$(out)/qv.o \
$(out)/result2.o \
$(out)/ret.o \
$(out)/shell.o \
$(out)/shell2.o \
$(out)/textpars.o \
$(out)/util.o \
$(out)/var.o \
$(main)


$(out)/%.o: %.cpp %.h
	g++ $(cflags4) $(cflags2) $(cflags1) -MF"$(@:%.o=%.d)" -MT"$(@)" -o"$@" "$<"
$(out)/segm/func/call.o: segm/func/call.cpp segm/func/call.h
	g++ $(cflags4) -O0 -g3 $(cflags1) -MF"$(@:%.o=%.d)" -MT"$(@)" -o"$@" "$<"
$(out)/%.o: %.cpp
	g++ $(cflags4) $(cflags2) $(cflags1) -MF"$(@:%.o=%.d)" -MT"$(@)" -o"$@" "$<"

x:
	rm -rf $(out)
x1:
	rm -rf "$(tag)"
