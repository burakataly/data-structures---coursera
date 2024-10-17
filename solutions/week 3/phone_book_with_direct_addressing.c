#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10000000

typedef struct{
	char type[10];
	char name[16];
	int number;
}QUERY;

void readQueries(QUERY* queries, int n);
void processQueries(QUERY* queries, int n, char** map);

int main(){
	char** map = (char**) calloc(MAX, sizeof(char*));
	int n;
	
	scanf("%d", &n);
	
	QUERY *queries = (QUERY*) malloc(n * sizeof(QUERY));
	
	readQueries(queries, n);
	
	processQueries(queries, n, map);
	
	return 0;
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

void processQueries(QUERY* queries, int n, char** map){
	int i;
	
	for(i=0;i<n;i++){
		if(queries[i].type[0] == 'a'){
			map[queries[i].number] = (char*) malloc(16 * sizeof(char));
			strcpy(map[queries[i].number], queries[i].name);
		}
		else if(queries[i].type[0] == 'f'){
			if(map[queries[i].number] == NULL){
				printf("not found\n");
			}
			else{
				printf("%s\n", map[queries[i].number]);
			}
		}
		else{
			free(map[queries[i].number]);
			map[queries[i].number] = NULL;
		}
	}
}
