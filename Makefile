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

clean:
	rm -f t27 t27_d t27t

# additional
# test
t27t-nofl: t27.c t27.h test.c
	gcc test.c t27.c -o t27t-nofl

t27t: t27.c t27.h test.c
	gcc test.c t27.c $(OPTIM) -o t27t

t27_dt: t27.c t27.h test.c
	gcc test.c t27.c $(DEBUG) -o t27_dt

t27-nf: t27.c t27.h driver.c
	gcc driver.c t27.c -o t27-nf
