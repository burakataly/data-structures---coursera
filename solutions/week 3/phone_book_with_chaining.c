#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define N 10000000 //the range of input keys
#define M 128
#define CONST_STR "not found"

typedef struct{
	char type[10];
	char name[16];
	int number;
}QUERY;

typedef struct node{
	int key;
	char* value;
	struct node* next;
}NODE;

typedef struct map{
	int m; //the number of chains (buckets) in the map
	int n; //the number of pairs currently in the map
	long long p; //prime that is slightly bigger than the range of input keys N to use it in universal hash function
	long long a; //number between [1, p-1] to use it in universal hash function
	long long b; //number between [0, p-1] to use it in universal hash function
	NODE **chainingList; //list of chains
}MAP;

int isPrime(int num);
int findNextPrime(int num);
long long hashFunction(MAP* map, int key);
MAP* createHashMap(int m);
NODE* createNewNode(int key, char* name);
int hasKey(MAP* map, int key);
void set(MAP** map, int key, char* name);
char* get(MAP* map, int key);
void removePair(MAP* map, int key);
void freeMap(MAP* map);
MAP* resizeMap(MAP* map);
void readQueries(QUERY* queries, int n);
void processQueries(QUERY* queries, int n, MAP* map);

int main(){
	int n, m = M;
	MAP* map = createHashMap(m);
	
	srand(time(0));
	map->p = findNextPrime(N); //defining the hash function randomly from universal family before taking the inputs
	map->a = rand() % (map->p - 1) + 1;
	map->b = rand() % (map->p);
	
	scanf("%d", &n);
	
	QUERY *queries = (QUERY*) malloc(n * sizeof(QUERY));
	
	readQueries(queries, n);
	
	processQueries(queries, n, map);
	
	return 0;
}

//hash function that applies universal hashing (long long is used since overflow happens when int used)
long long hashFunction(MAP* map, int key){
    long long m = map->m;
    long long k = key;
	return (((map->a * k) % map->p + map->b) % map->p) % m;
}

int findNextPrime(int num){
	int p = num + 1;
	
	while(!isPrime(p)){
		p++;
	};
	
	return p;
}

int isPrime(int num){
	int temp = sqrt(num), i;
	
	for(i=2;i<=temp;i++){
		if(num % i == 0) return 0;
	}
	
    return 1;
}

MAP* createHashMap(int m){
	MAP* map = (MAP*) calloc(1, sizeof(MAP));
	map->m = m;
	map->n = 0;
	map->chainingList = (NODE**) calloc(m, sizeof(NODE*));
	return map;
}

NODE* createNewNode(int key, char* name){
	NODE* node = (NODE*) calloc(1, sizeof(NODE));
	node->key = key;
	node->value = (char*) malloc(17 * sizeof(char));
	strcpy(node->value, name);
	return node;
}

int hasKey(MAP* map, int key){
	long long chain = hashFunction(map, key);
	NODE* temp = map->chainingList[chain]; 
	while(temp != NULL){
		if(temp->key == key) return 1;
		temp = temp->next;
	};
	return 0;
}

void set(MAP** map, int key, char* name){
	long long chain = hashFunction(*map, key);
	NODE* temp = (*map)->chainingList[chain];
	
	while(temp != NULL){
		if(temp->key == key){ //if key is already in the chain, we change the value of the key - value pair.
			strcpy(temp->value, name);
			return;
		}
		temp = temp->next;
	};
	
	NODE* node = createNewNode(key, name);
	node->next = (*map)->chainingList[chain];
	(*map)->chainingList[chain] = node;
	
	(*map)->n++;
	*map = resizeMap(*map);
}

char* get(MAP* map, int key){
	long long chain = hashFunction(map, key);
	NODE* temp = map->chainingList[chain];
	while(temp != NULL && temp->key != key){
		temp = temp->next;
	};
	return (temp != NULL) ? temp->value : CONST_STR;
}

void removePair(MAP* map, int key){
	long long chain = hashFunction(map, key);
	NODE* temp = map->chainingList[chain];
	
	if(temp == NULL) return;
	if(temp->key == key){
		map->chainingList[chain] = temp->next;
		free(temp);
		map->n--;
		return;
	}
	
	while(temp->next != NULL && temp->next->key != key){
		temp = temp->next;
	}
	
	if(temp->next == NULL) return;
	
	NODE* temp2 = temp->next;
	temp->next = temp->next->next;
	free(temp2);
	map->n--;
}

void freeMap(MAP* map){
	int i;
	
	for(i=0;i<map->m;i++){
		NODE* temp = map->chainingList[i];
        while(temp != NULL){
            NODE* deleting = temp;
            temp = temp->next;
			free(deleting->value);
            free(deleting);
        }
	}
	
	free(map->chainingList);
	free(map);
}

MAP* resizeMap(MAP* map){ //resizing the map if load factor becomes exceeds 1 since we would get long chains when it is bigger than 1
	int load_factor = map->n / map->m;
	
	if(load_factor >= 1){
		int i;
		MAP* newMap = createHashMap(map->m * 2);
		newMap->p = map->p;
		newMap->a = rand() % (newMap->p - 1) + 1;
		newMap->b = rand() % (newMap->p);
		for(i=0;i<map->m;i++){
			NODE* temp = map->chainingList[i];
			while(temp != NULL){
				set(&newMap, temp->key, temp->value);
				temp = temp->next;
			}
		}
		
		free(map);
		return newMap;
	}
	
	return map;
}

void readQueries(QUERY* queries, int n){
	int i;
	
	for(i=0;i<n;i++){
		scanf("%s", &queries[i].type);
		if(queries[i].type[0] == 'a'){
			scanf("%d %s", &queries[i].number, &queries[i].name);
		}
		else{
			scanf("%d", &queries[i].number);		
		}	
	}
}

void processQueries(QUERY* queries, int n, MAP* map){
	int i;
	
	for(i=0;i<n;i++){
		if(queries[i].type[0] == 'a'){
			set(&map, queries[i].number, queries[i].name);
		}
		else if(queries[i].type[0] == 'f'){
			printf("%s\n", get(map, queries[i].number));
		}
		else{
			removePair(map, queries[i].number);
		}
	}
}
