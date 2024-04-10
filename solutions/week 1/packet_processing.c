#include <stdio.h>
#include <stdlib.h>

typedef struct job{
	int arrival;
	int needed;	
}JOB;

typedef struct n{
	int index;
	struct n* next;
}node;

typedef struct queue{
	int size;
	node* head;
    node* tail;
}QUEUE;

void push(QUEUE* queue, int index){
	node *temp = (node*) malloc(sizeof(node));
	temp -> index = index;
	temp -> next = NULL;
	if(queue -> head == NULL){
		queue -> tail = queue -> head = temp;
	}
	else{
		queue -> tail -> next = temp;
		queue -> tail = temp;
	}
	(queue -> size)++;
}

void pop(QUEUE* queue){
	if(queue -> head != NULL){
        node *temp = queue -> head;
        queue -> head = queue -> head -> next;
        if(queue -> head == NULL) queue -> tail = NULL;
        free(temp);
        (queue -> size)--;
    }
}

int max(int a, int b){
	return (a > b) ? a : b;
}

void processor(int s, int n, JOB* jobs){
	int i = 0, beginTime = 0, temp;
	int* beginTimes = (int*) calloc(n, sizeof(int));
	QUEUE* queue = (QUEUE*) calloc(1, sizeof(QUEUE));
	
	while(i < s && i < n) push(queue, i++);
	while(queue -> head != NULL){
		
		temp = max(beginTime, jobs[queue -> head -> index].arrival);
		beginTimes[queue -> head -> index] = temp;
		beginTime = temp + jobs[queue -> head -> index].needed;
		pop(queue);
		
		while(queue -> size < s && i < n){
			if(beginTime > jobs[i].arrival) beginTimes[i++] = -1;
			else push(queue, i++);
		}
	}
	
	for(i=0;i<n;i++) printf("%d\n", beginTimes[i]);
}

int main(){
	int s, n, i;
	JOB* jobs;
	scanf("%d %d", &s, &n);
	
	jobs = (JOB*) malloc(n * sizeof(JOB));
	for(i=0;i<n;i++) scanf("%d %d", &jobs[i].arrival, &jobs[i].needed);
	processor(s, n, jobs);
	
	return 0;
}
