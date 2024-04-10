#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct n{
	int x;
	struct n* next;
}stack;

void push(stack**, int);
int top(stack*);
void pop(stack**);

int main(){
	int q, i, v, n, k;
	char temp[20];
	stack *head = 0;
	stack *maxStack = 0;
	
	scanf("%d", &q);
	for(i=0;i<q;i++){
		scanf(" %[^\n]s", temp);
		if(temp[0] == 'm') printf("%d\n", top(maxStack));
		else if(temp[1] == 'o'){
			if(top(head) == top(maxStack)) pop(&maxStack);
			pop(&head);
		}
		else{
			n = strlen(temp);
			v = 0, k = 1;
			while(temp[--n] != ' '){
				v += (temp[n] - '0') * k;
				k *= 10;
			}
			push(&head, v);
			if(v >= top(maxStack)) push(&maxStack, v);
		}
	}
	return 0;
}

void push(stack **head, int i){
	stack *temp = (stack*) malloc(sizeof(stack));
	temp -> x = i;
	temp -> next = *head;
	*head = temp;
}

int top(stack *head){
	if(head != NULL) return head -> x;
	else return -1;
}

void pop(stack **head){
	if(*head != NULL){
		stack *temp = *head;
		*head = (*head) -> next;
		free(temp);
	}
}
