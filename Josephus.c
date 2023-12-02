#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Node {
    char data[20];
    struct Node *next;
};
struct Node *head = NULL;
void createNode(int n)  {
    struct Node *temp, *h;
    for(int i = 0; i<n; i++)    {
        if (head == NULL)   {
            temp = (struct Node *)malloc(sizeof(struct Node));
            head = temp;
        }
        else {
            temp->next = (struct Node*)malloc(sizeof(struct Node));
            temp = temp->next;
        }
        printf("\nEnter character %d : ",i+1);
        scanf("%s",&temp->data);
    }
    temp->next = NULL;
}
struct Node* reverseNode()  {
    struct Node *prev = NULL, *next = NULL;
    struct Node *curr = head;
    while(curr != NULL)    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
    return head;
}
void survivor(int k)    {   // k - skip value
    struct Node *temp = head;
    if (k == 1) {
        while(temp->next != NULL)   {
            temp = temp->next;
        }        
    }
    else if (k > 1){
        while(strcmp(temp->next->data,temp->data)!=0)   {
            struct Node *prev = NULL, *curr = temp, *nxt = NULL;
            for(int i = 0; i<k-1; i++)    {
                prev = curr;
                curr = curr->next;
                nxt = curr->next;
            }
            printf("Killed : %s\n",curr->data);
            free(curr);
            prev->next = nxt;
            temp = nxt;
        }
    }
    printf("Survivor : %s",temp->data);
}
void createLoop(struct Node *head)   {
    struct Node *temp = head;
    while(temp->next != NULL) 
        temp = temp->next;
    temp->next = head;
}
int main()  {
    int n, k;
    printf("\nEnter no. of players : ");
    scanf("%d",&n);
    re:
    printf("\nEnter skip value     : ");
    scanf("%d",&k);
    if (k == 0)    {
        printf("\nInvalid skip value, try again.");
        goto re;
    }
    createNode(n);
    if (k > 1)  {
        createLoop(head);
        survivor(k);
    }
    else if (k == 1)    
        survivor(k);
    else if (k < 0) {
        k = abs(k);
        struct Node *t = reverseNode();
        createLoop(t);
        survivor(k);
    }
}
