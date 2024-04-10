#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int parent;
	int rank;
	int data;
}node;


void makeSet(node* nodes, int n, int i, int data){
	nodes[i].parent = i;
	nodes[i].rank = 0;
	nodes[i].data = data;
}

int find(node* nodes, int n, int i){
	if(i != nodes[i].parent) nodes[i].parent = find(nodes, n, nodes[i].parent);
	return nodes[i].parent;
}

int setUnion(node* nodes, int n, int i, int j){
	int id1 = find(nodes, n, i);
	int id2 = find(nodes, n, j);
	if(id1 == id2) return -1;
	
	if(nodes[id2].rank > nodes[id1].rank){
		nodes[id1].parent = id2;
		nodes[id2].data += nodes[id1].data;
		nodes[id1].data = 0;
		return nodes[id2].data;
	}
	else{
		nodes[id2].parent = id1;
		nodes[id1].data += nodes[id2].data;
		nodes[id2].data = 0;
		if(nodes[id1].rank == nodes[id2].rank){
			nodes[id1].rank++;
		}
		return nodes[id1].data;
	}
}

int main(){
	int n, m, i, data, max = 0, dest, src;
	
	scanf("%d %d", &n, &m);
	node* nodes = (node*) malloc(n * sizeof(node));
	
	for(i=0;i<n;i++){
		scanf("%d", &data);
		if(data > max) max = data;
		makeSet(nodes, n, i, data);
	}
	
	for(i=0;i<m;i++){
		scanf("%d %d", &dest, &src);
		data = setUnion(nodes, n, --dest, --src);
		if(data > max) max = data;
		printf("%d\n", max);
	}

	return 0;
}
