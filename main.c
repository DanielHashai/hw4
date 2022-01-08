#include <stdio.h>
#include "algo.h"
#include "nodes.h"
#include "edges.h"

int main() {

	while (true) {

		char cmd = getChar();

		if (cmd == '\0') return 0;

		switch (cmd) {
			case 'A':
				if (!listIsNull()) {
					deleteList();
				}
				char result = createUserList();
				if ((result == '\0') || (result == EOF) || (result == 255)) {
					return 0;
				} else if (result == 'B') {
				} else if (result == 'S') {
				} else if (result == 'T') {
				}
				break;
			case 'B':
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
