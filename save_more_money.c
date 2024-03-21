#ifndef SAVE_MORE_MONEY
#define SAVE_MORE_MONEY
#define TEN 10
#define SIZE 8
#include <stdio.h>

typedef struct {
	int a, b, c;
} tuple;

static struct {
	int count;
	int k;
	tuple result[SIZE];
} _Answers;

static int _Digits[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

static int *_S = _Digits + 0;
static int *_A = _Digits + 1;
static int *_V = _Digits + 2;
static int *_E = _Digits + 3;
static int *_M = _Digits + 4;
static int *_O = _Digits + 5;
static int *_R = _Digits + 6;
static int *_N = _Digits + 7;
static int *_Y = _Digits + 8;

static void _Doit(int *arr, int num) {
	if (num == 1) {
		if (*_S != 0 && *_M != 0) {
			int a = *_S * 1000 + *_A * 100 + *_V * 10 + *_E;
			int b = *_M * 1000 + *_O * 100 + *_R * 10 + *_E;
			int c = *_M * 10000 + *_O * 1000 + *_N * 100 + *_E * 10 + *_Y;

			if (a + b == c) {
				if (_Answers.k < SIZE) {
					(_Answers.result + _Answers.k)->a = a;
					(_Answers.result + _Answers.k)->b = b;
					(_Answers.result + _Answers.k)->c = c;
				}
				++_Answers.k;
			}

			++_Answers.count;
		}
	}
	else {
		int x;
		_Doit(arr + 1, num - 1);  // the lead item, no swap

		for (int i = 1; i < num; ++i) {
			// swap with another item
			x = arr[i];
			for (int j = i; j > 0; --j) {
				arr[j] = arr[j - 1];
			}
			arr[0] = x;

			_Doit(arr + 1, num - 1);

			// back swap
			x = arr[0];
			for (int j = 0; j < i; ++j) {
				arr[j] = arr[j + 1];
			}
			arr[i] = x;
		}
	}
}

static void _Unique() {
	tuple *p = _Answers.result;
	int k = _Answers.k;
	int r = 0;

	if (k <= 1 || k > SIZE) return;  // nothing to do, or not to do anything

	for (int i = 1; i < k; ++i) {
		int a = (p + i)->a;
		int b = (p + i)->b;
		int c = (p + i)->c;
		int j = 0;

		while (j <= r) {
			if ((p + j)->a == a && (p + j)->b == b) {
				break;
			}
			++j;
		}

		if (r < j) {
			(p + j)->a = a;
			(p + j)->b = b;
			(p + j)->c = c;
			++r;
		}
	}

	for (int i = (_Answers.k = r + 1); i < k; ++i) {
		(p + i)-> a = 0;
		(p + i)-> b = 0;
		(p + i)-> c = 0;
	}
}

static void bar() {
	_Answers.count = 0;
	_Answers.k = 0;
	_Doit(_Digits, TEN);
	_Unique();
}

static void baz() {
	int k = _Answers.k;

	if (k == 0) {
		printf("** There is no solution to this problem!\n");
	}
	else {
		if (k > SIZE) {
			printf("** These are incomplete answers! "
				"(There are, in fact, %d answers, "
				"which may not be unique.)\n", k);
		}

		tuple *p = _Answers.result;
		printf("[");
		for (int i = 1; i < (k > SIZE ? SIZE : k); ++i) {
			printf("(%d, %d, %d), ", p->a, p->b, p->c);
			++p;
		}
		printf("(%d, %d, %d)]\n", p->a, p->b, p->c);
	}

	printf("%d answer%s, %d trials\n", k, k > 1 ? "s" : "", _Answers.count);
}

#endif


#include <time.h>

int main() {
	clock_t elapsed = clock();
	bar();
	baz();
	elapsed = clock() - elapsed;
	int msec = elapsed * 1000 / CLOCKS_PER_SEC;
	printf("Time elapsed: %d sec, %d msec", msec / 1000, msec % 1000);
	return 0;
}
