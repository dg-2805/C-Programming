/* Write a Program to find the MST of a given graph using Prim’s algorithm. Check your program on a graph whose length matrix is given as follows. Your program should use priority queue implementation.
   a b c d e f g h i
a  0 4 ∞ ∞ ∞ ∞ ∞ 8 ∞
b  4 0 8 ∞ ∞ ∞ ∞ 11 ∞
c  ∞ 8 0 7 ∞ 4 ∞ ∞ 2
d  ∞ ∞ 7 0 9 14 ∞ ∞ ∞
e  ∞ ∞ ∞ 9 0 10 ∞ ∞ ∞
f  ∞ ∞ 4 14 10 0 2 ∞ ∞
g  ∞ ∞ ∞ ∞ ∞ 2 0 1 6
h  8 11 ∞ ∞ ∞ ∞ 1 0 7
i  ∞ ∞ 2 ∞ ∞ ∞ 6 7 0 
*/

//graph.txt
9
0 1 4
0 7 8
1 2 8
1 7 11
2 3 7
2 5 4
2 8 2
3 4 9
3 5 14
4 5 10
5 6 2
6 7 1
6 8 6
7 8 7

#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include <time.h> 
 
#define MAX_VERTICES 1000 
 
typedef struct AdjListNode { 
    int dest; 
    int weight; 
    struct AdjListNode* next; 
} AdjListNode; 
 
typedef struct AdjList { 
    AdjListNode* head; 
} AdjList; 
 
typedef struct Graph { 
    int V; 
    AdjList* array; 
} Graph; 
 
typedef struct MinHeapNode { 
    int v; 
    int key; 
} MinHeapNode; 
 
typedef struct MinHeap { 
    int size; 
    int capacity; 
    int* pos; 
    MinHeapNode** array; 
} MinHeap; 
 
AdjListNode* newAdjListNode(int dest, int weight) { 
    AdjListNode* newNode = (AdjListNode*) malloc(sizeof(AdjListNode)); 
    newNode->dest = dest; 
    newNode->weight = weight; 
    newNode->next = NULL; 
    return newNode; 
} 
 
Graph* createGraph(int V) { 
    Graph* graph = (Graph*) malloc(sizeof(Graph)); 
    graph->V = V; 
    graph->array = (AdjList*) malloc(V * sizeof(AdjList)); 
    for (int i = 0; i < V; ++i) 
        graph->array[i].head = NULL; 
    return graph; 
} 
void addEdge(Graph* graph, int src, int dest, int weight) { 
    AdjListNode* newNode = newAdjListNode(dest, weight); 
    newNode->next = graph->array[src].head; 
    graph->array[src].head = newNode; 
    newNode = newAdjListNode(src, weight); 
    newNode->next = graph->array[dest].head; 
    graph->array[dest].head = newNode; 
} 
 
MinHeapNode* newMinHeapNode(int v, int key) { 
    MinHeapNode* minHeapNode = (MinHeapNode*) malloc(sizeof(MinHeapNode)); 
    minHeapNode->v = v; 
    minHeapNode->key = key; 
    return minHeapNode; 
} 
 
MinHeap* createMinHeap(int capacity) { 
    MinHeap* minHeap = (MinHeap*) malloc(sizeof(MinHeap)); 
    minHeap->pos = (int*) malloc(capacity * sizeof(int)); 
    minHeap->size = 0; 
    minHeap->capacity = capacity; 
    minHeap->array = (MinHeapNode**) malloc(capacity * sizeof(MinHeapNode*)); 
    return minHeap; 
} 
 
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) { 
    MinHeapNode* t = *a; 
    *a = *b; 
    *b = t; 
} 
void minHeapify(MinHeap* minHeap, int idx) { 
    int smallest = idx; 
    int left = 2 * idx + 1; 
    int right = 2 * idx + 2; 
    if (left < minHeap->size && 
        minHeap->array[left]->key < minHeap->array[smallest]->key) 
        smallest = left; 
    if (right < minHeap->size && 
        minHeap->array[right]->key < minHeap->array[smallest]->key) 
        smallest = right; 
    if (smallest != idx) { 
        MinHeapNode* smallestNode = minHeap->array[smallest]; 
        MinHeapNode* idxNode = minHeap->array[idx]; 
        minHeap->pos[smallestNode->v] = idx; 
        minHeap->pos[idxNode->v] = smallest; 
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]); 
        minHeapify(minHeap, smallest); 
    } 
} 
int isEmpty(MinHeap* minHeap) { 
    return minHeap->size == 0; 
} 
MinHeapNode* extractMin(MinHeap* minHeap) { 
    if (isEmpty(minHeap)) 
        return NULL; 
    MinHeapNode* root = minHeap->array[0]; 
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; 
    minHeap->array[0] = lastNode; 
    minHeap->pos[root->v] = minHeap->size-1; 
    minHeap->pos[lastNode->v] = 0; 
    --minHeap->size; 
    minHeapify(minHeap, 0); 
    return root; 
} 
 
