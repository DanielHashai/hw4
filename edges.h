#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"

Edge *createEdge(int weight, Vertex *to);
Vertex *createVertex();
LinkedList *createLinkedList();
void insertIntoList(LinkedList *list, Edge *edge);
void deleteGraph();
char createUserList();
void deleteEdge(Edge *current);
bool graphIsNull();
char addVertex();
void deleteVertex(Vertex *current);

int numVertices;
Vertex **vertices;

#define DIVIDER 'n'
