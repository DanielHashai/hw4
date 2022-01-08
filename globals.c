#include "globals.h"

bool isEOF(int x) {
    return (x == EOF) ? true : false;
}

char getChar() {

	char ret;

	int eofCheck = scanf("%c", &ret); // check if reached end of file

	if (isEOF(ret) || (ret == '\0')) return '\0'; 

	while (ret == ' ') { // ignore white spaces
		eofCheck = scanf("%c", &ret);
		if (isEOF(ret) || isTerminate(ret)) return 'f';
	}
	
	if (DEBUG_EN && EXTRA_DEBUG_EN) printf("%s %d [getChar] in(%c) isEOF(%d)\n", __FILE__, __LINE__, ret, isEOF(ret));

	return ret;

}

int getInt() {

	int ret;

	scanf("%d", &ret);
	
	if (DEBUG_EN && EXTRA_DEBUG_EN) printf("%s %d [getInt] in(%d)\n", __FILE__, __LINE__, ret);

	return ret;

}

bool isInt(char c) {

	return ((DECIMAL_CHAR_VAL_0 <= c) && (c <= DECIMAL_CHAR_VAL_9)) ? true : false;

}

char getCharOnly() {

    char ret = getChar();
    if (DEBUG_EN && EXTRA_DEBUG_EN) printf("%s %d [getCharOnly] in(%c)\n", __FILE__, __LINE__, ret);

    while(isInt(ret) && !isTerminate(ret)) {
	ret = getChar();
	if (DEBUG_EN && EXTRA_DEBUG_EN) printf("%s %d [getCharOnly] in(%c)\n", __FILE__, __LINE__, ret);
    }

    return ret;

}

bool isTerminate(char c) {
    return ((c == '\0') || (c == EOF) || (c == CHAR_SUCCESS) || (c == '\n')) ? true : false;
}
