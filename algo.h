#include <stdio.h>
#include "nodes.h"
#include "edges.h"

void doDijkstra();
int* dijkstra(int **G,int startnode);
int ** allocateTwoDimenArrayOnHeapUsingMalloc(int row, int col);
void destroyTwoDimenArrayOnHeapUsingFree(int ** ptr, int row, int col);
void printSolution(int dist[]);
char doTSP();
void TSP(int* C, int* A, int* path, int* fpath, int *sum, int *fsum, int flag, int n, int b, int a, int *sc);
