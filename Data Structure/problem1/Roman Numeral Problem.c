#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// roman description in integer
int roma(char c) {

    switch (c) {
    case 'I':
        return 1;
    case 'V':
        return 5;
    case 'X':
        return 10;
    case 'L':
        return 50;
    case 'C':
        return 100;
    case 'D':
        return 500;
    case 'M':
        return 1000;
    default:
        return -1;
    }
}

// roman -> integer
int r_to_int(char* r) {

    int i = 0, result = 0, len = (int)strlen(r);
    while (i < len) {
        int a = roma(r[i]);
        int b = roma(r[i + 1]);
        if (a < b) {
            result += b - a;
            i++;
        }
        else
            result += a;
        i++;
    }
    return result;
}

// integer -> roman
char* int_to_r(int a) {

    char* roman = malloc(sizeof(char) * 2000);
    int i = 0; // current index

    while (a > 0)
    {
        if (a >= 1000) {
            roman[i++] = 'M';
            a -= 1000;
        }
        else if (a >= 900) {
            roman[i++] = 'C';
            roman[i++] = 'M';
            a -= 900;
        }
        else if (a >= 500) {
            roman[i++] = 'D';
            a -= 500;
        }
        else if (a >= 400) {
            roman[i++] = 'C';
            roman[i++] = 'D';
            a -= 400;
        }
        else if (a >= 100) {
            roman[i++] = 'C';
            a -= 100;
        }
        else if (a >= 90) {
            roman[i++] = 'X';
            roman[i++] = 'C';
            a -= 90;
        }
        else if (a >= 50) {
            roman[i++] = 'L';
            a -= 50;
        }
        else if (a >= 40) {
            roman[i++] = 'X';
            roman[i++] = 'L';
            a -= 40;
        }
        else if (a >= 10) {
            roman[i++] = 'X';
            a -= 10;
        }
        else if (a >= 9) {
            roman[i++] = 'I';
            roman[i++] = 'X';
            a -= 9;
        }
        else if (a >= 5) {
            roman[i++] = 'V';
            a -= 5;
        }
        else if (a >= 4) {
            roman[i++] = 'I';
            roman[i++] = 'V';
            a -= 4;
        }
        else {
            roman[i++] = 'I';
            a -= 1;
        }
    }

    roman[i] = '\0';
    return roman;
}

// main 
int main() {

    int num;
    int i = 0;
    scanf("%d", &num); // test case number

    char roman1[1001][101], roman2[1001][101];

    for (int i = 0; i < num; i++) {
        scanf("%1000s%1000s", roman1[i], roman2[i]);
    }

    for (int i = 0; i < num; i++) {

        int a1 = r_to_int(roman1[i]);
        int a2 = r_to_int(roman2[i]);
        int result_sum = a1 + a2;

        char* result_roman = int_to_r(result_sum);

        printf("%s+ %s=%s\n", roman1[i], roman2[i], result_roman);
        printf("%d+ %d=%d\n", a1, a2, result_sum);
       
        free(result_roman);
    }

    return 0;
}