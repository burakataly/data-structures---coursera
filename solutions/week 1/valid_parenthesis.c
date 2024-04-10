#include <stdio.h>
#include <stdlib.h>

typedef struct s{
    char x;
    int i;
    struct s* next;
}stack;

void push(stack**, char, int);
char top(stack*);
void pop(stack**);
void isValid(char*);

int main(){
	char s[100001];
	scanf("%s", s);
	isValid(s);
	return 0;
}

void isValid(char * s){
    int i=0;
    stack *head = NULL;
    while(s[i]){
    	if(s[i] == '(' || s[i] == '[' || s[i] == '{' || s[i] == ')' || s[i] == ']' || s[i] == '}'){
    		if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
            	push(&head, s[i], i+1);
	        }
	        else if(head != NULL && ((s[i] == ')' && top(head) == '(') || (s[i] == ']' && top(head) == '[') || (s[i] == '}' && top(head) == '{'))){
	            pop(&head);
	        }
			else{
				printf("%d", i+1);
				return;
			}
		}
        i++;
    }
    if(head == NULL){
    	printf("%s", "Success");
	}
    else printf("%d", head -> i);
}

void push(stack **head, char c, int i){	
	stack *temp = (stack*) malloc(sizeof(stack));
	temp -> x = c;
	temp -> i = i;
	temp -> next = *head;
	*head = temp;
}

char top(stack *head){
    return head -> x;
}

void pop(stack **head){
	if(*head != NULL){
		stack *temp = *head;
		*head = (*head) -> next;
		free(temp);	
	}
}
