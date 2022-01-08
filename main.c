#include <stdio.h>
#include "algo.h"
#include "nodes.h"
#include "edges.h"

char doA() {
    if (!graphIsNull()) {
	freeGraph();
    }
    char ret = createUserList();
    if (DEBUG_EN) printf("AAAAAAAAAAAAAAAAAAAAAAAAAaAAAAAAAAAAA ---->\n");
    printGraph();
    if (DEBUG_EN) printf("<---- AAAAAAAAAAAAAAAAAAAAAAAAAaAAAAAAAAAAA\n");
    return ret;
}

char doB() {
    char ret = addVertex();
    if (DEBUG_EN) printf("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB ---->\n");
    printGraph();
    if (DEBUG_EN) printf("<---- BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n");
    return ret;
}


char doS() {
    doDijkstra();
    return getCharOnly();
}

char doD() {
    deleteVertex();
    if (DEBUG_EN) printf("DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD ---->\n");
    printGraph();
    if (DEBUG_EN) printf("<---- DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD\n");
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
