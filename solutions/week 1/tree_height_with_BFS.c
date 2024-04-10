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
int maxHeightWithBFS(GRAPH*, int, int);

int main(){
	int n, i, src, root;
	scanf("%d", &n);
	GRAPH* graph = createGraph(n);
	for(i=0;i<n;i++){
		scanf("%d", &src);
		if(src == -1) root = i;
		else addEdges(graph, n, src, i);
	}

	printf("%d", maxHeightWithBFS(graph, n, root));
	
	return 0;
}

//size o seviyedeki node say�s�n� tutuyor. size kadar gezme i�lemi yap�nca head, size kadar ilerleyece�inden for bitince o seviyedeki nodelar�n
//hepsini gezmi� oluyoruz. o seviyeyi bitirdi�imizden depth'i bir art�r�p tail artt�ysa yani sonraki seviyede node varsa sonraki turda tekrardan
//ayn� i�lemi yap�caz. (size kadar gez o seviyedeki t�m node'lar� bitir.)  

int maxHeightWithBFS(GRAPH* graph, int n, int root){
	int* queue = (int*) malloc(n*sizeof(int));
	int head = 0, tail = 0, depth=0, size, i;
	NODE* temp;
	queue[tail++] = root;
	while(head < tail){
		size = tail - head;
		for(i=0;i<size;i++){
			temp = graph -> adjList[queue[head++]];
			while(temp != NULL){
				queue[tail++] = temp -> vertex;
				temp = temp -> next;
			}
		}
		depth++;
	}
	free(queue);
	
	return depth;
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
