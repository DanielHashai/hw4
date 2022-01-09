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

int** getGraph() {
    int** graph = allocateTwoDimenArrayOnHeapUsingMalloc(numVertices, numVertices);

    for (int i = 0; i < numVertices; i++) {
	Vertex *from = vertices[i];
	for (int j = 0; j < numVertices; j++) {
	    Vertex *to = vertices[j];
	    graph[i][j] = getWeight(from->value, to->value);
    	}
    }

    print2DGraph(graph);

    return graph;
}

void print2DGraph(int **graph) {
    for (int i = 0; i < numVertices; i++) {
	if (DEBUG_EN) printf("%s %d [print2DGraph] graph[%d/%d]: ", __FILE__, __LINE__, i, vertices[i]->value);
	for (int j = 0; j < numVertices; j++) {
	    if (DEBUG_EN) printf("%d ", graph[i][j]);
    	}
	if (DEBUG_EN) printf("\n");
    }
}

void doDijkstra() {

    int from = getInt();
    int to = getInt();

    if (DEBUG_EN) printf("%s %d [doDijkstra] start from(%d) to(%d)\n", __FILE__, __LINE__, from, to);

    int **graph = getGraph();

    int *minPathWeights = dijkstra(graph, from);
    printSolution(minPathWeights);

     printf("Dijsktra shortest path: %d\n", minPathWeights[getVertexId(to)]);

    destroyTwoDimenArrayOnHeapUsingFree(graph, numVertices,numVertices);
    free(minPathWeights);

    
}

// A utility function to print the constructed distance array
void printSolution(int dist[])
{
    if (DEBUG_EN) printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < numVertices; i++)
        if (DEBUG_EN) printf("%d \t\t %d\n", i, dist[i]);
}

int* dijkstra(int **G,int startnode)
{
    int startnodeId = getVertexId(startnode);

    if (DEBUG_EN) printf("%s %d [dijkstra] startnode(%d) startnodeId(%d)\n", __FILE__, __LINE__, startnode, startnodeId);

    int **cost = allocateTwoDimenArrayOnHeapUsingMalloc(numVertices, numVertices);
    int *distance = (int *)(malloc(sizeof(int)*numVertices));
    int *pred = (int *)(malloc(sizeof(int)*numVertices));
    bool *visited = (bool *)(malloc(sizeof(bool)*numVertices));
    int count,mindistance,nextnode,i,j;
    //pred[] stores the predecessor of each node
    //count gives the number of nodes seen so far
    //create the cost matrix
    for(i=0;i<numVertices;i++)
	for(j=0;j<numVertices;j++)
	    if(G[i][j]==0)
		cost[i][j]=MAX_WEIGHT;
	    else
		cost[i][j]=G[i][j];
    //initialize pred[],distance[] and visited[]
    
    for(i=0;i<numVertices;i++)
    {
	distance[i]=cost[startnodeId][i];
	pred[i]=startnode;
	visited[i]=false;
    }
    distance[startnodeId]=0;
    visited[startnodeId]=1;
    count=1;
    
    while(count<numVertices-1)
    {
	mindistance=MAX_WEIGHT;
	//nextnode gives the node at minimum distance
	for(i=0;i<numVertices;i++)
	    if(distance[i]<mindistance&&!visited[i])
	    {
		mindistance=distance[i];
		nextnode=i;
		if (DEBUG_EN && EXTRA_DEBUG_EN) printf("%s %d [dijkstra] nextnode %d count %d mindistance %d i %d\n", __FILE__, __LINE__,nextnode,count, mindistance, i);
	    }
	//check if a better path exists through nextnode
	visited[nextnode]=true;
	for(i=0;i<numVertices;i++) {
	    if(!visited[i]) {
		if(mindistance+cost[nextnode][i]<distance[i])
		{
		    distance[i]=mindistance+cost[nextnode][i];
		    pred[i]=nextnode;
		}
	    }
	}
	count++;
    }

    destroyTwoDimenArrayOnHeapUsingFree(cost, numVertices,numVertices);
    free(pred);
    free(visited);

    return distance;
}

//
//==============================================================================
//

char doTSP() {

    int numVerticesInPath = getInt();
    int *vertexIsInPath = (int*)(malloc(sizeof(int)*numVerticesInPath));
    for (int i = 0; i < numVerticesInPath; i++) {
	int value = getInt();
	vertexIsInPath[i] = value;

    }
    if (DEBUG_EN) printf("%s %d [doTSP] start numVerticesInPath(%d) vertixIsInPath: ", __FILE__, __LINE__, numVerticesInPath);
    for (int i = 0; i < numVertices; i++) {
	if (DEBUG_EN) printf("[%d/%d]-%s ", i, vertices[i]->value, vertexIsInPath[i] ? "true" : "false");
    }
    if (DEBUG_EN) printf("\n");

    int **graph = getGraph();
    int tspShortestPath = travelingSalesmanProblem(graph, vertexIsInPath, numVerticesInPath);

    printf("TSP shortest path: %d\n", tspShortestPath);

    free(vertexIsInPath);
    destroyTwoDimenArrayOnHeapUsingFree(graph, numVertices,numVertices);

    return getCharOnly();
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int** getVerticesPermutations(int numOfPermutations, int numVerticesInPath) {
    int **ret = allocateTwoDimenArrayOnHeapUsingMalloc(numOfPermutations, numVerticesInPath);

    return ret;
}

// implementation of traveling Salesman Problem
int travelingSalesmanProblem(int **graph, int *verticesInPath, int numVerticesInPath)
{

    int numOfPermutations = (int)pow(2, numVerticesInPath);
    int **verticesPermutations = getVerticesPermutations(numOfPermutations, numVerticesInPath);
    int minPath = MAX_WEIGHT;

    for (int i = 0; i < numOfPermutations; i++) {
	int *currentVerticesPermutation = verticesPermutations[i];

    	// store current Path weight(cost)
    	int currentPathWeight = 0;
 
    	// compute current path weight
	int fromValue = currentVerticesPermutation[0];
	int fromGraphId = getVertexId(fromValue);
    	for (int i = 1; i < numVerticesInPath; i++) {
	    int toValue = currentVerticesPermutation[i];
    	    int pathWeight = graph[fromValue][toValue];
    	    currentPathWeight = (pathWeight == 0) ? MAX_WEIGHT : currentPathWeight + pathWeight;
    	    fromValue = currentVerticesPermutation[i];
	    fromGraphId = getVertexId(fromValue);
    	}
 
    	// update minimum
    	minPath = (minPath < currentPathWeight) ? minPath : currentPathWeight;
 

    }

    destroyTwoDimenArrayOnHeapUsingFree(verticesPermutations, numVertices,numVertices);
 
    return minPath == MAX_WEIGHT ? -1 : minPath;
}
