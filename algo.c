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

     printf("Dijsktra shortest path: %0d\n", minPathWeights[getVertexId(to)]);

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
    for (int i = 0; i < numVerticesInPath; i++) {
	if (DEBUG_EN) printf("%d ", vertexIsInPath[i]);
    }
    if (DEBUG_EN) printf("\n");

    int **graph = getGraph();
    int tspShortestPath = travelingSalesmanProblem(graph, vertexIsInPath, numVerticesInPath);

    printf("TSP shortest path: %0d\n", tspShortestPath);

    free(vertexIsInPath);
    destroyTwoDimenArrayOnHeapUsingFree(graph, numVertices,numVertices);

    return getCharOnly();
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static int permutationRowId = 0;

//function to print the array
void updateOut(int **out, int arr[], int size)
{
    int rowId = permutationRowId++;
    if (DEBUG_EN && TSP_DEBUG_EN && EXTRA_DEBUG_EN) printf("%s %d [updateOut] row(%d) size(%d)\n", __FILE__, __LINE__, rowId, size);
    if (DEBUG_EN && TSP_DEBUG_EN && EXTRA_DEBUG_EN) print1DArray(arr, size);
    for(int i=0; i<size; i++)
    {
	out[rowId][i] = arr[i];
    }
    if (DEBUG_EN && TSP_DEBUG_EN && EXTRA_DEBUG_EN) printf("\n");
}

void print1DArray(int arr[], int size)
{
    if (DEBUG_EN) printf("%s %d [print1DArray] size(%d) arr: ", __FILE__,__LINE__, size);
    for (int i = 0; i < size; i++) {
	if (DEBUG_EN) printf("%d ", arr[i]);
    }
    if (DEBUG_EN) printf("\n");
}

void print1DVertexBoolArray(bool arr[], int size)
{
    if (DEBUG_EN) printf("%s %d [print1DBoolArray] size(%d) arr: ", __FILE__,__LINE__, size);
    for (int i = 0; i < size; i++) {
	if (DEBUG_EN) printf("%d ", arr[i]);
    }
    if (DEBUG_EN) printf("\n");
}

void print2DArray(int **arr, int row, int col)
{
    for(int i=0; i<row; i++) {
	if (DEBUG_EN) printf("%s %d [print2DArray] row %d:\t", __FILE__, __LINE__, i);
	for(int j=0; j<col; j++) {
	    if (DEBUG_EN) printf("%d\t", arr[i][j]);
	}
	if (DEBUG_EN) printf("\n");
    }
}

//permutation function
void permutation(int **out, int *arr, int start, int end)
{
    if(start==end)
    {
        updateOut(out, arr, end+1);
        return;
    }
    int i;
    for(i=start;i<=end;i++)
    {
        //swapping numbers
        swap((arr+i), (arr+start));
        //fixing one first digit
        //and calling permutation on
        //the rest of the digits
        permutation(out, arr, start+1, end);
        swap((arr+i), (arr+start));
    }
}

unsigned factorial(unsigned n)
{
    int fact = 1;
     for(int i=1;i<=n;i++){    
	fact=fact*i;    
     }    
    if (DEBUG_EN) printf("%s %d [factorial] n(%d) fact(%d)\n", __FILE__, __LINE__, n, fact);
    return fact;
}

int** getPermutations(int *elements, int size) {
    if (DEBUG_EN && EXTRA_DEBUG_EN) print1DArray(elements, size);
    int numOfPermutations = factorial(size);
    int **ret = allocateTwoDimenArrayOnHeapUsingMalloc(numOfPermutations, size);
    permutation(ret, elements, 0, size-1);
    return ret;
}

bool vertexInList(int vertexValue, bool* vertexValid) {
    int vertexId = getVertexId(vertexValue);
    return vertexValid[vertexId];
}


