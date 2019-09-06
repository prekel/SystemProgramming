#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "input.h"
//#include "options.h"

int input_line(char *str) {
	fgets(str, MAX_STRING_LENGTH, stdin);
	int size = strlen(str);
	str[strlen(str) - 1] = '\0';
	return size;
}

int cycle_input_int(char *output, bool(*checker)(int)) {
	int n;
	char string_number[100];
	while (true) {
		printf("%s", output);
		//scanf("%s", string_number);
		input_line(string_number);
		int code = sscanf(string_number, "%d", &n);
		if (!checker(n)) continue;
		if (code > 0) break;
	}
	return n;
}

double cycle_input_double(char *output, bool(*checker)(double)) {
	double n;
	char string_number[100];
	while (true) {
		printf("%s", output);
		//scanf("%s", string_number);
		input_line(string_number);
		int code = sscanf(string_number, "%lf", &n);
		if (!checker(n)) continue;
		if (code > 0) break;
	}
	return n;
}