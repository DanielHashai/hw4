#include "edges.h"

bool listIsNull() {
	return ((list == null) ? true : false);
}

void visit(Vertex *vertex) {
	printf("Visiting %c\n", vertex->value);
	vertex->visited = true;
}

bool isVisited(Vertex *vertex) {
	return vertex->visited;
}

void printList(Vertex *vertices[], int size, int from) {
	Vertex *toVisit[size], *current;
	int top = -1;
	toVisit[++top] = vertices[from];
	while((current = toVisit[top--])) {
		if(isVisited(current) == false) {
			visit(current);
			Edge *iterator = current->edges->head;
			while(iterator != null) {
				toVisit[++top] = iterator->to;
				iterator = iterator->next;
			}
		}
		if(top == -1) break;
	}
}

void printEdge(Edge edge) {
	if (!DEBUG_EN) return;
	char str[MAX_STR];
	str[MAX_STR-1] = '\0';
	char *nextExists = edge.next == null ? "false" : "true";
	int totalRead = sscanf(str, "\tto(%d) weight(%d) nextExists(%s)", &edge.to->value, &edge.weight, nextExists);
	
	if (DEBUG_EN) {
		printf("%s %d totalRead(%d) %s\n",  __FILE__, __LINE__, totalRead, str);
	}
}

void printVertex(Vertex vertex) {

	if (!DEBUG_EN) return;

	char trueStr[MAX_STR] = "true";
	char falseStr[MAX_STR] = "false";

	char str[MAX_STR];
	str[MAX_STR-1] = '\0';
	int totalRead = sscanf(str, "value(%d) smallestWeight(%d) visited(%s)", &vertex.value, &vertex.smallestWeight,vertex.visited ? trueStr : falseStr );

	if (DEBUG_EN) {
		printf("%s %d totalRead(%d) %s\n", __FILE__, __LINE__, totalRead, str);
	}

	Edge *edge = vertex.edges->head;
	while (edge != null) {
		printEdge(*edge);
		edge = edge->next;
	}
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
	vertex->visited = false;
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

// input - CMD NUM_EDGES n EDGE_VALUE TO WEIGHT TO WEIGHT ... n EDGE_VALUE ..
char createUserList() {

	int size;
	char dummy;

	scanf("%d", &size);
	dummy = getChar();


	list = createLinkedList(size);
	list->size = size;
	vertices = (Vertex **) malloc(sizeof(Vertex*) * size);

	for (int i = 0; i < size; i ++) {
		int value;
		char weight;

		scanf("%d", &value);
		vertices[i] = createVertex(value);

		if (DEBUG_EN) printf("%s %d size(%d) dummy(%c) vertice_i(%d) value(%d)\n", __FILE__, __LINE__, size, dummy, i, value);

		weight = getChar();

		while (isInt(weight)) {
			insertIntoList(createEdge(atoi(&weight), vertices[i]));
			weight = getChar();
		}

		if (weight == DIVIDER) {
			printVertex(*vertices[i]);
			continue;
		} else {
			printVertex(*vertices[i]);
			return weight;
		}

	}

	return 255; // dummy success return value

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
