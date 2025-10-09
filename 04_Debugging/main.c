#include <stdio.h>
#include <stdlib.h>

void print_help() {
	printf("Usage:\n");
	printf("	range N		-> [0, 1, ..., N-1]\n");
	printf("	range M N	-> [M, M+1, ..., N-1]\n");
	printf("	range M N S	-> [M, M+S, M+2S, ..., N-1]\n");
}

int range(int from, int to, int step) {
	if (step == 0) {
		return 1;
	}
	int i;
	if (step > 0){
		for (i=from; i<to; i+=step) {
			printf("%d\n", i);
		}
	} else {
		for (i=from; i>to; i+=step) {
			printf("%d\n", i);
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		print_help();
		return 0;
	}

	int M = 0;
	int N = 0;
	int S = 1;

	if (argc == 2) {
		N = atoi(argv[1]);
	} else if (argc == 3) {
		M = atoi(argv[1]);
		N = atoi(argv[2]);
	} else if (argc == 4) {
		M = atol(argv[1]);
		N = atol(argv[2]);
		S = atol(argv[3]);
	} else {
		print_help();
		return 1;
	}

	return range(M, N, S);
}