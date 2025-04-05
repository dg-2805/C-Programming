/* Implement Dijkstra's Algorithm to find the shortest path
From \ To	s	 t	x	y	z
s       	∞	10	∞	5	∞
t	        ∞	 ∞	1	2	∞
x	        ∞	 ∞	∞	∞	4
y	        ∞	 3	9	∞	2
z	        7	 ∞	6	∞	∞

*/

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

// Function to create a Min Heap
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->pos = (int*)malloc(V * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

// Function to create a Min Heap Node
MinHeapNode* newMinHeapNode(int vertex, int dist) {
    MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    minHeapNode->vertex = vertex;
    minHeapNode->dist = dist;
    return minHeapNode;
}

// Function to swap two nodes in Min Heap
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

// Function to extract minimum node from Min Heap
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

// Function to decrease distance value of a vertex
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

void printMinHeap(MinHeap* minHeap) {
    printf("\n--- MIN HEAP (PRIORITY QUEUE) ---\n");
    printf("Size: %d, Capacity: %d\n", minHeap->size, minHeap->capacity);
    printf("Nodes (vertex, distance):\n");
    
    for (int i = 0; i < minHeap->size; i++) {
        printf("[%d] Vertex: %c, Distance: ", i, 'S' + minHeap->array[i]->vertex);
        if (minHeap->array[i]->dist == INF)
            printf("INF\n");
        else
            printf("%d\n", minHeap->array[i]->dist);
    }
    printf("\n");
}

void printPositions(MinHeap* minHeap) {
    printf("\n--- POSITION ARRAY ---\n");
    printf("Vertex -> Heap Index:\n");
    
    for (int i = 0; i < V; i++) {
        printf("Vertex %c -> Index %d\n", 'S' + i, minHeap->pos[i]);
    }
    printf("\n");
}

void printAdjList(Graph* graph) {
    printf("\n--- ADJACENCY LIST ---\n");
    
    for (int i = 0; i < V; i++) {
        printf("Vertex %c: ", 'S' + i);
        Node* temp = graph->array[i].head;
        
        while (temp) {
            printf("(%c, %d) -> ", 'S' + temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("NULL\n");
    }
    printf("\n");
}

void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%c", 'S' + j);
        return;
    }
    printPath(parent, parent[j]);
    printf(" -> %c", 'S' + j);
}

// Original Dijkstra Algorithm implementation
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
        printf("%c\t%d\t\t", 'S' + i, dist[i]);
        printPath(parent, i);
        printf("\n");
    }
}

