#include "algo.h"

void destroyTwoDimenArrayOnHeapUsingFree(int ** ptr, int row, int col)
{
    for(int i = 0; i < row; i++)
    {
        free(ptr[i]);
    }
    free(ptr);
}

int ** allocateTwoDimenArrayOnHeapUsingMalloc(int row, int col)
{
    int ** ptr = (int **) malloc(sizeof(int *)*row);
    for(int i = 0; i < row; i++)
    {
        ptr[i] = (int *) malloc(sizeof(int)*col);
    }
    return ptr;
}

void doDijkstra() {

    int from = getInt();
    int to = getInt();

    int **graph = allocateTwoDimenArrayOnHeapUsingMalloc(numVertices, numVertices);

    for (int i = 0; i < numVertices; i++) {
	Vertex *from = vertices[i];
	for (int j = 0; j < numVertices; j++) {
	    if (i == j) continue;
	    Vertex *to = vertices[j];
	    graph[i][j] = getWeight(from->value, to->value);
    if (DEBUG_EN) printf("%s %d graph[%d][%d] %d\n", __FILE__, __LINE__, i, j, graph[i][j]);
    	}
    }

    dijkstra(graph, from);

    
}

// A utility function to print the constructed distance array
void printSolution(int dist[])
{
    if (DEBUG_EN) printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < numVertices; i++)
        if (DEBUG_EN) printf("%d \t\t %d\n", i, dist[i]);
}

void dijkstra(int **graph, int src)
{
    int *dist = (int*)(malloc(sizeof(int)*numVertices)); // The output array.  dist[i] will hold the shortest
    // distance from src to i

    bool *sptSet = (bool*)(malloc(sizeof(bool)*numVertices)); // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < numVertices; i++)
        dist[i] = MAX_WEIGHT, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < numVertices - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < numVertices; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != MAX_WEIGHT
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // print the constructed distance array
    printSolution(dist);
}

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = MAX_WEIGHT, min_index;

    for (int v = 0; v < numVertices; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}
