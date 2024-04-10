#include <stdio.h>
#include <stdlib.h>

struct node{
	int vertex;
	struct node* next;
};

typedef struct node NODE;

struct graph{
	int numOfNodes;
	NODE** adjList;
};

typedef struct graph GRAPH;

NODE* createNode(int);
GRAPH* createGraph(int);
void addEdges(GRAPH*, int, int, int);
int maxHeightWithDFS(GRAPH*, int, int);

int main(){
	int n, i, src, root;
	scanf("%d", &n);
	GRAPH* graph = createGraph(n);
	for(i=0;i<n;i++){
		scanf("%d", &src);
		if(src == -1) root = i;
		else addEdges(graph, n, src, i);
	}
	
	printf("%d\n", maxHeightWithDFS(graph, n, root));

	return 0;
}

int maxHeightWithDFS(GRAPH* graph, int n, int root){
	int max = 0, result;
	NODE* temp = graph -> adjList[root];
	while(temp != NULL){
		result = maxHeightWithDFS(graph, n, temp -> vertex);
		if(result > max) max = result;
		temp = temp -> next;
	}
	
	return max+1;
}

NODE* createNode(int vertex){
	NODE* node = (NODE*) malloc(sizeof(NODE));
	node -> vertex = vertex;
	node -> next = NULL;
	return node;
}

GRAPH* createGraph(int n){
	int i;
	GRAPH* graph = (GRAPH*) malloc(sizeof(GRAPH));
	graph -> numOfNodes = n;
	graph -> adjList = (NODE**) calloc(n, sizeof(NODE*));
	return graph;
}

void addEdges(GRAPH* graph, int n, int src, int dest){
	if(src == dest || src >= n || dest >= n) return;
		
	NODE* newNode = createNode(dest);
	newNode->next = graph->adjList[src];
	graph->adjList[src] = newNode;
}
