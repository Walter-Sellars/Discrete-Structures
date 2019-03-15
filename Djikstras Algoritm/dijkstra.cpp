// CSCI 2530
// Assignment: 7
// Author:     Walter Sellars
// File:       dijkstra.cpp
// Tab stops:  4

/*

 Dijkstra.cpp is a module designed to find the shortest path between
 two given vertices based on the weight of the edges between the vertices. 
 Dijkstra shows which vertices it went through and the time taken for the
 pathing to finish. 
 In addition, Dijkstra implements tracing
 to see what the program is doing in real-time.

 The first number is the number
 of vertices the graph will have.

 Then the next three values are:
 two integer values (separated by a space) for the vertices the edge connects
 and a double value separated by a space from the previous integer that
 represents the weight.

 To end input of the graph, enter '0'.

 Then input the path from vertex 'a' to vertex 'b' seperated by a space.

 Example input:

 5
 1 2  9.0
 1 3 12.0
 2 4 18.0
 2 3  6.0
 2 5 20.0
 3 5 15.0
 0

 1 5

 Example output:

 There are 5 vertices and 6 edges.
 The edges are as follows.

 (1, 3) weight 12.000000
 (1, 2) weight 9.000000
 (2, 5) weight 20.000000
 (2, 3) weight 6.000000
 (2, 4) weight 18.000000
 (3, 5) weight 15.000000

The shortest path from 1 to 5 has length 27.000000 and is 1 -> 3 -> 5
 */

#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include "pqueue.h"
#include "event.h"

using namespace std;

typedef int vertexNumber;

typedef PriorityQueue EventQueue;

// Trace variable used for tracing throughout module.

int trace = 0;
/*
 structure "Edge" is used as a cell in an adjacency list. 
 The "Edge" structure containst:
 - Two vertex numbers 'u' and 'v'.
 - A weight "weight".
 - A pointer "next" to the next Edge in the linked list.

 Type Edge has a constructor 'Edge(one, two, w, nxt) which initializes
 each of the aforementioned fields.
 */

struct Edge
{
    int u; //start
    int v; //end
    double weight;
    Edge* next;

    Edge(int one, int two, double w, Edge* nxt)
    {
        u = one;
        v = two;
        weight = w;
        next = nxt;
    }
};
/*
 The strucure "vertex" contains:
 - A pointer to the adjacency list of edges
 - A real number indicating v's shortest distance from the start vertex.
 - An int 'from' that holds the previous number

"Vertex" has a constructor that takes no parameters and sets distance 
 and from to -1, and the next edge to NULL
 */

struct Vertex
{
    Edge* adjList;
    double distance;
    vertexNumber from;

    Vertex()
    {
        from = -1;
        adjList = NULL;
        distance = -1.0;
    }
};
/*

 The "Graph" structure contains:
 - Number of vertices
 - Number of edges
 - An array of vertices

 "Graph" has a constructor 'Graph(numV)' which initializes
 the variable for the number of vertices, sets the number of edges to '0'
 and declares the size of the array to be the number of vertices.

 */

struct Graph
{
    int numVerts;
    int numOfEdges;
    Vertex* vertices;

    Graph(int numV)
    {
        numVerts = numV;
        numOfEdges = 0;
        vertices = new Vertex[numVerts+1];
    }
};

// Prototype Functions

Graph readGraph();
void printGraph(const Graph g);
void printList(Edge* t);
void insertEdge(int first, int second, double weight, Graph& g);
void singleSignal(int u, int v, double time, EventQueue& q);
void propagateSignals(Graph& g, Vertex& v, EventQueue& q);
void processEvent(Graph& g, EventQueue& q, Event* e);
void dijkstraAlgorithm(EventQueue& q, Graph& g, int start, int end);
double shortestDistance(Graph& g, int finish);
void showPath(Graph&g, int strt, int end);
Event* getEvent(EventQueue& q);
void traceOn(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    traceOn(argc, argv);
    printf("\n Input graph:\n");
    Graph g = readGraph();
   
    EventQueue q;
    int start, finish;
    printf("\nInput starting vertex and "
        "finishing vertex seperated by a space:\n");
    scanf("%d %d", &start, &finish);
    dijkstraAlgorithm(q, g, start, finish);

    printGraph(g);
    printf("\nThe shortest path from %d to %d "
           "has length %lf and is ", start, finish,
           shortestDistance(g, finish));
    showPath(g, finish, start);
    putchar('\n');

    return 0;
}

// traceOn turns on tracing for the dijkstra module if "-t" is present in args.
// If there is a bad argument, traceOn writes a warning to the output and exits.

