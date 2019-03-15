/** CSCI 2530
 File:       mst.cpp
 Tab stops:  4

 mst.cpp reads a description of a weighted graph with integer weights, and
 then writes the graph G, The edges that are part of the minimal spanning
 tree K of G, and the total weight of K to the standard output.

Example
Input::
  5
  1 2 9
  1 3 12
  2 4 18
  2 3 8
  2 5 20
  3 5 15
  0


Output::
 Input graph:

   There are 5 vertices and 6 edges

   vertices   weight
      1 2     9
      1 3     12
      2 4     18
      2 3     6
      2 5     20
      3 5     15

 Minimal spanning tree:

 There are 5 vertices and 4 edges
   vertices   weight
      2 3     6
      1 2     9
      3 5     15
      2 4     18
      
 The total weight of the spanning tree is 48.*/

#include <cstdio>
#include <cstdlib>
#include "equiv.h"
using namespace std;

/**An object of type Edge represents an edge between two vertices
 in a weight graph.
The fields are:
  vert1   the first vertex
  vert2   the second vertex
  wght    the weight of the edge*/

const int MAX_EDGES = 100;
using vertexNum = int;
using edgeNum = int;
typedef int (*QSORT_COMPARE_TYPE)(const void *, const void *);

struct Edge
{
    int vert1;
    int vert2;
    int wght;

    Edge()
    {
        vert1 = 0;
        vert2 = 0;
        wght = 0;
    }
};

/**An object of type Graph represents a weighted graph
The fields are:
  totalVertices   the total number of verticies in the graph
  totalEdges   the total number of edges in the graph
  edgeArray    an array that holds the edges
  arrSize    the physical size of edgeArray*/
struct Graph
{
    int totalVertices;
    int totalEdges;
    Edge* edgeArray;
    int arrSize;

    Graph(int nv)
    {
        totalVertices = nv;
        totalEdges = 0;
        arrSize = MAX_EDGES
    ;
        edgeArray = new Edge[arrSize];
    }
};

/** Function insertEdge inserts an edge of weight 'w' between vertices
 'u' and 'v' into graph 'g'.

 If there is not enough room in graph 'g' to add the edge, then
 insertEdge does nothing.*/
void insertEdge(int u, int v, int w, Graph& g)
{
    Edge newEdge;
    newEdge.vert1 = u;
    newEdge.vert2 = v;
    newEdge.wght = w;
    if(g.totalEdges < MAX_EDGES
)
    {
        g.edgeArray[g.totalEdges] = newEdge;
        g.totalEdges ++;
    }
}

// Function readGraph reads a description of a graph from standard input and 
// stores it in Graph 'g'. Function readGraph will terminate if the first number on an
// input line is 0.
void readGraph(Graph& g)
{
    int nv;
    scanf("%i", &nv);
    Graph *g = new Graph(nv);
    int u,v,w;
    while(true)
    {
        scanf("%i", &u);
        if(u == 0)
        {
            break;
        }
        scanf("%i", &v);
        scanf("%i", &w);
        insertEdge(u, v, w, g);
    }
}

// Function writeGraph prints a formatted version of Graph 'g' to the standard 
// output.
void writeGraph(const Graph& g)
{
    printf("\nThere are %i vertices and %i edges\n", g.totalVertices, 
    g.totalEdges);
    printf(" Vertices    Weight\n");
    for(int n = 0; n< g.totalEdges; n++)
    {
        printf("  %i  %i         %i\n", g.edgeArray[n].vert1, g.edgeArray[n].vert2, 
        g.edgeArray[n].wght);
    }

}
// Function compareEdges returns a negative or positive number
// if 'A' is smaller or larger than 'B' respectively.
int compareEdges(const Edge *A, const Edge *B)
{
    return A->wght - B->wght;
}

// Function sortEdges sorts the array of edges in graph G by weight
// in ascending order.

void sortEdges(Graph& g)
{
    qsort((void *)g.edgeArray, g.totalEdges, sizeof(Edge), 
    (QSORT_COMPARE_TYPE)compareEdges);
}

//Function minimalSpanningTree returns the minimal spanning tree graph of 'g'.
Graph minimalSpanningTree(Graph& g)
{
    sortEdges(g);
    Graph k = Graph(g.totalVertices);
    ER kTracker = newER(g.totalVertices);
    for(int n = 0; n < g.totalEdges; n++)
    {
        if (!equivalent(kTracker, g.edgeArray[n].vert1, g.edgeArray[n].vert2))
        {
            insertEdge(g.edgeArray[n].vert1, g.edgeArray[n].vert2, 
            g.edgeArray[n].wght, k);
            merge(kTracker, g.edgeArray[n].vert1, g.edgeArray[n].vert2);
        }
    }
    delete [] kTracker;
    return k;
}

// Function totalWeight returns the combined weight of each edge 
// in the graph 'g'.

int totalWeight(const Graph& g)
{
    int totalWeight =0;
    for(int n = 0; n<= g.totalEdges; n++)
    {
        totalWeight = totalWeight + g.edgeArray[n].wght;
    }
    return totalWeight;
}

int main()
{
    int nv;
    struct Graph g(nv);
    readGraph(g);
    printf("Input Graph:\n");
    writeGraph(g);
    Graph k = minimalSpanningTree(g);
    printf("Minimal spanning tree:\n");
    writeGraph(k);
    printf("\nThe total weight of the spanning tree is %i\n ", totalWeight(k));
    return 0;
}