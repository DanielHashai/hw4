#include <stdio.h>
#include "nodes.h"
#include "edges.h"

void doDijkstra();
int* dijkstra(int **G,int startnode);
int ** allocateTwoDimenArrayOnHeapUsingMalloc(int row, int col);
void destroyTwoDimenArrayOnHeapUsingFree(int ** ptr, int row, int col);
void printSolution(int dist[]);
int minDistance(int dist[], bool sptSet[]);
