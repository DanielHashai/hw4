#include "algo.h"

void doDijkstra() {

    int from = getInt();
    int to = getInt();

    dijkstra(from);

    printGraph();
    
}

void dijkstra(int from) {

	if (DEBUG_EN) printf("%s %d [dijkstra] start from(%d)\n", __FILE__, __LINE__, from);

	Vertex *toVisit[numVertices], *current;
	int top = -1;
	toVisit[++top] = vertices[from];

	// Set the source weight to be 0, since it needs not be traversed
	vertices[from]->smallestWeight = 0;

	while((current = toVisit[top--])) {
		Edge *edge = current->edges->head;

		while(edge != null) {
			// Current weight is the previous vertex's smallest weight plus the edge
			int weight = current->smallestWeight + edge->weight;
			if(weight < edge->to->smallestWeight) {
				edge->to->smallestWeight = weight;
				toVisit[++top] = edge->to;
			}
			edge = edge->next;
		}
		if(top == -1) break;
	}

	if (DEBUG_EN) printf("%s %d [dijkstra] start\n", __FILE__, __LINE__);
}
