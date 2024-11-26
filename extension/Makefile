WARNS := -Wall -Wextra -Wfloat-equal -Wvla -std=c99 -Wpedantic
DEBUG := $(WARNS) -fsanitize=undefined -fsanitize=address -g3
OPTIM := $(WARNS) -O3
.PHONY: all run rund clean

all: bst bst_d

bst: bst.c driver_ext.c
	gcc driver_ext.c bst.c $(OPTIM) -o bst

bst_d: bst.c driver_ext.c
	gcc driver_ext.c bst.c $(DEBUG) -o bst_d

run: bst
	./bst

rund: bst_d
	./bst_d

clean:
	rm -f bst bst_d
