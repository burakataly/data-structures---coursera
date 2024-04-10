#include <stdio.h>
#include <stdlib.h>

typedef struct n{
	int index;
	long long freeTime;
}node;

void siftDown(node* heap, int n, int i){
	int index = i;
	node temp;
	
	do{
		i = index;
		
		if((2 * i + 1 < n) && ((heap[2 * i + 1].freeTime < heap[index].freeTime) || (heap[2 * i + 1].freeTime == heap[index].freeTime && heap[2 * i + 1].index < heap[index].index))){
			index = 2 * i + 1;
		}
		
		if((2 * i + 2 < n) && ((heap[2 * i + 2].freeTime < heap[index].freeTime) || (heap[2 * i + 2].freeTime == heap[index].freeTime && heap[2 * i + 2].index < heap[index].index))){
			index = 2 * i + 2;
		}
		
		temp = heap[i];
		heap[i] = heap[index];
		heap[index] = temp;
		
	} while(i != index);
}

void processor(int* jobs, int m, int n){
	int i;
	node* heap = (node*) calloc(n, sizeof(node)); //defining a minheap containing each thread
	
	for(i=0;i<n;i++) heap[i].index = i; //building the minheap 
	
	for(i=0;i<m;i++){
		printf("%d %lld\n", heap[0].index, heap[0].freeTime);
		heap[0].freeTime += jobs[i];
		siftDown(heap, n, 0);
	}
}

int main(){
	int n, m, i; //n -> number of threads, m -> number of jobs
	int* jobs; //how much time needed for each job
	scanf("%d %d", &n, &m);
	
	jobs = (int*) malloc(m * sizeof(int));
	
	for(i=0;i<m;i++) scanf("%d", &jobs[i]);
	
	processor(jobs, m, n);
	
	return 0;
}
