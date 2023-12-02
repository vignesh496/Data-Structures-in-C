#include<stdio.h>
#include<stdlib.h>
struct Node {
    int data;
    struct Node *prev, *next;
};
struct Node *head = NULL, *f, *b, *t;
void pushFront(int data) {
    struct Node *temp;
    if (head == NULL)   {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->data = data;
        temp->prev = temp->next = NULL;
        head = f = b = temp;
    }
    else    {
        f->prev = (struct Node*)malloc(sizeof(struct Node));
        f->prev->data = data;
        f->prev->prev = NULL;
        f->prev->next = f;
        f = f->prev;
        head = f;
    }
}
void pushBack(int data) {
    struct Node *temp = head;
    if (head == NULL)   {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->data = data;
        temp->prev = temp->next = NULL;
        head = f = b = temp;
    }
    else    {
        b->next = (struct Node*)malloc(sizeof(struct Node));
        b->next->data = data;
        b->next->next = NULL;
        b->next->prev = b;
        b = b->next;
    }
}
int popFront()  {
    if (f->next == NULL)    {
        int x = f->data;
        head = NULL;
        free(f);
        f = head;
        return x;
    }
    else    {
        int x = f->data;
        head = f->next;
        head->prev = NULL;
        f->next = NULL;
        free(f);
        f = head;
        return x;
    }
}
int popBack()  {
    if (b->prev == NULL)    {
        int x = b->data;
        head = NULL;
        free(b);
        b = head;
        return x;
    }
    else    {
        int x = b->data;
        b = b->prev;
        free(b->next);
        b->next = NULL;
        return x;
    }
}
void print()    {
    t = head;
    while(t != NULL) {
        printf("%d ",t->data);
        t = t->next;
    }
}
int main()  {
    int c = 0;
    while(1)    {
        int x;
        printf("\n\n1 - Push front\n2 - Push back\n3 - Pop front\n4 - Pop back\n5 - Peek front and rear\n6 - Size of deque\n7 - Check if deque is empty/not\n");
        printf("\nEnter choice : ");
        scanf("%d",&x);
        switch (x)  {
        case 1:
            printf("\nEnter data : ");
            scanf("%d",&x);
            pushFront(x);
            print();
            break;
        case 2:
            printf("\nEnter data : ");
            scanf("%d",&x);
            pushBack(x);
            print();
            break;
        case 3:
            if (head == NULL) 
                printf("\nNo elements to be popped");
            else
                printf("\nPopped data : %d",popFront());
            print();
            break;
        case 4:
            if (head == NULL) 
                printf("\nNo elements to be popped");
            else
                printf("\nPopped data : %d",popBack());
            print();
            break;
        case 5:
            printf("\nFront peek : %d",f->data);
            printf("\nRear peek  : %d",b->data);
            break;
        case 6:
            for(struct Node *temp = head; temp != NULL; temp=temp->next, c++);
            printf("\nSize of deque : %d",c);
            print();
            break;
        case 7:
            if (head == NULL)   
                printf("\nDeque is empty");
            else
                printf("\nDeque is not empty");
            print();
            break;
        default:
            return 0;
        }
    }
}
