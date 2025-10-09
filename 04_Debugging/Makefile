GENERATES=range

range: main.c
	cc -o0 -g -o $@ $^

test: test-1 test-2

test-%: range
	gdb -x $*.gdb | grep @@@ | diff -q $*_test.out -

clean:
	rm -f $(GENERATES)