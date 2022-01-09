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
    bool *vertexIsInPath = (bool*)(malloc(sizeof(bool)*numVertices));
    for (int i = 0; i < numVertices; i++) {
	vertexIsInPath[i] = false;
    }
    for (int i = 0; i < numVerticesInPath; i++) {
	int value = getInt();
	int vertexId = getVertexId(value);
	vertexIsInPath[vertexId] = true;

    }
    if (DEBUG_EN) printf("%s %d [doTSP] start numVerticesInPath(%d) vertixIsInPath: ", __FILE__, __LINE__, numVerticesInPath);
    for (int i = 0; i < numVertices; i++) {
	if (DEBUG_EN) printf("[%d]-%s ", i, vertexIsInPath[i] ? "true" : "false");
    }
    if (DEBUG_EN) printf("\n");

    int tspShortestPath = -1;
    int **A = getGraph();

    for (int fromId = 0; fromId < numVertices; fromId++) {
	for (int toId = 0; toId < numVertices; toId++) {

            int sc=0;
	    
    	    int **C = allocateTwoDimenArrayOnHeapUsingMalloc(numVertices, numVertices);
    	    int sum=0,fsum=9999;
    	    int *path = (int*)malloc(sizeof(int)*(numVertices-1));
    	    int **fpath =  allocateTwoDimenArrayOnHeapUsingMalloc(1000, numVertices-1);

	    if (fromId == toId) continue;

	    // initialize array
	    for(int i=0;i<numVertices;i++)
		for(int j=0;j<numVertices;j++)
		    C[i][j]=0;

	    // set destination vertex
	    for(int i=0;i<numVertices;i++)
		C[i][toId] = toId;

	    TSP(C,A,path,fpath,&sum,&fsum,0,toId,fromId,&sc);

	    // check if there is a new minimum and if edges in path are what we got from user input
	    printf("\n\nMinimum traveled distance = %d.",fsum);
	    for(int i=0;i<=sc;i++){
    	        printf("\n\n\tpath direction type %d: %d -->",i+1,toId);
    	        for(int j=0;j<numVertices-1;j++)
    	            printf(" %d -->",fpath[i][j]+1);
    	        printf(" %d -> %d",fromId, toId);
    	    }
    	    printf("\n\n\n");

	    destroyTwoDimenArrayOnHeapUsingFree(C, numVertices,numVertices);
	    free(path);
	    destroyTwoDimenArrayOnHeapUsingFree(fpath, 1000, numVertices-1);

	}
    }

    printf("TSP shortest path: %d\n", tspShortestPath);

    free(vertexIsInPath);
    destroyTwoDimenArrayOnHeapUsingFree(A, numVertices,numVertices);

    return getCharOnly();
}

void TSP(int* C, int* A, int* path, int* fpath, int *sum, int *fsum, int flag, int b, int a, int *sc){
    int i,k;
    flag++;
    for(k=0;k<numVertices;k++)
        if(*(C+numVertices*flag+k)==0){  //Checking if any node of (flag+1)-th row is not already reached.
            *(C+numVertices*flag+k)=k;   //Placing the new node in that Vertex.
            *sum=*sum+*(A+numVertices*b+k);   //Updating total covered path distance.
            *(path+flag-1)=k;   //Adding the vertex to salesman's path.

            /*Updating the Board w.r.t. the newly covered vertex*/
            if(flag<numVertices){
                for(i=flag+1;i<numVertices;i++)
                    *(C+i*numVertices+k)=k;
            }

            /*Recursively call TSP function*/
            if(flag<numVertices-1)
                TSP(C,A,path,fpath,sum,fsum,flag,k,a,sc);

            /*Storing new solution to 'fpath'-array if found.*/
            if(flag==numVertices-1){
                *sum=*sum+*(A+numVertices*k+a);
                if(*sum==*fsum){
                    *sc=*sc+1;
                    for(i=0;i<numVertices-1;i++)
                        *(fpath+(*sc)*(numVertices-1)+i)=*(path+i);   //Updating final path direction.
                }
                else if(*sum<*fsum){
                    *fsum=*sum; //Updating covered path distance.
                    *sc=0;
                    for(i=0;i<numVertices-1;i++)
                        *(fpath+i)=*(path+i);   //Updating final path direction.
                }
                *sum=*sum-*(A+numVertices*k+a);
            }

            /*Removing the previous node and undoing all its effect*/
            for(i=flag;i<numVertices;i++)
                *(C+numVertices*i+k)=0;
            *sum=*sum-*(A+numVertices*b+k);   //Substructing last added path distance.
        }
}
