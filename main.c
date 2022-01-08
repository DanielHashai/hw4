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
    return addVertex();
}



char doT() {
    return addVertex();
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
			    }
				break;
			case 'B':
			    result = addVertex();
			    if ((result == '\0') || (result == EOF) || (result == CHAR_SUCCESS)) {
				return 0;
			    } else if (result == 'B') {
				doB();
			    } else if (result == 'S') {
				doS();
			    } else if (result == 'T') {
				doT();
			    }
			    break;
			case 'S':
			    break;
			case 'T':
			    break;
			default:
			    break;
		}
	}

	return 0;
}
