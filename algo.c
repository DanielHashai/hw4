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

    if (DEBUG_EN) printf("%s %d [doDijkstra] start from(%d) to(%d)\n", __FILE__, __LINE__, from, to);

    int **graph = allocateTwoDimenArrayOnHeapUsingMalloc(numVertices, numVertices);

    for (int i = 0; i < numVertices; i++) {
	Vertex *from = vertices[i];
	for (int j = 0; j < numVertices; j++) {
	    Vertex *to = vertices[j];
	    graph[i][j] = getWeight(from->value, to->value);
    	}
    }

    for (int i = 0; i < numVertices; i++) {
	Vertex *from = vertices[i];
	if (DEBUG_EN) printf("%s %d [doDijkstra] graph[%d/%d]: ", __FILE__, __LINE__, i, vertices[i]->value);
	for (int j = 0; j < numVertices; j++) {
	    if (DEBUG_EN) printf("%d ", graph[i][j]);
    	}
	if (DEBUG_EN) printf("\n");
    }

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

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = MAX_WEIGHT, min_index;

    for (int v = 0; v < numVertices; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    if (DEBUG_EN) printf("%s %d [minDistance] done\n", __FILE__, __LINE__);

    return min_index;
}
