WARNS := -Wall -Wextra -Wfloat-equal -Wvla -std=c99 -Wpedantic
DEBUG := $(WARNS) -fsanitize=undefined -fsanitize=address -g3
OPTIM := $(WARNS) -O3
.PHONY: all run rund clean

all: ext ext_d

ext: ext.c driverext.c
	gcc driverext.c ext.c $(OPTIM) -o ext

ext_d: ext.c driverext.c
	gcc driverext.c ext.c $(DEBUG) -o ext_d

run: ext
	./ext

rund: ext_d
	./ext_d

clean:
	rm -f ext ext_d

extt: ext.c wordtest.c
	gcc ..wordtest.c ext.c $(OPTIM) -o extt