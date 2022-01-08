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
    return getCharOnly();
}

char doD() {
    return getCharOnly();
}

char doT() {
    return getCharOnly();
}

int main() {

	char cmd = getChar();
	while (cmd != 'A') {
	    cmd = getChar();
	}
	cmd = doA();
	printGraph();

	if (isTerminate(cmd)) return 0;

	while (!isTerminate(cmd)) {

		if (DEBUG_EN) printf("%s %d [main] cmd(%c)\n", __FILE__, __LINE__, cmd);

		switch (cmd) {
			case 'A':
			    cmd = doA();
			    printGraph();
			    break;
			case 'B':
			    cmd = doB();
			    printGraph();
			    break;
			case 'S':
			    cmd = doS();
			    break;
			case 'D':
			    cmd = doD();
			    break;
			case 'T':
			    cmd = doT();
			    break;
			default:
			    break;
		}
	}

	deleteGraph();

	return 0;
}
