#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 500001

typedef struct{
	int *arr;
	int capacity;
	int size;
}VECTOR;

VECTOR* createVector(){
	VECTOR* vector = (VECTOR*) malloc(sizeof(VECTOR));
	if(vector == NULL){
        printf("Memory allocation failed!\n");
        exit(1);
    }
	vector->capacity = 2;
	vector->size = 0;
	vector->arr = (int*) malloc(2 * sizeof(int));
	if(vector->arr == NULL){
        printf("Memory allocation failed!\n");
        exit(1);
    }
	return vector;
}

void append(VECTOR* vector, int i){
	if(vector->size == vector->capacity){
		vector->capacity *= 2;
		int* temp = (int*) realloc(vector->arr, vector->capacity * sizeof(int));
		if(temp != NULL){
			vector->arr = temp;
		}
		else{
			printf("Memory allocation failed!\n");
			exit(1);
		}
	}
	
	vector->arr[vector->size++] = i;
}

//polynomial hashing for string keys
long long polyHash(char* str, int i, int j, long long p, long long x){
	int k, n = strlen(str);
	long long hash = 0;
	
	for(k=j;k>=i;k--){
		hash = ((hash * x) % p + str[k]) % p;
	}
	
	return hash;
}

int areEquals(char* str1, int a, int b, char* str2, int c, int d){
	int i, n = b - a + 1;
	if(a > b || c > d || (b - a) != (d - c)) return 0;
	
	for(i=0;i<n;i++){
		if(str1[a + i] != str2[c + i]) return 0;
	}
	
	return 1;
}

void rabinKarps(char* T, char* P, long long p, long long x){
	int i, n = strlen(P), m = strlen(T);
	long long y = 1;
	VECTOR* vector = createVector();

	for(i=0;i<n;i++) y = (y * x) % p; //x^n % p
	
	long long hashP = polyHash(P, 0, n - 1, p, x);
	long long hashSub = polyHash(T, m - n, m - 1, p, x);

	if(hashP == hashSub && areEquals(P, 0, n - 1, T, m - n, m - 1)){
		append(vector, m - n);
	}

	for(i=m-n-1;i>=0;i--){
		hashSub = (((hashSub * x) % p + T[i] - (y * T[i + n])) % p + p) % p;
		if(hashP == hashSub && areEquals(P, 0, n - 1, T, i, i + n - 1)){
			append(vector, i);
		}
	}
	
	for(i=vector->size-1;i>=0;i--){
		printf("%d ", vector->arr[i]);
	}
	
	free(vector->arr);
	free(vector);
}

int main(){
	long long p = 1000000007, x = 31;
	char* T = (char*) malloc(MAX * sizeof(char));
	char* P = (char*) malloc(MAX * sizeof(char));
	
	scanf("%s", P);
	scanf("%s", T);
	
	rabinKarps(T, P, p, x);
	
	free(P);
	free(T);
	
	return 0;
}
