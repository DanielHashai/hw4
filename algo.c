#include "algo.h"

void dijkstra(Vertex *vertices[], int size, int from) {
	printf("\n\nDijkstra-ing\n");
	Vertex *toVisit[size], *current;
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
}
