#include<stdio.h>
#include<stdlib.h>
int top = -1, size;
int *stack;
void push(int data) {
    stack[++top] = data;
}
int pop()  {
    return stack[top--];
}
int peek()  {
    return stack[top];
}
int main()  {
    int ch, data;
    printf("\nEnter size of stack : ");
    scanf("%d",&size);
    stack = (int *)malloc(size * sizeof(int));
    while (1)   {
        printf("\n1 - Push\n2 - Pop\n3 - Peek\n");
        printf("\nEnter choice : ");
        scanf("%d",&ch);
        switch(ch)  {
            case 1:
                printf("\nEnter data : ");
                scanf("%d",&data);
                (top == size-1)? printf("\nStack is full"): push(data);
                break;
            case 2:
                (top != -1)? printf("\nPopped data : %d",pop()): printf("\nStack is empty");
                break;
            case 3:
                (top != -1)? printf("\nPeek data : %d",peek()): printf("\nStack is empty");
                break;
        }
    }
}
