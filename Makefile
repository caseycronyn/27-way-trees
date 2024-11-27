WARNS := -Wall -Wextra -Wfloat-equal -Wvla -std=c99 -Wpedantic
DEBUG := $(WARNS) -fsanitize=undefined -fsanitize=address -g3
OPTIM := $(WARNS) -O3
.PHONY: all run rund clean

all: t27 t27_d

t27: t27.c t27.h driver.c
	gcc driver.c t27.c $(OPTIM) -o t27

t27_d: t27.c t27.h driver.c
	gcc driver.c t27.c $(DEBUG) -o t27_d

run: t27
	./t27

rund: t27_d
	./t27_d

ext: Extension/ext.c ./driverext.c Extension/ext.h
	gcc driverext.c Extension/ext.c -IExtension -I.. -I. $(OPTIM) -o ext

clean:
<<<<<<< HEAD
	rm -f t27 t27_d ext
=======
	rm -f t27 t27_d

t27t: t27.c t27.h wordtest.c
	$(COMPILER) wordtest.c t27.c $(OPTIM) -o t27t

ext: ext.c driverext.c
	gcc driverext.c ext.c $(OPTIM) -o ext

ext_d: ext.c driverext.c
	gcc driverext.c ext.c $(DEBUG) -o ext_d

extt: ext.c wordtest.c
	gcc wordtest.c ext.c $(OPTIM) -o extt
>>>>>>> refs/remotes/origin/main