void decreaseKey(MinHeap* minHeap, int v, int key) { 
    int i = minHeap->pos[v]; 
    minHeap->array[i]->key = key; 
    while (i && minHeap->array[i]->key < minHeap->array[(i-1)/2]->key) { 
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2; 
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i; 
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i-1)/2]); 
        i = (i-1)/2; 
    } 
} 
int isInMinHeap(MinHeap *minHeap, int v) { 
    if (minHeap->pos[v] < minHeap->size) 
        return 1; 
    return 0; 
} 
void PrimMST(Graph* graph) { 
    int V = graph->V; 
    int parent[V]; 
    int key[V]; 
    MinHeap* minHeap = createMinHeap(V); 
    for (int v = 0; v < V; ++v) { 
        parent[v] = -1; 
        key[v] = INT_MAX; 
        minHeap->array[v] = newMinHeapNode(v, key[v]); 
        minHeap->pos[v] = v; 
    } 
    srand(time(NULL)); 
    int src = rand() % V; 
    printf("Random starting vertex: %d\n", src); 
    minHeap->array[src] = newMinHeapNode(src, key[src]); 
    minHeap->pos[src] = src; 
    key[src] = 0; 
    decreaseKey(minHeap, src, key[src]); 
    minHeap->size = V; 
    while (!isEmpty(minHeap)) { 
        MinHeapNode* minHeapNode = extractMin(minHeap); 
        int u = minHeapNode->v; 
        AdjListNode* pCrawl = graph->array[u].head; 
        while (pCrawl != NULL) { 
            int v = pCrawl->dest; 
            if (isInMinHeap(minHeap, v) && pCrawl->weight < key[v]) { 
                key[v] = pCrawl->weight; 
                parent[v] = u; 
                decreaseKey(minHeap, v, key[v]); 
            } 
            pCrawl = pCrawl->next; 
        } 
    } 
    printf("Edge \tWeight\n"); 
    int totalWeight = 0; 
    for (int i = 0; i < V; ++i) { 
        if (parent[i] != -1) { 
            printf("%d - %d\t%d\n", parent[i], i, key[i]); 
            totalWeight += key[i]; 
        } 
    } 
    printf("Total MST Weight: %d\n", totalWeight); 
} 
Graph* readGraphFromFile(const char* filename) { 
    FILE* file = fopen(filename, "r"); 
    if (!file) { 
        printf("Error opening file.\n"); 
        exit(1); 
    } 
    int V; 
    fscanf(file, "%d", &V); 
    Graph* graph = createGraph(V); 
    int src, dest, weight; 
    while (fscanf(file, "%d %d %d", &src, &dest, &weight) == 3) { 
        addEdge(graph, src, dest, weight); 
} 
} 
fclose(file); 
return graph; 
int main() { 
Graph* graph = readGraphFromFile("graph.txt"); 
PrimMST(graph); 
return 0; 
} 

/*
#OUTPUT 
Random starting vertex: 4 
Edge    Weight 
1 - 0   4 
2 - 1   8 
3 - 2   7 
4 - 3   9 
2 - 5   4 
5 - 6   2 
6 - 7   1 
2 - 8   2 
Total MST Weight: 37 
Random starting vertex: 2 
Edge    Weight 
7 - 0   8 
0 - 1   4 
2 - 3   7 
3 - 4   9 
2 - 5   4 
5 - 6   2 
6 - 7   1 
2 - 8   2 
Total MST Weight: 37 
Random starting vertex: 8 
Edge    Weight 
7 - 0   8 
0 - 1   4 
8 - 2   2 
2 - 3   7 
3 - 4   9 
2 - 5   4 
5 - 6   2 
6 - 7   1 
Total MST Weight: 37 
Random starting vertex: 0 
Edge    Weight 
0 - 1   4 
5 - 2   4 
2 - 3   7 
3 - 4   9 
6 - 5   2 
7 - 6   1 
0 - 7   8 
2 - 8   2 
Total MST Weight: 37
   */
