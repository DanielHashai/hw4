#include <stdio.h>
#include "nodes.h"
#include "edges.h"

void doDijkstra();
void dijkstra(int **graph, int src);
int ** allocateTwoDimenArrayOnHeapUsingMalloc(int row, int col);
void destroyTwoDimenArrayOnHeapUsingFree(int ** ptr, int row, int col);
void printSolution(int dist[]);
int minDistance(int dist[], bool sptSet[]);
