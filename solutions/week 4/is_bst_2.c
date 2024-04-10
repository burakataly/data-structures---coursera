#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct n{
	long long key;
	int left;
	int right;
}node;

int isBST(node* tree, int i, long long minVal, long long maxVal){
	if(i == -1) return 1;
	if(tree[i].key < minVal || tree[i].key >= maxVal) return 0;
	return isBST(tree, tree[i].left, minVal, tree[i].key) && isBST(tree, tree[i].right, tree[i].key, maxVal);
}

int main(){
	int n, i;
	int result;
	scanf("%d", &n);
	node* tree = (node*) malloc(n * sizeof(node));
	
	for(i=0;i<n;i++){
		scanf("%ld %ld %ld", &tree[i].key, &tree[i].left, &tree[i].right);
	}
	
	result = (n) ? isBST(tree, 0, LLONG_MIN, LLONG_MAX) : 1;
	if(result) printf("CORRECT");
	else printf("INCORRECT");
	
	return 0;
}
