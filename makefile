cflags1=-std=c++1y -Wall -c -fmessage-length=0 -MMD -MP

ifeq ($(o),d)
out=Debug
main=$(out)/main.o
tag=$(out)/zhscript2
cflags2=-O0 -g3
endif

ifeq ($(o),r)
out=Release
main=$(out)/main.o
tag=$(out)/zhscript2
cflags2=-O3
endif

ifeq ($(o),dl)
out=Debug-l
tag=$(out)/l4.so
cflags2=-O0 -g3 -fPIC
cflags3=-shared
endif

ifeq ($(o),rl)
out=Release-l
tag=$(out)/l4.so
cflags2=-O3 -fPIC
cflags3=-shared
endif

ifndef o
$(error 可用选择： o={d调试版 | r发布版 | dl动态库调试版 | rl动态库发布版} [x清理 | x1])
endif

all: mkdir $(tag)
	g++ $(cflags3) -o "$(tag)" `find $(out) -name '*.o'` -lstdc++fs -ldl


mkdir:
	@mkdir -p $(out)/segm/for $(out)/segm/func/param $(out)/segm/var

$(tag): \
$(out)/segm/for/base.o \
$(out)/segm/for/base2.o \
$(out)/segm/func/param/callback.o \
$(out)/segm/func/call.o \
$(out)/segm/var/arg.o \
$(out)/segm/var/args.o \
$(out)/segm/var/base.o \
$(out)/segm/all.o \
$(out)/segm/call.o \
$(out)/segm/def.o \
$(out)/segm/dl.o \
$(out)/segm/eval.o \
$(out)/segm/exec.o \
$(out)/segm/func.o \
$(out)/segm/if.o \
$(out)/segm/item.o \
$(out)/segm/item1.o \
$(out)/segm/load.o \
$(out)/segm/mod_.o \
$(out)/segm/mod.o \
$(out)/segm/no.o \
$(out)/segm/print.o \
$(out)/segm/set.o \
$(out)/segm/tag.o \
$(out)/segm/var.o \
$(out)/arg.o \
$(out)/debug.o \
$(out)/eval.o \
$(out)/file.o \
$(out)/keyword.o \
$(out)/lib.o \
$(out)/qv.o \
$(out)/result2.o \
$(out)/ret.o \
$(out)/util.o \
$(out)/var.o \
$(main)


$(out)/%.o: %.cpp
	g++ $(cflags2) $(cflags1) -MF"$(@:%.o=%.d)" -MT"$(@)" -o"$@" "$<"

x:
	rm -rf $(out)
x1:
	rm -rf "$(tag)"
