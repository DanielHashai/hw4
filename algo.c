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

//
//==============================================================================
//

char doTSP() {
    return '0';
}

void TSP(int* C, int* A, int* path, int* fpath, int *sum, int *fsum, int flag, int n, int b, int a, int *sc){
    int i,k;
    flag++;
    for(k=0;k<n;k++)
        if(*(C+n*flag+k)==0){  //Checking if any node of (flag+1)-th row is not already reached.
            *(C+n*flag+k)=k+1;   //Placing the new node in that Vertex.
            *sum=*sum+*(A+n*b+k);   //Updating total covered path distance.
            *(path+flag-1)=k;   //Adding the vertex to salesman's path.

            /*Updating the Board w.r.t. the newly covered vertex*/
            if(flag<n){
                for(i=flag+1;i<n;i++)
                    *(C+i*n+k)=k+1;
            }

            /*Recursively call TSP function*/
            if(flag<n-1)
                TSP(C,A,path,fpath,sum,fsum,flag,n,k,a,sc);

            /*Storing new solution to 'fpath'-array if found.*/
            if(flag==n-1){
                *sum=*sum+*(A+n*k+a);
                if(*sum==*fsum){
                    *sc=*sc+1;
                    for(i=0;i<n-1;i++)
                        *(fpath+(*sc)*(n-1)+i)=*(path+i);   //Updating final path direction.
                }
                else if(*sum<*fsum){
                    *fsum=*sum; //Updating covered path distance.
                    *sc=0;
                    for(i=0;i<n-1;i++)
                        *(fpath+i)=*(path+i);   //Updating final path direction.
                }
                *sum=*sum-*(A+n*k+a);
            }

            /*Removing the previous node and undoing all its effect*/
            for(i=flag;i<n;i++)
                *(C+n*i+k)=0;
            *sum=*sum-*(A+n*b+k);   //Substructing last added path distance.
        }
}
