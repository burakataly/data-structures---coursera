#include <stdio.h>
#include <stdlib.h>

typedef struct n{
	int key;
	int left;
	int right;
}node;

void preorder(node* tree, int i){
    if(i == -1) return;
	printf("%d ", tree[i].key);
    preorder(tree, tree[i].left);
    preorder(tree, tree[i].right);
}

void inorder(node* tree, int i){
    if(i == -1) return;
    inorder(tree, tree[i].left);
    printf("%d ", tree[i].key);
    inorder(tree, tree[i].right);
}

void postorder(node* tree, int i){
    if(i == -1) return;
    postorder(tree, tree[i].left);
    postorder(tree, tree[i].right);
	printf("%d ", tree[i].key);
}

void treeTraversal(node* tree){
	inorder(tree, 0);
	printf("\n");
	preorder(tree, 0);
	printf("\n");
	postorder(tree, 0);
}

int main(){
	int n, i;
	scanf("%d", &n);
	node* tree = (node*) malloc(n * sizeof(node));
	
	for(i=0;i<n;i++){
		scanf("%d %d %d", &tree[i].key, &tree[i].left, &tree[i].right);
	}
	
	treeTraversal(tree);
	
	return 0;
}
