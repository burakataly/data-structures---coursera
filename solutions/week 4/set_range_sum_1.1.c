#include <stdio.h>
#include <stdlib.h>

//this is an avl implementation to solve the problem but couldnt pass the 69th test case due to time limit exceeded

typedef struct node{
	long long key;
	int height;
	struct node* left;
	struct node* right;
	struct node* parent;
}NODE;

NODE* createNode(long long key);
NODE* find(NODE* root, long long key);
NODE* findPositionToAdd(NODE* root, long long key);
NODE* insertNode(NODE** root, long long key);
NODE* insertToAVL(NODE** root, long long key);
NODE* deleteNode(NODE** root, long long key);
void deleteFromAVL(NODE** root, long long key);
int getBalance(NODE* node);
void adjustHeight(NODE* node);
int max(int a, int b);
void rebalanceRight(NODE** root, NODE* node);
void rebalanceLeft(NODE** root, NODE* node);
void rightRotation(NODE** root, NODE* node);
void leftRotation(NODE** root, NODE* node);
void rebalance(NODE** root, NODE* node);
NODE* nextLargest2(NODE* node);
NODE* descendant(NODE* node);
NODE* ancestor(NODE* node);
long long rangeSearch(long long x, long long y, NODE* root);

int main(){
	int i, n, M = 1000000001, parts; 
	long long num1, num2, sum = 0;
	NODE* root = NULL, *temp;
	char *input = (char*) malloc(30 * sizeof(char)); 
	char operation;
	scanf("%d", &n);
	
	for(i=0;i<n;i++){
		scanf(" %[^\n]s", input);
		parts = sscanf(input, "%c %lld %lld", &operation, &num1, &num2);
		if(parts >= 2){
			switch(operation){
				case '+':
					insertToAVL(&root, (num1 + sum) % M);
					break;
				case '-':
					deleteFromAVL(&root, (num1 + sum) % M);
					break;
				case '?':
					temp = find(root, (num1 + sum) % M);
					(temp == NULL || temp->key != (num1 + sum) % M) ? printf("Not found\n") : printf("Found\n");
					break;
				case 's':
					sum = rangeSearch((num1 + sum) % M, (num2 + sum) % M, root);
					printf("%lld\n", sum);		
					break;
			}
		}
	}
	
	return 0;
}

NODE* createNode(long long key){
	NODE* node = (NODE*) calloc(1, sizeof(NODE));
	node -> key = key;
	node -> height = 1;
	return node;
}

NODE* find(NODE* root, long long key){
	if(root == NULL) return NULL;
	if(root -> key == key) return root;
	if(root -> key > key) return (root -> left != NULL) ? find(root -> left, key) : root;
	if(root -> key < key) return (root -> right != NULL) ? find(root -> right, key) : root;
}

NODE* insertNode(NODE** root, long long key){
	NODE* node = find(*root, key);
	if(node == NULL){
		*root = createNode(key);
		return *root;
	}
	if(node -> key == key) return NULL;
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

NODE* insertToAVL(NODE** root, long long key){
	NODE* node = insertNode(root, key);
	if(node == NULL) return;
	rebalance(root, node);
	return node;
}

NODE* deleteNode(NODE** root, long long key){
	NODE* node = find(*root, key);
	if(node == NULL || node->key != key) return NULL;
	
	if(node -> right == NULL){
		NODE* parent = node -> parent;
		if(node -> parent != NULL){
			if(node -> key > node -> parent -> key) node -> parent -> right = node -> left;
			else node -> parent -> left = node -> left;
		}
		else *root = node -> left;
		
		if(node -> left != NULL) node -> left -> parent = node -> parent;
		free(node);
		return parent;
	}
	else{
		NODE* next = nextLargest2(node);
		NODE* parent = next -> parent;
		if(next -> key > next -> parent -> key) next -> parent -> right = next -> right;
		else next -> parent -> left = next -> right;
		if(next -> right != NULL) next -> right -> parent = next -> parent;
		node -> key = next -> key;
		free(next);
		return parent;
	}
}

void deleteFromAVL(NODE** root, long long key){
	NODE* parent = deleteNode(root, key);
	if(parent == NULL) return;
	rebalance(root, parent);
}

void rebalance(NODE** root, NODE* node){
	NODE* parent = node -> parent;
	int balance = getBalance(node);
	if(balance > 1){
		rebalanceRight(root, node);
	}
	if(balance < -1){
		rebalanceLeft(root, node);
	}
	adjustHeight(node);
	if(parent != NULL) rebalance(root, parent);
}

int getBalance(NODE* node){
	int leftH = (node -> left == NULL) ? 0 : node -> left -> height;
	int rightH = (node -> right == NULL) ? 0 : node -> right -> height;
	return leftH - rightH;
}

void adjustHeight(NODE* node){
	int leftH = (node -> left == NULL) ? 0 : node -> left -> height;
	int rightH = (node -> right == NULL) ? 0 : node -> right -> height;
	node -> height = max(leftH, rightH) + 1;
}

int max(int a, int b){
	return (a > b) ? a : b;
}

void rebalanceRight(NODE** root, NODE* node){
	NODE *temp = node -> left;
	if(temp == NULL) return;
	if(getBalance(temp) < 0) leftRotation(root, temp);
	rightRotation(root, node);
	adjustHeight(node);
	adjustHeight(temp);
}

void rebalanceLeft(NODE** root, NODE* node){
	NODE *temp = node -> right;
	if(getBalance(temp) > 0) rightRotation(root, temp);
	leftRotation(root, node);
	adjustHeight(node);
	adjustHeight(temp);
}

void rightRotation(NODE** root, NODE* node){
	NODE *temp1, *temp2;
	temp1 = node -> left;
	temp2 = temp1 -> right;
	
	temp1 -> parent = node -> parent;
	if(temp1 -> parent != NULL){
		if(temp1 -> parent -> key < temp1 -> key) temp1 -> parent -> right = temp1;
		else temp1 -> parent -> left = temp1;
	}
	else *root = temp1;
	
	node -> left = temp2;
	if(temp2 != NULL) temp2 -> parent = node;
	
	temp1 -> right = node;
	node -> parent = temp1;
}

void leftRotation(NODE** root, NODE* node){
	NODE *temp1, *temp2;
	temp1 = node -> right;
	temp2 = temp1 -> left;
	
	temp1 -> parent = node -> parent;
	if(temp1 -> parent != NULL){
		if(temp1 -> parent -> key < temp1 -> key) temp1 -> parent -> right = temp1;
		else temp1 -> parent -> left = temp1;
	}
	else *root = temp1;
	
	node -> right = temp2;
	if(temp2 != NULL) temp2 -> parent = node;
	
	temp1 -> left = node;
	node -> parent = temp1;
}

NODE* nextLargest2(NODE* node){
	if(node == NULL) return NULL;
	if(node -> right != NULL) return descendant(node -> right);
	else return ancestor(node);
}

NODE* descendant(NODE* node){
	return (node -> left != NULL) ? descendant(node -> left) : node;
}

NODE* ancestor(NODE* node){
	if(node -> parent == NULL) return NULL;
	if(node -> key < node -> parent -> key) return node -> parent;
	return ancestor(node -> parent);
}

long long rangeSearch(long long x, long long y, NODE* root){
	if(root == NULL) return 0;
	long long result = 0;
	NODE* node = find(root, x);
	while(node != NULL && node -> key <= y){
		if(node -> key >= x) result += node -> key;
		node = nextLargest2(node);
	}
	return result;
}