void traceOn(int argc, char* argv[])
{
    if (argc >= 2)
    {
        for (int i = 1; i < argc; ++i) 
        {
            if (strcmp(argv[i], "-t") == 0) 
            {
                trace = 1;
            }
            if (!strcmp(argv[i], "-t") == 0)
            {
                printf("usage: dijkstra [-t]\n");
                exit(1);
            }
        }
    }
}


//ReadGraph reads the standard input and returns a graph  of the edges and their weights.


Graph readGraph()
{
    int verts;
    scanf("%d", &verts);
    Graph g = Graph(verts);
    int startVert, endVert;
    double weight;
    scanf("%d", &startVert);
    while (startVert != 0)
    {
        scanf("%d %lf", &endVert, &weight);
        insertEdge(startVert, endVert, weight, g);
        scanf("%d", &startVert);
    }
    return g;
}

// insertEdge inserts an edge cell into the adjacency list of graph 'g'.

void insertEdge(int first, int second, double weight, Graph& g)
{
    g.vertices[first].adjList =
    new Edge(first, second, weight, g.vertices[first].adjList);

    g.vertices[second].adjList =
    new Edge(second, first, weight, g.vertices[second].adjList);

    g.numOfEdges += 1;
}

// printGraph prints description the graph of 'g' to the standard output.

void printGraph(const Graph g)
{
    printf("\n\n");
    printf("There are %d vertices and %d edges.\n",g.numVerts,g.numOfEdges);
    printf("The edges are:\n");
    for (int i = 1; i < g.numVerts+1; ++i) 
    {
        Edge* temp = g.vertices[i].adjList;
        printList(temp);
    }
}

// printList is a helper function that writes the adjacency list 'temp'
// to the standard output

void printList(Edge* temp)
{
    while (temp) 
        {
            if(temp -> u < temp -> v)
            { 
                printf("%i %4i   weight %10.3lf\n", temp -> u, temp -> v, temp -> weight);
                if(trace == 1)
                {
                    printf("%i %4i   weight %10.3lf\n", temp -> v, temp -> u, temp -> weight);
                }
            }
            temp = temp->next;
        }
}


/*
 singleSignal sends a signal from 'u' to 'v', arriving at time 'time', 
 by inserting an event into 'q'.
 */

void singleSignal(int u, int v, double time, EventQueue& q)
{
    Event* e = new Event(u, v, time);

    if (trace == 1) {
        printf("\nSending signal from %d to %d time %lf", u , v, time);
    }

    insert(q, e, time);
}

/*
 propagateSignals sends a signal from 'v' to every vertex that is
 adjacent to 'v' in 'g', excluding those that have already received
 a signal.
 */

void propagateSignals(Graph& g, Vertex& v, EventQueue& q)
{
    Edge* adjcts = v.adjList;
    while (adjcts != NULL)
    {
        if (g.vertices[adjcts->v].from == -1)
        {
            double time = g.vertices[adjcts->u].distance;
            singleSignal(adjcts->u, adjcts->v,
                         adjcts->weight + time, q);
        }
        adjcts = adjcts->next;
    }
}

// processEvent process a single event from
// event queue 'q'.

void processEvent(Graph& g, EventQueue& q, Event* e)
{
        Vertex* recip = &(g.vertices[e->receiver]);
        if (trace == 1)
        {
            printf("\nVertex (%i) received a signal. "
                   "Sent by: %i, time: %lf\n",
                   e->receiver, e->sender, e->time);
        }
        if (recip->from == -1)
        {
            recip->from = e->sender;
            recip->distance = e->time;

            if (trace == 1)
            {
                printf("\nVertex (%i) updated. "
                       "Previous: %i. Time from start: %lf",
                       e->receiver, e->sender, e->time);
            }
            propagateSignals(g, *recip, q);
        }
    delete e;
}

// getEvent(q) gets an event from priority queue 'q' with the
// least priority and returns the event.

Event* getEvent(EventQueue& q)
{
    Event* event;
    double val;
    remove(q, event, val);

    return event;
}

// dijkstarAlgorithm(q, g, start, end) searches for the shortest path
// from vertices 'start' to 'end'.

void dijkstraAlgorithm(EventQueue& q, Graph& g, int start, int end)
{
    singleSignal(0, start, 0.0, q);

    while (g.vertices[end].from == -1)
    {
        Event* evnt = getEvent(q);
        double val;
        remove(q, evnt, val);
        processEvent(g, q, evnt);
    }
}

// shortestDistance returns the shortest distance
// from the starting vertex to arg.

double shortestDistance(Graph& g, int finish)
{
    return g.vertices[finish].distance;
}

// showPath displays the shortest path in graph 'g'
// from 'strt' to 'end' to the standard output.

void showPath(Graph&g, int strt, int end)
{
    if (strt == end)
    {
        printf("%d", strt);
    }
    else
    {
        showPath(g, g.vertices[strt].from, end);
        printf(" -> ");
        printf("%d", strt);
    }
}
