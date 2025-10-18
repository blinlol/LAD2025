GENERATES=esub esub.out sed.out

esub: main.c
	cc -o0 -g -o $@ $^

clean:
	rm -f $(GENERATES)

test: esub
	./esub "([[:digit:]]{4}) +([[:digit:]]{1,2}) +([[:alpha:]]+) +([[:alpha:]]+)" "\4, \2 \3 year of \1" "2024 17 October Thursday" > esub.out
	echo "2024 17 October Thursday" | sed -E "s/([[:digit:]]{4}) +([[:digit:]]{1,2}) +([[:alpha:]]+) +([[:alpha:]]+)/\4, \2 \3 year of \1/" > sed.out
	diff esub.out sed.out