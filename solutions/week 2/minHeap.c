#include <stdio.h>
#include <stdlib.h>

void siftDown(int* heap, int* result, int n, int i, int* m);
void buildHeap(int* arr, int n);

int main(){
	int* arr;
	int i, n;
	scanf("%d", &n);
	arr = (int*) malloc(n*sizeof(int));
	for(i=0;i<n;i++) scanf("%d", arr + i);
	buildHeap(arr, n);
	
	return 0;
}

void buildHeap(int* arr, int n){
	int i, m=0;
	int* result = (int*) malloc(3*n*sizeof(int));
	for(i=n/2;i>=0;i--) siftDown(arr, result, n, i, &m);
	printf("%d\n", m/2);
	for(i=0;i<m;i+=2){
		printf("%d %d\n", result[i], result[i+1]);
	}
}

void siftDown(int* heap, int* result, int n, int i, int* m){
	int temp, index = i;
	
	do{
		i = index;
		if(2 * i + 1 < n && heap[2 * i + 1] < heap[index]){
			index = 2 * i + 1;
		}
		if(2 * i + 2 < n && heap[2 * i + 2] < heap[index]){
			index = 2 * i + 2;
		}
		temp = heap[i];
		heap[i] = heap[index];
		heap[index] = temp;
		
		if(i != index){
			result[*m] = i;
			result[*m + 1] = index;
			*m += 2;
		}
	} while(i != index);
}
