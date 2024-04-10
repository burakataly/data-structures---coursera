#include <stdio.h>
#include <stdlib.h>

/*
Analysis: every element in the input is added to the deque and removed from deque at most once so time complexity is O(n):
O(n) for deleting and O(n) for adding. it can be thought more than O(n) because adding elements in sorted order
with linear search in every iteration but they are removed if they are smaller than the new element so there wont
be more than O(n) for total search. And there is O(m) worst case space complexity. if input is is non decreasing order it would be O(1).
*/

typedef struct n{
	int x;
	struct n* prev;
	struct n* next;
}queue;

void popBack(queue**, queue**);
int top(queue*);
void popFront(queue**, queue**);
void pushBack(queue**, queue**, int);

int main(){
	int n, m, i, j;
	int *arr;
	queue *head = 0, *tail = 0;
	
	scanf("%d", &n);
	arr = (int*) malloc(n * sizeof(int));
	for(i=0;i<n;i++) scanf("%d", arr + i);
	scanf("%d", &m);
	
	for(i=0;i<m;i++){
		pushBack(&head, &tail, arr[i]);
	}
	
	i=0, j=m;
	while(j <= n){
		printf("%d ", top(head));
		if(arr[i] == top(head)) popFront(&head, &tail);
		pushBack(&head, &tail, arr[j]);
		i++, j++;
	}
	return 0;
}

void pushBack(queue **head, queue **tail, int i){
	if(*tail == NULL){
		*tail = (queue*) malloc(sizeof(queue));
		(*tail) -> x = i;
		(*tail) -> next = NULL;
		(*tail) -> prev = NULL;
		*head = *tail;
		return;
	}
	
	//dropping smaller elements before adding to the back
	queue *temp = *tail;
	while(temp != NULL && temp -> x < i){
		temp = temp -> prev;
		popBack(head, tail);
	}
	
	if(temp == NULL){
		*tail = (queue*) malloc(sizeof(queue));
		(*tail) -> x = i;
		(*tail) -> next = NULL;
		(*tail) -> prev = NULL;
		*head = *tail;
		return;
	}
	(*tail) -> next = (queue*) malloc(sizeof(queue));
	(*tail) -> next -> prev = *tail;
	*tail = (*tail) -> next;
	(*tail) -> x = i;
	(*tail) -> next = NULL;
}

void popFront(queue** head, queue **tail){
	if(*head == *tail){
		queue *temp = *head;
		*head = *tail = NULL;
		free(temp);
	}
	else if(*head != NULL){
		queue *temp = *head;
		*head = (*head) -> next;
		(*head) -> prev = NULL;
		free(temp);
	}
}

void popBack(queue** head, queue **tail){
	if(*head == *tail){
		queue *temp = *head;
		*head = *tail = NULL;
		free(temp);
	}
	else if(*tail != NULL){
		queue *temp = *tail;
		if((*tail) -> prev != NULL){
			*tail = (*tail) -> prev;
			(*tail) -> next = NULL;
		}
		else *tail = NULL;
		free(temp);	
	}
}

int top(queue *head){
	if(head != NULL) return head -> x;
	else return -1;
}

