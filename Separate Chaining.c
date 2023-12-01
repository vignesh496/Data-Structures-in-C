#include<stdio.h>
#include<stdlib.h>
struct Node {
    int data;
    int len;
    struct Node *next;
};
int isPrime(int n)    {
    int f = 0;
    for(int i = 2; i<n/2+1; i++)    {
        if (n%i == 0)   {
            f = 1;
            return 0;
        }
    }
    return (f == 0)? 1:0;
}
int findPrime(int n)    {
    if (isPrime(n))
        return n;
    return findPrime(n-1);
}
int hash(int data, int tablesize)  {
    return abs(data) % tablesize;
}
struct Node* insertNode(struct Node *head, int data)    {
    struct Node *temp = NULL;
    if (head == NULL)   {
        temp = (struct Node *)malloc(sizeof(struct Node));
        head = temp;
    }
    else {
        temp->next = (struct Node *)malloc(sizeof(struct Node));
        temp = temp->next;
    }
    temp->data = data;
    temp->len = 1;
    temp->next = NULL;
    return head;
}
void insert(struct Node *arr[], int tablesize, int data)    {
    int index = hash(data, tablesize);
    struct Node *temp = arr[index];
    if (temp == NULL)  
        arr[index] = insertNode(temp, data);
    else {
        while (temp->next != NULL)  
            temp = temp->next;
        temp->next = insertNode(temp->next, data);
    }
}
void display(struct Node *arr[], int tablesize, int index)  {
    if (index>=tablesize)
        return;
    printf("HashTable[%d] : ",index);
    if (arr[index] != NULL) {
        printf("%d ", arr[index]->data);
        struct Node *temp = arr[index]->next;
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
    }
    printf("\n");
    display(arr, tablesize, index+1);
}
int search(struct Node *arr[], int tablesize, int data)    {
    int index = hash(data, tablesize);
    struct Node *temp = arr[index];
    while (temp != NULL)    {
        if (temp->data == data) 
            return index;
        temp = temp->next;
    }
    return -1;
}
int delete(struct Node *arr[], int tablesize, int data) {
    if (search(arr, tablesize, data) != -1) {
        int index = hash(data, tablesize); 
        struct Node *temp = arr[index];
        struct Node *prev = NULL;
        while (temp != NULL) {
            if (temp->data == data) {
                (prev == NULL)? (arr[index] = temp->next): (prev->next = temp->next);
                int n = temp->data;
                free(temp);
                return n; 
            }
            prev = temp;
            temp = temp->next;
        }
    }
    return -1;
}
void rehash(struct Node ***arr, int *tablesize, double loadFactor) {
    double currentLoadFactor = 0.0;
    for (int i = 0; i < *tablesize; i++) {
        int chainLength = 0;
        struct Node *temp = (*arr)[i];
        while (temp != NULL) {
            chainLength++;
            temp = temp->next;
        }
        currentLoadFactor += (double)chainLength / *tablesize;
    }
    if (currentLoadFactor <= loadFactor) {
        printf("No rehashing required. Current load factor: %.2f\n", currentLoadFactor);
        return;
    }
    int newTableSize = findPrime(*tablesize * 2);
    struct Node **new_arr = (struct Node **)malloc(newTableSize * sizeof(struct Node *));
    for (int j = 0; j < *tablesize; j++) {
        struct Node *temp = (*arr)[j];
        while (temp != NULL) {
            insert(new_arr, newTableSize, temp->data);
            temp = temp->next;
        }
    }
    free(*arr);
    *arr = new_arr;
    *tablesize = newTableSize;
    printf("Rehashing completed. New table size: %d\n", newTableSize);
}
int main()  {
    int tablesize;
    printf("\nEnter size of hash table (initial) : ");
    scanf("%d",&tablesize);
    struct Node **arr = (struct Node **)malloc(tablesize * sizeof(struct Node*));
    while(1)    {
        int ch;
        printf("\n1 - Insert\n2 - Search\n3 - Delete\n4 - Rehash\n");
        printf("\nEnter choice : ");
        scanf("%d",&ch);
        switch(ch)  {
            case 1:
                printf("\nEnter data : ");
                scanf("%d",&ch);
                insert(arr, tablesize, ch);
                display(arr, tablesize, 0);
                break;
            case 2:
                printf("\nEnter data : ");
                scanf("%d",&ch);
                int x = search(arr, tablesize, ch);
                if (x != -1)    {
                    printf("\nData found at index %d\n",x);
                    display(arr, tablesize, 0);
                }
                else {
                    printf("\nData not found\n");
                }
                break;
            case 3:
                printf("\nEnter data : ");
                scanf("%d",&ch);
                if (delete(arr, tablesize, ch) == -1)   {
                    printf("\nData not found\n");
                }
                else {
                    printf("Data deleted\n");
                    display(arr, tablesize, 0);
                }
                break;
            case 4:
                rehash(&arr, &tablesize, 0.7);
                break;
            default:
                printf("Exit successfully\n");
                return 0;
        }
    }
    return 0;
}