// implementation of traveling Salesman Problem
int travelingSalesmanProblem(int **graph, int *verticesInPath, int numVerticesInPath)
{

    int numOfPermutations = factorial(numVertices);;
    int *verticesValueList = getVerticesValueList();
    int **verticesPermutations = getPermutations(verticesValueList, numVertices);
    int minPath = MAX_WEIGHT;

    if (DEBUG_EN) printf("%s %d [TSP] start numOfPermutations(%d) minPath(%d) permutationRowId(%d)\n", __FILE__, __LINE__, numOfPermutations, minPath, permutationRowId);
    print2DArray(verticesPermutations, numOfPermutations, numVertices);
    print1DArray(verticesInPath, numVerticesInPath);

    int numValidRows = (permutationRowId < numOfPermutations) ? permutationRowId : numOfPermutations;
    
    for (int i = 0; i < numValidRows; i++) {
	int *currentVerticesPermutation = verticesPermutations[i];

	// store current Path weight(cost)
        int currentPathWeight = 0;

    	// compute current path weight
	int fromValue = currentVerticesPermutation[0];
	int fromGraphId = getVertexId(fromValue);
	bool* vertexIsInPath = (bool *)malloc(sizeof(bool)*numVertices);
    	for (int k = 0; k < numVertices; k++) {
	    vertexIsInPath[k] = false;
	}
	if (DEBUG_EN) printf("%s %d [TSP] permutation %d\n=============\n", __FILE__, __LINE__, i);
	print1DArray(currentVerticesPermutation, numVertices);
    	for (int j = 1; j < numVertices; j++) {

	print1DArray(currentVerticesPermutation, numVertices);
	    int toValue = currentVerticesPermutation[j];
	    int toGraphId = getVertexId(toValue);
    	    int pathWeight = graph[fromGraphId][toGraphId];

	    vertexIsInPath[fromGraphId] = true;

	    if (pathWeight == 0) {
		currentPathWeight = 0;
		break;
	    }
	   //if (DEBUG_EN) printf("%s %d [TSP] from(%d) to(%d) pathWeight(%d) j(%d)\n", __FILE__, __LINE__, fromValue, toValue, pathWeight, j);

//    if (DEBUG_EN) printf("%s %d [TSP] here\n", __FILE__, __LINE__);
	    vertexIsInPath[toGraphId] = true;

//    if (DEBUG_EN) printf("%s %d [TSP] here\n", __FILE__, __LINE__);
    	    currentPathWeight += pathWeight;
    	    fromValue = currentVerticesPermutation[j];
	    fromGraphId = getVertexId(toValue);

 //   if (DEBUG_EN) printf("%s %d [TSP] here\n", __FILE__, __LINE__);
	    bool allPathsAreInList = true;
    	    for (int k = 0; k < numVerticesInPath; k++) {
    	        if (vertexInList(verticesInPath[k], vertexIsInPath)) continue;
    	        allPathsAreInList = false;
    	        break;
    	    }
	    if (allPathsAreInList) break;
    	}

	bool allPathsAreInList = true;
    	for (int j = 0; j < numVerticesInPath; j++) {
	    if (vertexInList(verticesInPath[j], vertexIsInPath)) continue;
	    allPathsAreInList = false;
	    break;
	}

	bool updateMin = (currentPathWeight != 0) && (currentPathWeight < minPath)  && allPathsAreInList;
 
	if (DEBUG_EN) printf("%s %d [TSP] from(%d) to(%d) currentPathWeight(%d) i(%d) updateMin(%d) allPathsAreInList(%d) minPath(%d)\n", __FILE__, __LINE__, currentVerticesPermutation[0], currentVerticesPermutation[numVerticesInPath-1], currentPathWeight, i, updateMin, allPathsAreInList, minPath);

    	// update minimum
    	minPath = updateMin ? currentPathWeight : minPath;

    }

    if (DEBUG_EN) printf("%s %d [TSP] before deletes\n", __FILE__, __LINE__);
    destroyTwoDimenArrayOnHeapUsingFree(verticesPermutations, numVertices,numVertices);
    free(verticesValueList);
    permutationRowId = 0; // initialize for next call

    return minPath == MAX_WEIGHT ? -1 : minPath;
}
