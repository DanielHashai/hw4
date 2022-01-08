#include <stdio.h>
#include "algo.h"
#include "nodes.h"
#include "edges.h"

char doA() {
    if (!graphIsNull()) {
	deleteGraph();
    }
    return createUserList();
}

char doB() {
    return addVertex();
}


char doS() {
    return '0';
}

char doD() {
    return '0';
}

char doT() {
    return '0';
}

int main() {

	while (true) {

		char cmd = getChar();
		char result = '\0';

		if (DEBUG_EN) printf("%s %d [main] cmd(%c)\n", __FILE__, __LINE__, cmd);
		if (cmd == '\0') return 0;

		switch (cmd) {
			case 'A':
			    result = doA();
			    if ((result == '\0') || (result == EOF) || (result == CHAR_SUCCESS)) {
				return 0;
			    } else if (result == 'B') {
				doB();
			    } else if (result == 'S') {
				doS();
			    } else if (result == 'T') {
				doT();
			    } else if (result == 'A') {
				doA();
			    } else if (result == 'D') {
				doD();
			    }
			    break;
			case 'B':
			    result = doB();
			    if ((result == '\0') || (result == EOF) || (result == CHAR_SUCCESS)) {
				return 0;
			    } else if (result == 'B') {
				doB();
			    } else if (result == 'S') {
				doS();
			    } else if (result == 'T') {
				doT();
			    } else if (result == 'A') {
				doA();
			    } else if (result == 'D') {
				doD();
			    }
			    break;
			case 'S':
			    result = doS();
			    if ((result == '\0') || (result == EOF) || (result == CHAR_SUCCESS)) {
				return 0;
			    } else if (result == 'B') {
				doB();
			    } else if (result == 'S') {
				doS();
			    } else if (result == 'T') {
				doT();
			    } else if (result == 'A') {
				doA();
			    } else if (result == 'D') {
				doD();
			    }
			    break;
			case 'D':
			    result = doD();
			    if ((result == '\0') || (result == EOF) || (result == CHAR_SUCCESS)) {
				return 0;
			    } else if (result == 'B') {
				doB();
			    } else if (result == 'S') {
				doS();
			    } else if (result == 'T') {
				doT();
			    } else if (result == 'A') {
				doA();
			    } else if (result == 'D') {
				doD();
			    }
			    break;
			case 'T':
			    result = doT();
			    if ((result == '\0') || (result == EOF) || (result == CHAR_SUCCESS)) {
				return 0;
			    } else if (result == 'B') {
				doB();
			    } else if (result == 'S') {
				doS();
			    } else if (result == 'T') {
				doT();
			    } else if (result == 'A') {
				doA();
			    } else if (result == 'D') {
				doD();
			    }
			    break;
			default:
			    break;
		}
	}

	return 0;
}
