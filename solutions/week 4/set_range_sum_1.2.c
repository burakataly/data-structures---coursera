#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	long long key;
	long long sum;
	struct node* left;
	struct node* right;
	struct node* parent;
}NODE;

NODE* createNode(long long key);
NODE* find(NODE* root, long long key);
NODE* sFind(NODE* root, long long key);
NODE* insertNode(NODE** root, long long key);
void insertToST(NODE** root, long long key);
void deleteFromST(NODE** root, long long key);
void split(NODE* root, long long key, NODE** root1, NODE** root2);
NODE* merge(NODE* root1, NODE* root2);
NODE* splay(NODE* node);
void rotateRight(NODE* node);
void rotateLeft(NODE* node);
NODE* treeMax(NODE* root);
NODE* treeMin(NODE* root);
long long sum(NODE* node);
void adjustSum(NODE* node);
long long rangeSum(long long x, long long y, NODE** root);

int main(){
	int i, n, M = 1000000001, parts; 
	long long num1, num2, sum = 0;
	NODE* root = NULL;
	char *input = (char*) malloc(30 * sizeof(char)); 
	char operation;
	scanf("%d", &n);
	
	for(i=0;i<n;i++){
		scanf(" %[^\n]s", input);
		parts = sscanf(input, "%c %lld %lld", &operation, &num1, &num2);
		if(parts >= 2){
			switch(operation){
				case '+':
					insertToST(&root, (num1 + sum) % M);
					break;
				case '-':
					deleteFromST(&root, (num1 + sum) % M);
					break;
				case '?':
					root = sFind(root, (num1 + sum) % M);
					(root == NULL || root->key != (num1 + sum) % M) ? printf("Not found\n") : printf("Found\n");
					break;
				case 's':
					sum = rangeSum((num1 + sum) % M, (num2 + sum) % M, &root);
					printf("%lld\n", sum);
					break;
			}
		}
	}
	return 0;
}

NODE* createNode(long long key){
	NODE* node = (NODE*) calloc(1, sizeof(NODE));
	node->key = key;
	node->sum = key;
	return node;
}

NODE* find(NODE* root, long long key){
	if(root == NULL) return NULL;
	if(root -> key == key) return root;
	if(root -> key > key) return (root -> left != NULL) ? find(root -> left, key) : root;
	if(root -> key < key) return (root -> right != NULL) ? find(root -> right, key) : root;
}

NODE* sFind(NODE* root, long long key){
	NODE* node = find(root, key);
	splay(node);
	return node;
}

long long sum(NODE* node){
	return (node == NULL) ? 0ll : node->sum;
}

void adjustSum(NODE* node){
	if(node == NULL) return;
	node->sum = sum(node->left) + sum(node->right) + node->key;
}

NODE* insertNode(NODE** root, long long key){
	NODE* node = find(*root, key);
	if(node == NULL){
		*root = createNode(key);
		return *root;
	}
	if(node->key == key) return node;
	if(node -> key > key){
		node -> left = createNode(key);
		node -> left -> parent = node; //parent'ýný ekleme ihityacý varsa diye
		return node -> left;
	}
	if(node -> key < key){
		node -> right = createNode(key);
		node -> right -> parent = node;
		return node -> right;
	}
}

void insertToST(NODE** root, long long key){
	NODE* node = insertNode(root, key);
	splay(node);
	*root = node;
}

void deleteFromST(NODE** root, long long key){
	NODE* node = sFind(*root, key);
	if(node == NULL || node->key != key){
		*root = node;
		return;
	}
	if(node->left != NULL) node->left->parent = NULL;
	if(node->right != NULL) node->right->parent = NULL;
	*root = merge(node->left, node->right);
	free(node);
}

void split(NODE* root, long long key, NODE** root1, NODE** root2){
	if(root == NULL){
		*root1 = NULL;
		*root2 = NULL;
		return;
	}
	NODE* node = sFind(root, key);
	if(node->key > key){
		*root1 = node->left;
		*root2 = node;
		if(node->left != NULL) node->left->parent = NULL;
		node->left = NULL;
		adjustSum(*root2);
	}
	else{
		*root1 = node;
		*root2 = node->right;
		if(node->right != NULL) node->right->parent = NULL;
		node->right = NULL;
		adjustSum(*root1);
	}
}

NODE* merge(NODE* root1, NODE* root2){
	if(root1 == NULL) return root2;
	if(root2 == NULL) return root1;
	NODE* max1 = treeMax(root1);
	NODE* min2 = treeMin(root2);
	
	if(max1 -> key > min2 -> key) return NULL;
	else{
		splay(max1);
		max1->right = root2;
		root2->parent = max1;
		adjustSum(max1);
		return max1;		
	}
}

NODE* treeMax(NODE* root){
	if(root == NULL) return NULL;
	while(root->right != NULL) root = root -> right;
	return root;
}

NODE* treeMin(NODE* root){
	if(root == NULL) return NULL;
	while(root -> left != NULL) root = root -> left;
	return root;
}

//the given node is going to be root after this function
NODE* splay(NODE* node){
	if(node == NULL) return NULL;
	//zig = rightRotate, zag = leftRotate
	while(node->parent != NULL){		
		if(node->parent->parent == NULL){ //zig or zag
			(node->parent->left == node) ? rotateRight(node->parent) : rotateLeft(node->parent);
		}
		else if(node->parent->left == node){
			if(node->parent->parent->left == node->parent){ //zig-zig
				rotateRight(node->parent->parent);
				rotateRight(node->parent);
			}
			else{ //zag-zig
				rotateRight(node->parent);
				rotateLeft(node->parent);
			}
		}
		else{
			if(node->parent->parent->right == node->parent){ //zag-zag
				rotateLeft(node->parent->parent);
				rotateLeft(node->parent);
			}
			else{ //zig-zag
				rotateLeft(node->parent);
				rotateRight(node->parent);
			}
		}
	}
	return node;
}

void rotateRight(NODE* node){
	NODE *temp = node -> left;
	
	temp -> parent = node -> parent;
	if(temp -> parent != NULL){
		if(temp->parent->left == node) temp -> parent -> left = temp;
		else temp -> parent -> right = temp;
	}
	
	node -> left = temp->right;
	if(temp->right != NULL) temp->right->parent = node;
	
	temp -> right = node;
	node -> parent = temp;
	
	adjustSum(node);
	adjustSum(temp);
}

void rotateLeft(NODE* node){
	NODE *temp = node->right;
	
	temp -> parent = node -> parent;
	if(temp -> parent != NULL){
		if(temp->parent->left == node) temp -> parent -> left = temp;
		else temp -> parent -> right = temp;
	}
	
	node->right = temp->left;
	if(temp->left != NULL) temp->left->parent = node;
	
	temp -> left = node;
	node -> parent = temp;
	
	adjustSum(node);
	adjustSum(temp);
}

/*
after the first split, left will store the tree with elements less than and equal to x-1 and middle will store the tree with bigger elements than x-1. 
after the second split, middle will store the tree with elements less than and equal to y and bigger than x-1 while right will have the tree with elements 
bigger than y. since we use sum field to know the sum of all the keys in that subtree, we can simply return sum field of middle. now we should merge left,
middle and right trees to get the initial tree.
*/

long long rangeSum(long long x, long long y, NODE** root){
	NODE *left = NULL, *middle = NULL, *right = NULL;
	split(*root, x-1, &left, &middle);
	split(middle, y, &middle, &right);
	long long result = sum(middle);
	middle = merge(left, middle);
	*root = merge(middle, right);
	return result;
}

