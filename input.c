#include <stdio.h>
#include <stdlib.h>
#include "input.h"

bool whitespace(char c) {
	return c == 32 || c == 9  || c == 11 || c == 12 || c == 13;
}

char *getLine() {
	char *line;
	size_t length = 1, index = 0;
	char c = -1;
	bool pause = 0;
	
	line = malloc((length + 1) * sizeof(char));
	
	while (!pause) {
		c = getchar_unlocked();
		
		if (c == 10 || c == -1) {
			pause = 1;
		}
		
		if ((whitespace(c) && (index > 0 && !whitespace(line[index - 1]))) ||
			(whitespace(c) && !index) ||
			!whitespace(c)) {
			if (index + 1 >= length) {
				length <<= 1;
				line = realloc(line, length + 1);
			}
			
			if (whitespace(c)) c = 32;
			line[index++] = c;
		}
	}
	
	line[index] = '\0';
	
	return line;
}
