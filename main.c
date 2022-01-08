#include <stdio.h>
#include "algo.h"
#include "nodes.h"
#include "edges.h"

char doA() {
    if (!graphIsNull()) {
	freeGraph();
    }
    char ret = createUserList();
    printGraph();
    return ret;
}

char doB() {
    char ret = addVertex();
    printGraph();
    return ret;
}


char doS() {
    return getCharOnly();
}

char doD() {
    deleteVertex();
    printGraph();
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
			    break;
			case 'B':
			    cmd = doB();
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

	freeGraph();

	return 0;
}
