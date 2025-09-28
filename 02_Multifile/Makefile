GENERATES = prog README liboutput* prog-* test*
TRASH = *.o *~ o.*
CFLAGS = -fPIC

%.o:    %.c
	cc $< -c -fPIC -o $@

all: README prog 

fun.o: outlib.h

prog:   const.o fun.o prog.o
	cc $^ -o $@

README: prog
	./$< 2> $@

clean:
	rm -f $(TRASH)

clean!: distclean

distclean:      clean
	rm -rf $(GENERATES)

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^

liboutput.so: fun.o const.o
	cc -shared $^ -o $@

prog-a: prog.o liboutput_static.a
	cc $^ -o $@

prog-so: prog.o liboutput.so
	cc $^ -o $@

test: test-noargs test-args-1 test-args-3

test-noargs: testout-noargs-prog testout-noargs-prog-a testout-noargs-prog-so
	cmp testout-noargs-prog testout-noargs-prog-a
	cmp testout-noargs-prog testout-noargs-prog-so
	cmp testout-noargs-prog-a testout-noargs-prog-so

testout-noargs-%: %
	LD_LIBRARY_PATH=. ./$< > testout-noargs-$< 2>&1

test-args-1: testout-args-1-prog testout-args-1-prog-a testout-args-1-prog-so
	cmp testout-args-1-prog testout-args-1-prog-a
	cmp testout-args-1-prog testout-args-1-prog-so
	cmp testout-args-1-prog-a testout-args-1-prog-so

testout-args-1-%: %
	LD_LIBRARY_PATH=. ./$< > testout-args-1-$< 2>&1

test-args-3: testout-args-3-prog testout-args-3-prog-a testout-args-3-prog-so
	cmp testout-args-3-prog testout-args-3-prog-a
	cmp testout-args-3-prog testout-args-3-prog-so
	cmp testout-args-3-prog-a testout-args-3-prog-so

testout-args-3-%: %
	LD_LIBRARY_PATH=. ./$< > testout-args-3-$< 2>&1
