#include "globals.h"

char getChar() {

	char ret;

	int eofCheck = scanf("%c", &ret); // check if reached end of file

	if ((eofCheck == EOF) || (ret == '\0')) return '\0'; 

	while (ret == ' ') { // ignore white spaces
		eofCheck = scanf("%c", &ret);
		if ((eofCheck == EOF) || (ret == '\0')) return '\0';
	}
	
	if (DEBUG_EN) printf("%s %d in(%c) eofCheck(%d)\n", __FILE__, __LINE__, ret, eofCheck);

	return ret;

}

bool isInt(char c) {

	return ((DECIMAL_CHAR_VAL_0 <= c) && (c <= DECIMAL_CHAR_VAL_9)) ? true : false;

}
