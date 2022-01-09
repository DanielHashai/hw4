#include <stdio.h>
#include "nodes.h"
#include "edges.h"
#include <math.h>

void doDijkstra();
int* dijkstra(int **G,int startnode);
int **allocateTwoDimenArrayOnHeapUsingMalloc(int row, int col);
void destroyTwoDimenArrayOnHeapUsingFree(int ** ptr, int row, int col);
void printSolution(int dist[]);
char doTSP();
void TSP(int* C, int* A, int* path, int* fpath, int *sum, int *fsum, int flag, int b, int a, int *sc);
int travelingSalesmanProblem(int **graph, int *verticesInPath, int numVerticesInPath);
int** getGraph();
void print2DGraph(int **graph);
void swap(int *a, int *b);
int** getPermutations(int *elements, int size);
void permutation(int ** out, int *arr, int start, int end);
void print2DArray(int **arr, int row, int col);
void print1DArray(int arr[], int size);
bool vertexInList(int vertexValue, bool* vertexValid);
