#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"

Edge *createEdge(int weight, Vertex *to);
Vertex *createVertex(int value);
LinkedList *createLinkedList(int size);
void insertIntoList(Edge *edge);
void deleteList();
char createUserList();
void deleteEdge(Edge *current);
bool listIsNull();

Vertex **vertices;
LinkedList *list;

#define DIVIDER 'n'
