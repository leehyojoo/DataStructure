#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int find_int_value(int n, int s) {
	if (s < 0) {
		return 0;
	}
	else if (s == 0) {
		if (n = 0)
			return 0;
		return 1;
	}
	else if (s == 1) {
		return n;
	}
	else if (n == 1) {
		return 1;
	}
	else {
		int num = s, sum = 0;
		while (num >= 0) {
			sum += find_int_value(n-1, num);
			num--;
		}
		return sum;
	}
}

int main() {
	int n, s, result;
	scanf("%d %d", &n, &s);
	result = find_int_value(n, s);
	printf("%d\n", result);
	return 0;
}