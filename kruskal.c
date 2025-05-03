/*WAP to find the MST of a given graph using Kruskal’s algorithm. Check your
program on a graph whose length matrix is given above. Your program should use UNION &amp;
FIND operations on Disjoint data structure. */

#CODE
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_NODES 100
typedef struct Node{
    int vertex;
    int weight;
    struct Node* next;
}Node;
typedef struct Graph{
    int numVertices;
    struct Node** adjLists;
}Graph;
typedef struct{
    int u,v,weight;
}Edge;
int parent[MAX_NODES],rank[MAX_NODES];
Edge edges[MAX_NODES*MAX_NODES];
int edgeCount=0;
Node* createNode(int v,int w){
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->vertex=v;
    newNode->weight=w;
    newNode->next=NULL;
    return newNode;
}
Graph* createGraph(int vertices){
    Graph* graph=(Graph*)malloc(sizeof(Graph));
    graph->numVertices=vertices;
    graph->adjLists=(struct Node**)malloc(vertices*sizeof(struct Node*));
    for(int i=0;i<vertices;i++)
        graph->adjLists[i]=NULL;
    return graph;
}
void addEdge(Graph* graph,int u,int v,int w){
    Node* newNode=createNode(v,w);
    newNode->next=graph->adjLists[u];
    graph->adjLists[u]=newNode;
    newNode=createNode(u,w);
    newNode->next=graph->adjLists[v];
    graph->adjLists[v]=newNode;
}
void makeSet(int n){
    for(int i=0;i<n;i++){
        parent[i]=i;
        rank[i]=0;
    }
}
int findSet(int v){
    if(parent[v]!=v)
        parent[v]=findSet(parent[v]);
    return parent[v];
}
void unionSets(int u,int v){
    int rootU=findSet(u);
    int rootV=findSet(v);
    if(rootU!=rootV){
        if(rank[rootU]<rank[rootV])
            parent[rootU]=rootV;
        else if(rank[rootU]>rank[rootV])
            parent[rootV]=rootU;
        else{
            parent[rootV]=rootU;
            rank[rootU]++;
        }
    }
}
void swap(Edge *a,Edge *b){
    Edge temp=*a;
    *a=*b;
    *b=temp;
}
int randomizedPartition(Edge arr[],int low,int high){
    int p=low+rand()%(high-low+1);
    Edge temp=arr[p];
    arr[p]=arr[high];
    arr[high]=temp;
    int pivot=arr[high].weight;
    int i=low-1;
    for(int j=low;j<high;j++){
        if(arr[j].weight<=pivot){
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i+1],&arr[high]);
    return i+1;
}
void quickSort(Edge arr[],int low,int high){
    if(low<high){
        int pi=randomizedPartition(arr,low,high);
        quickSort(arr,low,pi-1);
        quickSort(arr,pi+1,high);
    }
}
void buildEdgeList(Graph* graph,int n){
    int visited[MAX_NODES][MAX_NODES]={0};
    edgeCount=0;
    for(int u=0;u<n;u++){
        Node* temp=graph->adjLists[u];
        while(temp){
            int v=temp->vertex;
            int w=temp->weight;
            if(!visited[u][v]){
                edges[edgeCount].u=u;
                edges[edgeCount].v=v;
                edges[edgeCount].weight=w;
                edgeCount++;
                visited[u][v]=visited[v][u]=1;
            }
            temp=temp->next;
        }
    }
}
void kruskalMST(Graph* graph,int vertices){
    makeSet(vertices);
    buildEdgeList(graph,vertices);
    quickSort(edges,0,edgeCount-1);
    int totalWeight=0;
    printf("Edges in the Minimum Spanning Tree:\n");
    printf("Vertices    Weight\n");
    for(int i=0;i<edgeCount;i++){
        int u=edges[i].u;
        int v=edges[i].v;
        int w=edges[i].weight;
        if(findSet(u)!=findSet(v)){
            printf("%d - %d\t\t%d\n",u,v,w);
            totalWeight+=w;
            unionSets(u,v);
        }
    }
    printf("Total weight of MST: %d\n",totalWeight);
}
int main(){
    srand(time(NULL));
    int vertices;
    FILE *fptr=fopen("graph.txt","r");
    fscanf(fptr,"%d",&vertices);
    struct Graph* graph=createGraph(vertices);
    while(!feof(fptr)){
        int a,b,c;
        fscanf(fptr,"%d%d%d",&a,&b,&c);
        addEdge(graph,a,b,c);
    }
    kruskalMST(graph,vertices);
    for(int i=0;i<vertices;i++){
        Node* curr=graph->adjLists[i];
        while(curr){
            Node* temp=curr;
            curr=curr->next;
            free(temp);
        }
    }
    free(graph);
    return 0;
}

#INPUT
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

#OUTPUT
Edges in the Minimum Spanning Tree:
Vertices    Weight
6 - 7           1
2 - 8           2
5 - 6           2
2 - 5           4
0 - 1           4
2 - 3           7
0 - 7           8
3 - 4           9
Total weight of MST: 37
