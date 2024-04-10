#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct n{
	int key;
	int left;
	int right;
}node;

int isBST(node* tree, int i, int minVal, int maxVal){
	if(i == -1) return 1;
	if(tree[i].key <= minVal || tree[i].key >= maxVal) return 0;
	return isBST(tree, tree[i].left, minVal, tree[i].key) && isBST(tree, tree[i].right, tree[i].key, maxVal);
}

int main(){
	int n, i, result;
	scanf("%d", &n);
	node* tree = (node*) malloc(n * sizeof(node));
	
	for(i=0;i<n;i++){
		scanf("%d %d %d", &tree[i].key, &tree[i].left, &tree[i].right);
	}
	
	result = (n) ? isBST(tree, 0, INT_MIN, INT_MAX) : 1;
	if(result) printf("CORRECT");
	else printf("INCORRECT");
	
	return 0;
}