void dijkstra_with_print(Graph* graph, int src) {
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

    
    printf("\n===== INITIAL STATE =====\n");
    printAdjList(graph);
    printMinHeap(minHeap);
    printPositions(minHeap);

    int step = 1;
    
    
    while (!isEmpty(minHeap)) {
        printf("\n===== STEP %d =====\n", step++);
        
       
        MinHeapNode* minNode = extractMin(minHeap);
        int u = minNode->vertex;
        
        printf("Extracted vertex %c with distance ", 'S' + u);
        if (dist[u] == INF)
            printf("INF\n");
        else
            printf("%d\n", dist[u]);

        
        Node* temp = graph->array[u].head;
        while (temp != NULL) {
            int v = temp->vertex;

            if (minHeap->pos[v] < minHeap->size && 
                dist[u] != INF && 
                temp->weight + dist[u] < dist[v]) {
                
                printf("Updating distance of vertex %c: %d -> %d\n", 
                       'S' + v, 
                       (dist[v] == INF) ? INF : dist[v], 
                       dist[u] + temp->weight);
                
                dist[v] = dist[u] + temp->weight;
                parent[v] = u;
                decreaseKey(minHeap, v, dist[v]);
            }
            temp = temp->next;
        }
        
       
        printMinHeap(minHeap);
        printPositions(minHeap);
    }

  
    printf("\n===== FINAL RESULTS =====\n");
    printf("Vertex\tDistance\tPath\n");
    for (int i = 0; i < V; i++) {
        printf("%c\t", 'S' + i);
        
        if (dist[i] == INF)
            printf("INF\t\t");
        else
            printf("%d\t\t", dist[i]);
            
        if (dist[i] != INF) {
            printPath(parent, i);
        } else {
            printf("No path");
        }
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
    
    printf("Graph Representation Before Dijkstra's Algorithm:\n");
    printAdjList(graph);
    
    dijkstra_with_print(graph, 0);

    return 0;
}


/*OUTPUT

Graph Representation Before Dijkstra's Algorithm:

--- ADJACENCY LIST ---
Vertex S: (V, 5) -> (T, 10) -> NULL
Vertex T: (W, 2) -> (U, 1) -> NULL
Vertex U: (W, 4) -> NULL
Vertex V: (W, 2) -> (U, 9) -> (T, 3) -> NULL
Vertex W: (U, 6) -> (S, 7) -> NULL


===== INITIAL STATE =====

--- ADJACENCY LIST ---
Vertex S: (V, 5) -> (T, 10) -> NULL
Vertex T: (W, 2) -> (U, 1) -> NULL
Vertex U: (W, 4) -> NULL
Vertex V: (W, 2) -> (U, 9) -> (T, 3) -> NULL
Vertex W: (U, 6) -> (S, 7) -> NULL


--- MIN HEAP (PRIORITY QUEUE) ---
Size: 5, Capacity: 5
Nodes (vertex, distance):
[0] Vertex: S, Distance: 0
[1] Vertex: T, Distance: INF
[2] Vertex: U, Distance: INF
[3] Vertex: V, Distance: INF
[4] Vertex: W, Distance: INF


--- POSITION ARRAY ---
Vertex -> Heap Index:
Vertex S -> Index 0
Vertex T -> Index 1
Vertex U -> Index 2
Vertex V -> Index 3
Vertex W -> Index 4


===== STEP 1 =====
Extracted vertex S with distance 0
Updating distance of vertex V: 2147483647 -> 5
Updating distance of vertex T: 2147483647 -> 10

--- MIN HEAP (PRIORITY QUEUE) ---
Size: 4, Capacity: 5
Nodes (vertex, distance):
[0] Vertex: V, Distance: 5
[1] Vertex: T, Distance: 10
[2] Vertex: U, Distance: INF
[3] Vertex: W, Distance: INF


--- POSITION ARRAY ---
Vertex -> Heap Index:
Vertex S -> Index 4
Vertex T -> Index 1
Vertex U -> Index 2
Vertex V -> Index 0
Vertex W -> Index 3


===== STEP 2 =====
Extracted vertex V with distance 5
Updating distance of vertex W: 2147483647 -> 7
Updating distance of vertex U: 2147483647 -> 14
Updating distance of vertex T: 10 -> 8

--- MIN HEAP (PRIORITY QUEUE) ---
Size: 3, Capacity: 5
Nodes (vertex, distance):
[0] Vertex: W, Distance: 7
[1] Vertex: T, Distance: 8
[2] Vertex: U, Distance: 14


--- POSITION ARRAY ---
Vertex -> Heap Index:
Vertex S -> Index 4
Vertex T -> Index 1
Vertex U -> Index 2
Vertex V -> Index 3
Vertex W -> Index 0


===== STEP 3 =====
Extracted vertex W with distance 7
Updating distance of vertex U: 14 -> 13

--- MIN HEAP (PRIORITY QUEUE) ---
Size: 2, Capacity: 5
Nodes (vertex, distance):
[0] Vertex: T, Distance: 8
[1] Vertex: U, Distance: 13


--- POSITION ARRAY ---
Vertex -> Heap Index:
Vertex S -> Index 4
Vertex T -> Index 0
Vertex U -> Index 1
Vertex V -> Index 3
Vertex W -> Index 2


===== STEP 4 =====
Extracted vertex T with distance 8
Updating distance of vertex U: 13 -> 9

--- MIN HEAP (PRIORITY QUEUE) ---
Size: 1, Capacity: 5
Nodes (vertex, distance):
[0] Vertex: U, Distance: 9


--- POSITION ARRAY ---
Vertex -> Heap Index:
Vertex S -> Index 4
Vertex T -> Index 1
Vertex U -> Index 0
Vertex V -> Index 3
Vertex W -> Index 2


===== STEP 5 =====
Extracted vertex U with distance 9

--- MIN HEAP (PRIORITY QUEUE) ---
Size: 0, Capacity: 5
Nodes (vertex, distance):


--- POSITION ARRAY ---
Vertex -> Heap Index:
Vertex S -> Index 4
Vertex T -> Index 1
Vertex U -> Index 0
Vertex V -> Index 3
Vertex W -> Index 2


===== FINAL RESULTS =====
Vertex  Distance        Path
S       0               S
T       8               S -> V -> T
U       9               S -> V -> T -> U
V       5               S -> V
W       7               S -> V -> W

daria@DG MINGW64 ~/Documents/Temp
$


===== FINAL RESULTS =====
Vertex  Distance        Path
S       0               S
T       8               S -> V -> T
U       9               S -> V -> T -> U
V       5               S -> V
W       7               S -> V -> W

===== FINAL RESULTS =====
Vertex  Distance        Path
S       0               S
T       8               S -> V -> T
U       9               S -> V -> T -> U

===== FINAL RESULTS =====
Vertex  Distance        Path
S       0               S
T       8               S -> V -> T

===== FINAL RESULTS =====
Vertex  Distance        Path
S       0               S


===== FINAL RESULTS =====
Vertex  Distance        Path
S       0               S
T       8               S -> V -> T
U       9               S -> V -> T -> U
V       5               S -> V
W       7               S -> V -> W
*/
