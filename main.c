#include <stdio.h>
#include "algo.h"
#include "nodes.h"
#include "edges.h"

int main() {

	while (true) {

		char cmd = getChar();
		char result = '\0';

		if (cmd == '\0') return 0;

		switch (cmd) {
			case 'A':
				if (!graphIsNull()) {
					deleteGraph();
				}
				result = createUserList();
				if ((result == '\0') || (result == EOF) || (result == CHAR_SUCCESS)) {
					return 0;
				} else if (result == 'B') {
				} else if (result == 'S') {
				} else if (result == 'T') {
				}
				break;
			case 'B':
				if (!graphIsNull()) {
				    result = addVertex();	
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
