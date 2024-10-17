#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
	char type[10];
	char name[16];
	int chain;
}QUERY;

typedef struct node{
	char key[17];
	struct node* next;
}NODE;

typedef struct map{
	long long m; //the number of chains (buckets) in the map
	int n; //the number of pairs currently in the map
	long long p;
	long long x;
	NODE **chainingList; //list of chains
}MAP;

long long polyHash(MAP* map, char* str);
MAP* createHashMap(long long m);
NODE* createNewNode(char* name);
int hasKey(MAP* map, char* key);
void set(MAP** map, char* name);
int get(MAP* map, char* key);
void removePair(MAP* map, char* key);
void freeMap(MAP* map);
void printChain(MAP* map, int chain);
void readQueries(QUERY* queries, int n);
void processQueries(QUERY* queries, int n, MAP* map);

int main(){
	long long m;
	scanf("%ld", &m);
	MAP* map = createHashMap(m);
	map->p = 1000000007;
	map->x = 263;
	int n;
	
	scanf("%d", &n);
	
	QUERY *queries = (QUERY*) malloc(n * sizeof(QUERY));
	
	readQueries(queries, n);
	
	processQueries(queries, n, map);
	
	return 0;
}

//hash function that applies universal hashing
long long polyHash(MAP* map, char* str){
	int k, n = strlen(str);
	
	long long hash = 0;
	
	for(k=n-1;k>=0;k--){
		hash = ((hash * map->x) % map->p + str[k]) % map->p;
	}
	
	return hash % map->m;
}

MAP* createHashMap(long long m){
	MAP* map = (MAP*) calloc(1, sizeof(MAP));
	map->m = m;
	map->n = 0;
	map->chainingList = (NODE**) calloc(m, sizeof(NODE*));
	return map;
}

NODE* createNewNode(char* name){
	NODE* node = (NODE*) calloc(1, sizeof(NODE));
	strcpy(node->key, name);
	return node;
}

void printChain(MAP* map, int chain){
	NODE* temp = map->chainingList[chain];
	 
	while(temp != NULL){
		printf("%s ", temp->key);
		temp = temp->next;
	};
	printf("\n");
}

int hasKey(MAP* map, char* key){
	long long chain = polyHash(map, key);
	NODE* temp = map->chainingList[chain]; 
	while(temp != NULL){
		if(!strcmp(temp->key, key)){
			return 1;
		}
		temp = temp->next;
	};
	return 0;
}

void set(MAP** map, char* name){
	long long chain = polyHash(*map, name);
	NODE* temp = (*map)->chainingList[chain];
	if(hasKey(*map, name)) return;

	NODE* node = createNewNode(name);
	node->next = (*map)->chainingList[chain];
	(*map)->chainingList[chain] = node;
	
	(*map)->n++;
}

int get(MAP* map, char* key){
	long long chain = polyHash(map, key);
	NODE* temp = map->chainingList[chain];
	while(temp != NULL && strcmp(temp->key, key)){
		temp = temp->next;
	};
	return (temp != NULL);
}

void removePair(MAP* map, char* key){
	long long chain = polyHash(map, key);
	NODE* temp = map->chainingList[chain];
	
	if(temp == NULL) return;
	if(!strcmp(temp->key, key)){
		map->chainingList[chain] = temp->next;
		free(temp);
		map->n--;
		return;
	}
	
	while(temp->next != NULL && strcmp(temp->next->key, key)){
		temp = temp->next;
	}
	
	if(temp->next == NULL) return;
	
	NODE* temp2 = temp->next;
	temp->next = temp->next->next;
	free(temp2);
	map->n--;
}

void freeMap(MAP* map){
	long long i;
	
	for(i=0;i<map->m;i++){
		NODE* temp = map->chainingList[i];
        while(temp != NULL){
            NODE* deleting = temp;
            temp = temp->next;
			free(deleting->key);
            free(deleting);
        }
	}
	
	free(map->chainingList);
	free(map);
}

void readQueries(QUERY* queries, int n){
	int i;
	
	for(i=0;i<n;i++){
		scanf("%s", &queries[i].type);
		if(queries[i].type[0] == 'c'){
			scanf("%d", &queries[i].chain);
		}
		else{
			scanf("%s", &queries[i].name);		
		}	
	}
}

void processQueries(QUERY* queries, int n, MAP* map){
	int i;
	
	for(i=0;i<n;i++){
		if(queries[i].type[0] == 'a'){
			set(&map, queries[i].name);
		}
		else if(queries[i].type[0] == 'f'){
			get(map, queries[i].name) ? printf("yes\n") : printf("no\n");
		}
		else if(queries[i].type[0] == 'd'){
			removePair(map, queries[i].name);
		}
		else{
			printChain(map, queries[i].chain);
		}
	}
}
