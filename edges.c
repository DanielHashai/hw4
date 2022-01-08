#include "edges.h"

bool graphIsNull() {
	return ((numVertices == 0) ? true : false);
}

void visit(Vertex *vertex) {
	printf("Visiting %c\n", vertex->value);
	vertex->visited = true;
}

bool isVisited(Vertex *vertex) {
	return vertex->visited;
}

void printList(Vertex *in[], int size, int from) {
	Vertex *toVisit[size], *current;
	int top = -1;
	toVisit[++top] = in[from];
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

void printEdge(Edge *edge) {

	if (DEBUG_EN) {
		printf("%s %d [edge] to(%d) weight(%d) nextExists(%s)\n",  __FILE__, __LINE__, edge->to->value, edge->weight, edge->next == null ? "false" : "true");
	}

}

void printVertex(Vertex *vertex) {

	if (!DEBUG_EN) return;

	char trueStr[MAX_STR] = "true";
	char falseStr[MAX_STR] = "false";

	if (DEBUG_EN) {
		printf("%s %d [vertex] value(%d) smallestWeight(%d) visited(%s) numConnections(%d)\n", __FILE__, __LINE__, vertex->value, vertex->smallestWeight,vertex->visited ? trueStr : falseStr, vertex->edges->size);
	}

	Edge *edge = (vertex->edges != null) ? vertex->edges->head : null;
	while (edge != null) {
		printEdge(edge);
		edge = edge->next;
	}

	if (DEBUG_EN) {
		printf("----------------------------------------------\n");
	}
}


Edge *createEdge(int weight, Vertex *to) {
	Edge *edge = (Edge *) malloc(sizeof(Edge));
	edge->weight = weight;
	edge->to = to;
	edge->next = null;
	return edge;
}

Vertex *createVertex() {
	Vertex *vertex = (Vertex * ) malloc(sizeof(Vertex));
	vertex->value = -1;
	vertex->edges = null;
	vertex->smallestWeight = MAX_WEIGHT;
	vertex->visited = false;
	return vertex;
}

LinkedList *createLinkedList() {
	LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
	list->head = null;
	list->tail = null;
	list->size = 0;
	return list;
}

void insertIntoList(LinkedList *list, Edge *edge) {
	if(list->head == null) {
		list->head = edge;
		list->tail = edge;
	} else {
		list->tail->next = edge;
		list->tail = edge;
	}
	list->size++;
}

int getVertexId(int value) {
    int ret = -1;
    for (int i = 0; i < numVertices; i++) {
	if (vertices[i]->value != value) continue;
	ret = i;
	break;
    }
    if (DEBUG_EN) printf("%s %d [getVertexId] value(%d) id(%d)\n", __FILE__, __LINE__, value, ret);
    return ret;
}

int getFreeVertexId() {
    int ret = -1;
    for (int i = 0; i < numVertices; i++) {
	if (vertices[i]->value != -1) continue;
	ret = i;
	break;
    }
    if (DEBUG_EN) printf("%s %d [getFreeVertexId] id(%d)\n", __FILE__, __LINE__, ret);
    return ret;
}

// input - CMD NUM_EDGES n EDGE_VALUE TO WEIGHT TO WEIGHT ... n EDGE_VALUE ..
char createUserList() {

	int size;
	char dummy;

	scanf("%d", &size);
	dummy = getChar();
	numVertices = size;

	vertices = (Vertex **)malloc(sizeof(Vertex*) * size);

	for (int i = 0; i < size; i++) {
		vertices[i] = createVertex();
	}

	int vertexCnt = size;
	while (vertexCnt > 0) {

		vertexCnt--;

		int value, weight;
		char toValue;

		scanf("%d", &value);

		int i = getVertexId(value) != -1 ? getVertexId(value) : getFreeVertexId();
		vertices[i]->value = value;

		if (DEBUG_EN) printf("%s %d size(%d) dummy(%c) vertice_i(%d) value(%d)\n", __FILE__, __LINE__, size, dummy, i, value);

		toValue = getChar();

		if (toValue == DIVIDER) continue;
		if (!isInt(toValue)) return toValue;

		LinkedList *list = createLinkedList();

		while (isInt(toValue)) {
			scanf("%d", &weight);
			int toVertexId = getVertexId(atoi(&toValue));
			if (toVertexId == -1) { // if vertex doesnt exist yet, set the next available vertex to the toValue, otherwise take existing vertex pointer
			    toVertexId = getFreeVertexId();
			    vertices[toVertexId]->value = atoi(&toValue);
			}
			Vertex *toVertex = vertices[toVertexId];
			
			insertIntoList(list, createEdge(weight, toVertex));

			toValue = getChar();
		}
		vertices[i]->edges = list;

		if (toValue == DIVIDER) {
			printVertex(vertices[i]);
			continue;
		} else {
			printVertex(vertices[i]);
			return toValue;
		}

	}

	return CHAR_SUCCESS; // dummy success return value

}

void deleteGraph() {
	for (int i = 0; i < numVertices; i++) {
	    deleteVertex(vertices[i]);
	}
}

void deleteEdge(Edge *current) {

	if (current == null) return;

	Edge *next = current->next;

	deleteEdge(next);
	free(current);

}

void deleteVertex(Vertex *current) {

	if (current == null) return;

	if (current->edges != null) {
	    deleteEdge(current->edges->head);
	}
	free(current);

}

char addVertex() {

    char value, toValue;
    bool vertexExists = false;

    value = getChar();
    if (!isInt(value)) return value;

    Vertex *newVertex = createVertex();
    newVertex->value = atoi(&value);
    
    toValue = getChar();
    LinkedList *list = createLinkedList();
    while (isInt(toValue)) {
	int weight;
	scanf("%d", &weight);
	int toVertexId = getVertexId(atoi(&toValue));
	Vertex *toVertex = vertices[toVertexId];
    	insertIntoList(list, createEdge(weight, toVertex));
	toValue = getChar();
    }
    newVertex->edges = list;

    printVertex(newVertex);

    if (numVertices == 0) { // shouldn't happen and will happen if input isn't valid
	return '\0';
    }

    for (int i = 0; i < numVertices; i++) {
	if (vertices[i]->value != atoi(&value)) continue; // continue loop until value matches a vertex value that we already have
	vertexExists = true;
	break;
    }

    // if vertex doesn't exist size of graph will increment by one, otherwise vertex exists and just need to update
    int oldSize = numVertices;
    int newSize = (vertexExists) ? oldSize : oldSize + 1;
    numVertices = newSize;

    Vertex **newVertices = (Vertex **) malloc(sizeof(Vertex*) * newSize);
    for (int i = 0; i < oldSize; i++) {
	if (vertices[i]->value != atoi(&value)) {
	    // copy vertex to new vertex array
	    newVertices[i] = vertices[i];
	    continue;
	} else {
	    // value exists and therefore need to delete and then update in array
	    if (DEBUG_EN) printf("%s %d [addVertex] delete vertex(%d) at i(%d)\n", __FILE__, __LINE__, atoi(&value), i);
	    printVertex(vertices[i]);
	    deleteVertex(vertices[i]);
	    newVertices[i] = newVertex;
	}
    }

    if (!vertexExists) { // if vertex isn't in list, then previous for loop didn't insert the new vertex, therefore add to last index in array 
	newVertices[newSize-1] = newVertex;
    }

    free(vertices); // free older pointer of vertices
    vertices = newVertices;
    if (DEBUG_EN) printf("%s %d [addVertex] add vertex(%d) numVertices(%d) vertexExists(%d)\n", __FILE__, __LINE__, atoi(&value), numVertices, vertexExists);

    return toValue;

}
