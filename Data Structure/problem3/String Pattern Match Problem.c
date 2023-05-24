#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* fail(char* pattern) {
    int lenp = strlen(pattern);

    int* fail_ = (int*)malloc(sizeof(int) * lenp);
    fail_[0] = 0;

    for (int i = 1, j = 0; i < lenp; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = fail_[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            fail_[i] = ++j;
        }
        else {
            fail_[i] = 0;
        }
    }

    return fail_;
}


int pmatch_delete(char* string, char* pattern) {
    int lens = strlen(string);
    int lenp = strlen(pattern);

    if (lenp > lens) {
        return -1;
    }

    int* failure = fail(pattern);
    int j = 0, start = 0;
    int result[31] = { 0, };
    char result2[31] = { '\0' }; 

    for (int i = 0; i < lens; i++) {
        while (j > 0 && string[i] != pattern[j]) {
            j = failure[j - 1];
        }

        if (string[i] == pattern[j]) {
            j++;
            if (j == lenp) {
                for (int k = i - lenp + 1; k <= i; k++) {
                    result[k] = 1;
                }
                j = failure[j - 1];
            }
        }
    }

    for (int i = 0; i < lens; i++) {
        if (result[i] == 0) { 
            strncat(result2, &string[i], 1);
        }
    }

    printf("%s\n", result2);

    free(failure);
    return 0;
}


int main() {
    char string[31], pattern[31];

    fgets(string, sizeof(string), stdin);
    string[strlen(string) - 1] = '\0';

    fgets(pattern, sizeof(pattern), stdin);
    pattern[strlen(pattern) - 1] = '\0';

    pmatch_delete(string, pattern);

    return 0;
}