#include "edges.h"

bool listIsNull() {
	return ((list == null) ? true : false);
}

Edge *createEdge(int weight, Vertex *to) {
	Edge *edge = (Edge *) malloc(sizeof(Edge));
	edge->weight = weight;
	edge->to = to;
	edge->next = null;
	return edge;
}

Vertex *createVertex(int value) {
	Vertex *vertex = (Vertex * ) malloc(sizeof(Vertex));
	vertex->value = value;
	vertex->edges = null;
	vertex->smallestWeight = MAX_WEIGHT;
	return vertex;
}

LinkedList *createLinkedList(int size) {
	LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
	list->head = null;
	list->tail = null;
	list->size = size;
	return list;
}

void insertIntoList(Edge *edge) {
	if(list->head == null) {
		list->head = edge;
		list->tail = edge;
	} else {
		list->tail->next = edge;
		list->tail = edge;
	}
}

void createUserList() {
	int size;
	char dummy;

	scanf("%d", &size);
	scanf("%c", &dummy);

	list = createLinkedList(size);
	vertices = (Vertex **) malloc(sizeof(Vertex*) * size);

	for (int i = 0; i < size; i ++) {
		char value, weight;

		scanf("%c", &value);
		vertices[i] = createVertex(value);


		scanf("%c", &weight);
		while (weight != DIVIDER) {
			insertIntoList(createEdge(weight, vertices[i]));
		}

	}

}

void deleteList() {
	for (int i = 0; i < list->size; i++) {
		deleteEdge(vertices[i]->edges->head);
		free(vertices[i]);
	}
}

void deleteEdge(Edge *current) {

	if (current == null) return;

	Edge *next = current->next;

	deleteEdge(next);
	free(current);

}
