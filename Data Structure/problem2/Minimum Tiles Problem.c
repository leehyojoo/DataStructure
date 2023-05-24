#define _CRT_SECURE_NO_WARNINGS	
#include <stdio.h>
#include <math.h>

int find_min_tile(int n, int m) {

    // case 3의 경우 -size 때문에 음수일 경우까지 고려
    if (n < 0 || m < 0) {
        return 0;
    }

    // case 1
    if (n == 0 || m == 0 || n == 1 || m == 1) {
        return n * m;
    }

    
    int k = log2(n < m ? n : m);
    int size = 1 << k;

    // case 2
    if (n == size && m == size) {
        return 1;
    }

    // case 3
    else {
        int result1 = find_min_tile(n, m - size);
        int result2 = find_min_tile(n - size, m);
        int result3 = find_min_tile(n - size, m - size);

        return 1 + result1 + result2 - result3;
    }
    
}


int main() {
	int N, M, result;
	scanf("%d %d", &N, &M);
	result = find_min_tile(N, M);
	printf("%d\n", result);
	return 0;
}