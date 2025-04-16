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
0 4 INF INF INF INF INF 8 INF
4 0 8 INF INF INF INF 11 INF
INF 8 0 7 INF 4 INF INF 2
INF INF 7 0 9 14 INF INF INF
INF INF INF 9 0 10 INF INF INF
INF INF 4 14 10 0 2 INF INF
INF INF INF INF INF 2 0 1 6
8 11 INF INF INF INF 1 0 7
INF INF 2 INF INF INF 6 7 0

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 9
#define INF INT_MAX

typedef struct {
    int vertex;
    int key;
} MinHeapNode;

typedef struct {
    MinHeapNode *array;
    int *pos;
    int size;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->pos = (int*)malloc(V * sizeof(int));
    heap->size = capacity;
    heap->array = (MinHeapNode*)malloc(V * sizeof(MinHeapNode));
    return heap;
}

void swapMinHeapNode(MinHeapNode *a, MinHeapNode *b) {
    MinHeapNode t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2*idx + 1;
    int right = 2*idx + 2;

    if (left < heap->size && heap->array[left].key < heap->array[smallest].key)
        smallest = left;

    if (right < heap->size && heap->array[right].key < heap->array[smallest].key)
        smallest = right;

    if (smallest != idx) {
        MinHeapNode smallestNode = heap->array[smallest];
        MinHeapNode idxNode = heap->array[idx];

        heap->pos[smallestNode.vertex] = idx;
        heap->pos[idxNode.vertex] = smallest;

        swapMinHeapNode(&heap->array[smallest], &heap->array[idx]);
        minHeapify(heap, smallest);
    }
}

int isInMinHeap(MinHeap *heap, int v) {
    return heap->pos[v] < heap->size;
}

MinHeapNode extractMin(MinHeap *heap) {
    if (heap->size == 0) return (MinHeapNode){-1, -1};

    MinHeapNode root = heap->array[0];
    MinHeapNode lastNode = heap->array[heap->size - 1];
    heap->array[0] = lastNode;

    heap->pos[root.vertex] = heap->size - 1;
    heap->pos[lastNode.vertex] = 0;

    heap->size--;
    minHeapify(heap, 0);

    return root;
}

void decreaseKey(MinHeap *heap, int v, int key) {
    int i = heap->pos[v];
    heap->array[i].key = key;

    while (i && heap->array[i].key < heap->array[(i - 1)/2].key) {
        heap->pos[heap->array[i].vertex] = (i - 1)/2;
        heap->pos[heap->array[(i - 1)/2].vertex] = i;
        swapMinHeapNode(&heap->array[i], &heap->array[(i - 1)/2]);
        i = (i - 1)/2;
    }
}

void primMST(int graph[V][V]) {
    int parent[V];
    int key[V];
    MinHeap *heap = createMinHeap(V);

    for (int v = 0; v < V; v++) {
        parent[v] = -1;
        key[v] = INF;
        heap->array[v].vertex = v;
        heap->array[v].key = key[v];
        heap->pos[v] = v;
    }

    key[0] = 0;
    heap->array[0].key = 0;

    while (heap->size > 0) {
        MinHeapNode minNode = extractMin(heap);
        int u = minNode.vertex;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && graph[u][v] != INF && isInMinHeap(heap, v) && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
                decreaseKey(heap, v, key[v]);
            }
        }
    }

    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%c - %c \t%d\n", parent[i] + 'a', i + 'a', graph[i][parent[i]]);
}

int main() {
    FILE *fp = fopen("graph.txt", "r");
    if (!fp) {
        printf("File not found!\n");
        return 1;
    }

    int graph[V][V];
    char word[10];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            fscanf(fp, "%s", word);
            if (word[0] == 'I') graph[i][j] = INF;
            else graph[i][j] = atoi(word);
        }
    }

    fclose(fp);
    primMST(graph);
    return 0;
}
/* OUTPUT
Edge    Weight
a - b   4
f - c   4
c - d   7
d - e   9
g - f   2
h - g   1
a - h   8
c - i   2
*/
