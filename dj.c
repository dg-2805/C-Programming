/* Implement Dijkstra's Algorithm to find the shortest path
From \ To	s	 t	x	y	z
s       	∞	10	∞	5	∞
t	        ∞	 ∞	1	2	∞
x	        ∞	 ∞	∞	∞	4
y	        ∞	 3	9	∞	2
z	        7	 ∞	6	∞	∞

*/
#CODE
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX
#define V 5  // Number of vertices in the graph

// Structure for adjacency list node
typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

// Structure for adjacency list
typedef struct {
    Node* head;
} AdjList;

// Structure for the graph
typedef struct {
    AdjList* array;
} Graph;

// Structure for Min Heap Node
typedef struct {
    int vertex;
    int dist;
} MinHeapNode;

// Structure for Min Heap
typedef struct {
    int size;
    int capacity;
    int *pos;
    MinHeapNode **array;
} MinHeap;

// Function to create a new node
Node* newNode(int vertex, int weight) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->vertex = vertex;
    temp->weight = weight;
    temp->next = NULL;
    return temp;
}

// Function to create a graph
Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; i++)
        graph->array[i].head = NULL;
    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* temp = newNode(dest, weight);
    temp->next = graph->array[src].head;
    graph->array[src].head = temp;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int*)malloc(V * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

MinHeapNode* newMinHeapNode(int vertex, int dist) {
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    minHeapNode->vertex = vertex;
    minHeapNode->dist = dist;
    return minHeapNode;
}

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

// Min Heapify function
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->vertex] = idx;
        minHeap->pos[idxNode->vertex] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

//Extract-Min(V times)
MinHeapNode* extractMin(MinHeap* minHeap) {
    if (minHeap->size == 0)
        return NULL;

    MinHeapNode* root = minHeap->array[0];

    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->vertex] = minHeap->size - 1;
    minHeap->pos[lastNode->vertex] = 0;

    minHeap->size--;
    minHeapify(minHeap, 0);

    return root;
}
//Decrease Key (E times)
void decreaseKey(MinHeap* minHeap, int vertex, int dist) {
    int i = minHeap->pos[vertex];
    minHeap->array[i]->dist = dist;

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        minHeap->pos[minHeap->array[i]->vertex] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->vertex] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}
int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}
// Printing the Path
void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%c", 's' + j);
        return;
    }
    printPath(parent, parent[j]);
    printf(" -> %c", 's' + j);
}
void printAdjList(Graph* graph) {
    printf("Adjacency List:\n");
    for (int i = 0; i < V; i++) {
        Node* temp = graph->array[i].head;
        printf("%c -> ", 's' + i);
        while (temp != NULL) {
            printf("%c(%d) -> ", 's' + temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}
void dijkstra(Graph* graph, int src) {
    int dist[V];
    int parent[V];
    MinHeap* minHeap = createMinHeap(V);

    for (int v = 0; v < V; v++) {
        parent[v] = -1;
        dist[v] = INF;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
    minHeap->array[src] = newMinHeapNode(src, 0);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
    minHeap->size = V;
    while (!isEmpty(minHeap)) {
        MinHeapNode* minNode = extractMin(minHeap);
        int u = minNode->vertex;

        Node* temp = graph->array[u].head;
        while (temp != NULL) {
            int v = temp->vertex;
            if (minHeap->pos[v] < minHeap->size && dist[u] != INF && temp->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + temp->weight;
                parent[v] = u;
                decreaseKey(minHeap, v, dist[v]);
            }
            temp = temp->next;
        }
    }
    printf("Vertex\tDistance\tPath\n");
    for (int i = 0; i < V; i++) {
        printf("%c\t%d\t\t", 's' + i, dist[i]);
        printPath(parent, i);
        printf("\n");
    }
}

int main() {
    Graph* graph = createGraph();
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 3, 5);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 4, 2);
    addEdge(graph, 2, 4, 4);
    addEdge(graph, 3, 1, 3);
    addEdge(graph, 3, 2, 9);
    addEdge(graph, 3, 4, 2);
    addEdge(graph, 4, 0, 7);
    addEdge(graph, 4, 2, 6);

    printAdjList(graph);
    printf("\n");
    printf("Dijkstra's Algorithm:\n");
    printf("\n");
    dijkstra(graph, 0);
    return 0;
}

/*OUTPUT
Adjacency List:
s -> v(5) -> t(10) -> NULL
t -> w(2) -> u(1) -> NULL
u -> w(4) -> NULL
v -> w(2) -> u(9) -> t(3) -> NULL
w -> u(6) -> s(7) -> NULL

Dijkstra's Algorithm:

Vertex  Distance        Path
s       0               s
t       8               s -> v -> t
u       9               s -> v -> t -> u
v       5               s -> v
w       7               s -> v -> w

*/
