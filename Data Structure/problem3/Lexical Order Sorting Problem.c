#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void swap(char** a, char** b) {
	char* tmp = *a;
	*a = *b;
	*b = tmp;
}

int my_strcmp(const char* str1, const char* str2) {
	int i = 0;

	while (str1[i] != '\0' && str2[i] != '\0') {
		if (str1[i] < str2[i]) {
			return -1;
		}
		else if (str1[i] > str2[i]) {
			return 1;
		}
		i++;
	}

	if (str1[i] == '\0' && str2[i] == '\0') {
		return 0;
	}
	else if (str1[i] == '\0') {
		return -1;
	}
	else {
		return 1;
	}
}
	
	

void sorting(char **arrayS, int count) {
	for (int i = 0; i < count; i++) {
		for (int j = i + 1; j < count; j++) {
			if (my_strcmp(arrayS[i], arrayS[j]) > 0)
				swap(&arrayS[i], &arrayS[j]);
		}
	}

	for (int i = 0; i < count; i++) {
		if (i == count-1) {
			printf("%s\n", arrayS[i]);
		}
		else
			printf("%s, ", arrayS[i]);
	}
}

int main() {
	int count = 0;
	char** arrayS = NULL;

	while (1) {
		char* string = malloc(sizeof(char) * 100);
		if (string == NULL) {
			exit(1);
		}
		scanf("%s", string);

		if (my_strcmp(string, "exit")==0) {
			free(string);
			for (int i = 0; i < count; i++) {
				free(arrayS[i]);
			}
			free(arrayS);
			return 0;
		}

		count++;
		arrayS = realloc(arrayS, sizeof(char*) * count);
		if (arrayS == NULL) {
			exit(1);
		}
		arrayS[count - 1] = string;
		sorting(arrayS, count);

	}
}