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

void visitGraph(int from) {
	Vertex *toVisit[numVertices], *current;
	int top = -1;
	toVisit[++top] = vertices[from];
	while((current = toVisit[top--])) {
		if(isVisited(current) == false) {
			visit(current);
			Edge *iterator = current->edges != null ? current->edges->head : null;
			while(iterator != null) {
				toVisit[++top] = iterator->to;
				iterator = iterator->next;
			}
		}
		if(top == -1) break;
	}
}

void printGraph() {

	if (DEBUG_EN) {
	    printf("%s %d [GRAPH] numVertices(%d)\n", __FILE__, __LINE__, numVertices);
	    for (int i = 0; i < numVertices; i++) {
		printf("%s %d [GRAPH] id(%d)\n", __FILE__, __LINE__, i);
		printVertex(vertices[i]);
	    }
	}

}

void printEdge(Edge *edge) {

	if (DEBUG_EN) {
		printf("%s %d [EDGE] to(%d) weight(%d) next(%d)\n",  __FILE__, __LINE__, edge->to->value, edge->weight, edge->next == null ? -1 : edge->next->to->value);
	}

}

void printVertex(Vertex *vertex) {

	if (!DEBUG_EN) return;

	char trueStr[MAX_STR] = "true";
	char falseStr[MAX_STR] = "false";

	if (DEBUG_EN) {
	    printf("%s %d [VERTEX] value(%d) head_value(%d) tail_value(%d) visited(%s) numConnections(%d)\n", __FILE__, __LINE__, 
		    vertex->value, 
		    vertex->edges != null && vertex->edges->head != null && vertex->edges->head->to != null ? vertex->edges->head->to->value : -1, 
		    vertex->edges != null && vertex->edges->head != null && vertex->edges->tail->to != null ? vertex->edges->tail->to->value : -1, 
		    vertex->visited ? trueStr : falseStr, 
		    vertex->edges != null ? vertex->edges->size : 1
	    );
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
    if (DEBUG_EN && EXTRA_DEBUG_EN) printf("%s %d [getVertexId] value(%d) id(%d)\n", __FILE__, __LINE__, value, ret);
    return ret;
}

int getFreeVertexId() {
    int ret = -1;
    for (int i = 0; i < numVertices; i++) {
	if (vertices[i]->value != -1) continue;
	ret = i;
	break;
    }
    if (DEBUG_EN && EXTRA_DEBUG_EN) printf("%s %d [getFreeVertexId] id(%d)\n", __FILE__, __LINE__, ret);
    return ret;
}

// input - CMD NUM_EDGES n EDGE_VALUE TO WEIGHT TO WEIGHT ... n EDGE_VALUE ..
char createUserList() {

	if (DEBUG_EN) printf("%s %d [createUserList] start\n", __FILE__, __LINE__);

	int size = getInt();
	char dummy = getChar();

	numVertices = size;

	vertices = (Vertex **)malloc(sizeof(Vertex*) * size);

	for (int i = 0; i < size; i++) {
		vertices[i] = createVertex();
	}

	int vertexCnt = size;
	while (vertexCnt > 0) {

		vertexCnt--;

		int value = getInt();

		int vertexId = getVertexId(value);
		int i = vertexId != -1 ? vertexId : getFreeVertexId();
		vertices[i]->value = value;

		if (DEBUG_EN && EXTRA_DEBUG_EN) printf("%s %d [createUserList] size(%d) dummy(%c) vertice_id(%d) value(%d) vertexCnt(%d)\n", __FILE__, __LINE__, size, dummy, i, value,vertexCnt+1);

		char toValue = getChar();

		if (toValue == DIVIDER) {
		    if (EXTRA_DEBUG_EN) printVertex(vertices[i]);
		    continue;
		}
		if (!isInt(toValue)) {
		    if (DEBUG_EN) printf("%s %d [createUserList] done \n", __FILE__, __LINE__);
		    return toValue;
		}

		LinkedList *list = createLinkedList();

		while (isInt(toValue)) {
			int weight = getInt();
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
			if (EXTRA_DEBUG_EN) printVertex(vertices[i]);
			continue;
		} else {
			if (EXTRA_DEBUG_EN) printVertex(vertices[i]);
			return toValue;
		}

	}

	return CHAR_SUCCESS; // dummy success return value

}

void freeGraph() {
	for (int i = 0; i < numVertices; i++) {
	    freeVertex(vertices[i]);
	}
}

void freeEdge(Edge *current) {

	if (current == null) return;

	Edge *next = current->next;

	freeEdge(next);
	free(current);

}

void freeVertex(Vertex *current) {

	if (current == null) return;

	if (current->edges != null) {
	    freeEdge(current->edges->head);
	}
	//free(current); TODO for some reason this screws me over, i thought i need to free here...

}

char addVertex() {

    if (DEBUG_EN) printf("%s %d [addVertex] start\n", __FILE__, __LINE__);

    bool vertexExists = false;

    char value = getChar();
    if (!isInt(value)) return value;

    Vertex *newVertex = createVertex();
    newVertex->value = atoi(&value);
    
    LinkedList *list = createLinkedList();
    char toValue = getChar();
    while (isInt(toValue)) {
	int weight = getInt();
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
    Vertex **verticesToRemove = vertices;

    for (int i = 0; i < oldSize; i++) {

	if (vertices[i]->value != atoi(&value)) {
	    // copy vertex to new vertex array
	    newVertices[i] = vertices[i];
	    continue;
	} 
	
	// value exists and therefore need to delete and then update in array
	if (DEBUG_EN) printf("%s %d [addVertex] DELETE vertex(%d) at id(%d)\n", __FILE__, __LINE__, atoi(&value), i);
	printVertex(vertices[i]);
    
	Vertex *vertexToRemove = vertices[i];
	newVertices[i] = newVertex;
	freeVertex(vertexToRemove);

    }

    if (!vertexExists) { // if vertex isn't in list, then previous for loop didn't insert the new vertex, therefore add to last index in array 
	newVertices[newSize-1] = newVertex;
    }

    vertices = newVertices;
    free(verticesToRemove); // free older pointer of vertices
    if (DEBUG_EN) printf("%s %d [addVertex] ADD vertex(%d) numVertices(%d) vertexExists(%d)\n", __FILE__, __LINE__, atoi(&value), numVertices, vertexExists);

    if (DEBUG_EN) printf("%s %d [addVertex] done ret(%c)\n", __FILE__, __LINE__, toValue);
    return toValue;

}

void deleteEdgeFromList(Vertex *vertex, int valueToRemove) {

    if (vertex->edges == null) return;

    bool hasEdge = false;
    Edge *iterator = vertex->edges->head;
    while (iterator != null) {
	if (iterator->to->value == valueToRemove) {
	    hasEdge = true;
	    break;
	}
	iterator = iterator->next;
    }
    if (!hasEdge) return;

    vertex->edges->size--;

    if (vertex->edges->head->to->value == valueToRemove) {
	if (DEBUG_EN && EXTRA_DEBUG_EN) printf("%s %d [deleteEdgeFromList] head value %d\n", __FILE__, __LINE__, valueToRemove);
	Edge *edgeToRemove = vertex->edges->head;
	vertex->edges->head = vertex->edges->head->next;
	free(edgeToRemove);
	return;
    }

    iterator = vertex->edges->head->next;
    Edge *previous = vertex->edges->head;
    while (iterator != null) {
	if (DEBUG_EN && EXTRA_DEBUG_EN) printf("%s %d [deleteEdgeFromList] valueToRemove(%d) iterator_value(%d)\n", __FILE__, __LINE__, valueToRemove, iterator->to->value);
	if (iterator->to->value == valueToRemove) {
	    Edge *edgeToRemove = iterator;
	    previous->next = iterator->next;
	    if (iterator->to->value == vertex->edges->tail->to->value) {
		vertex->edges->tail = previous;
	    }
	    free(edgeToRemove);
	    return;
	}
        previous = iterator;
        iterator = iterator->next;
    }
}

void deleteVertex() {

    if (DEBUG_EN) printf("%s %d [deleteVertex] done\n", __FILE__, __LINE__);

    int value = getInt();
    int vertexId = getVertexId(value);

    for (int i = 0; i < numVertices; i++) {
	if (vertexId == i) continue;
	deleteEdgeFromList(vertices[i], value);
    }
    printGraph();

    Vertex **newVertices = (Vertex **) malloc(sizeof(Vertex*) * (numVertices-1)); // removing vertice so need to allocate less memory

    for (int new_i = 0, old_i = 0; old_i < numVertices; old_i++) {

	if (vertices[old_i]->value != value) {
	    // copy vertex to new vertex array
	    newVertices[new_i++] = vertices[old_i];
	    continue;
	}

	// value == the vertex that we should delete
	freeVertex(vertices[old_i]);

    }

    numVertices--;
    Vertex **verticesToRemove = vertices;
    vertices = newVertices;
    free(verticesToRemove);

    if (DEBUG_EN) printf("%s %d [deleteVertex] done numVertices(%d)\n", __FILE__, __LINE__, numVertices);

}

int getWeight(int from, int to) {

    int ret = 0;

    int fromId = getVertexId(from);
    Vertex *fromVertex = vertices[fromId];

    Edge *iterator = fromVertex->edges != null && fromVertex->edges->head != null ? fromVertex->edges->head : null;
    while (iterator != null && (from != to)) {
	if (iterator->to->value == to) {
	    ret = iterator->weight;
	    break;
	}
	iterator = iterator->next;
    }

    if (DEBUG_EN && EXTRA_DEBUG_EN) printf("%s %d [getWeight] from(%d) to(%d) weight(%d)\n", __FILE__, __LINE__, from, to, ret);

    return ret;
}
