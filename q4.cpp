#define SIZE 2048
#define INFINITY SIZE*SIZE
#define MAX(a, b) ((a > b) ? (a) : (b))

1. SIZE: Defines the maximum size for the graph. In this case, 2048 is used as an arbitrary large number.
2. INFINITY: Represents a large value to signify that initially, the distance to all vertices is considered infinite. It is set to SIZE * SIZE, which is a large number assuming SIZE is reasonably large.
3. MAX(a, b): A macro to compute the maximum of two values, used to update the number of vertices.


int numOfEdges = 0;
int numOfVertices = 0;
long distance[SIZE][SIZE];
long shortestPath[SIZE];

1. numOfEdges: Number of edges in the graph.
2. numOfVertices: Number of vertices in the graph.
3. distance[SIZE][SIZE]: Adjacency matrix to store distances between vertices.
4. shortestPath[SIZE]: Array to store the shortest path from the source vertex to each vertex.


void print(void)
{
    int i = 0;

    printf("DJIKSTRA'S ALGORITHM\n\n");
    printf("Vertex Number:");

    for (i = 1; i <= numOfVertices; ++i)
    {
        printf("%10d", i);
    }

    printf("\n\nShortest Path:");

    for (i = 1; i <= numOfVertices; ++i)
    {
        printf("%10ld", shortestPath[i]);
    }

    printf("\n\n");
}

1. Purpose: Prints the results of the Dijkstra algorithm.
2. Details:
	a. it prints the header and the vertex numbers.
	b. it prints the shortest path from the source vertex to each vertex in the graph.


void dijkstra(int s) 
{
    int i = 0;
    int j = 0;
    int small = 0;
    int visited[SIZE];

    for (i = 1; i <= numOfVertices; ++i) 
    {
        shortestPath[i] = INFINITY;
        visited[i] = 0;
    }

    shortestPath[s] = 0;

    for (j = 1; j <= numOfVertices; ++j)
    {
        small = -1;

        for (i = 1; i <= numOfVertices; ++i)
        {
            if (!visited[i] && ((small == -1) || (shortestPath[i] < shortestPath[small])))
            {
                small = i;
            }
        }

        visited[small] = 1;

        for (i = 1; i <= numOfVertices; ++i)
        {
            if (distance[small][i])
            {
                if (shortestPath[small] + distance[small][i] < shortestPath[i])
                {
                    shortestPath[i] = shortestPath[small] + distance[small][i];
                }
            }
        }
    }
}

/*
1. Purpose: Implements Dijkstra's algorithm to find the shortest path from the source vertex s to all other vertices.
2. Details:
	a. Initializes the shortestPath array with INFINITY and visited array with 0 (not visited).
	b. Sets the distance to the source vertex s to 0.
	c. Iterates to find the vertex with the minimum distance (small) that hasn't been visited yet.
	d. Updates the shortest path estimates for all adjacent vertices of small.
	e. Marks the vertex small as visited and continues until all vertices are processed.
*/

int main(int argc, char *argv[]) 
{
    int i = 0;
    int j = 0;
    int vertexU = 0;
    int vertexV = 0;
    int vertexW = 0;

    FILE *theFile = fopen("djikstra.txt", "r");

    fscanf(theFile, "%d", &numOfEdges);

    for (i = 0; i < numOfEdges; ++i)
    {
        for (j = 0; j < numOfEdges; ++j)
        {
            distance[i][j] = 0;
        }
    }

    numOfVertices = -1;

    for (i = 0; i < numOfEdges; ++i) 
    {
        fscanf(theFile, "%d%d%d", &vertexU, &vertexV, &vertexW);
        distance[vertexU][vertexV] = vertexW;
        numOfVertices = MAX(vertexU, MAX(vertexV, numOfVertices));
    }

    fclose(theFile);

    dijkstra(1);

    print();

    return 0;
}

/*1. Purpose: Main function to drive the program.
2. Details:
	a. Opens and reads the graph data from djikstra.txt.
	b. Initializes the distance matrix with 0s.
	c. Reads edges and their weights from the file, updating the distance matrix and determining the number of vertices.
	d. Calls the dijkstra function with 1 as the source vertex.
	e. Prints the results using the print function.
    */