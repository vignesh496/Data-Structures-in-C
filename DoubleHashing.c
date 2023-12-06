#include<stdio.h>
#include<stdlib.h>
int *arr;
int tablesize;
int hash(int data) {
    return abs(data) % tablesize;
}
int hash2(int data) {
    return 7 - (abs(data)%7);
}
int isPrime(int n)  {
    int f = 0;
    for (int i = 2; i<n; i++)   {
        if (n % i == 0) {
            f = 0;
            return 0;
        }
        else    
            f = 1;
    }
    if (f == 1) 
        return 1;
}
void findNextPrime() {
    tablesize = tablesize * 2;
    for(int i = tablesize; ; i++)   {
        if (isPrime(i) == 1)    {
            tablesize = i;
            return;
        }
    }
}
void insert(int data, int probe)   {
    int index = (hash(data) + probe * hash2(data)) % tablesize;
    if (arr[index] == '\0') 
        arr[index] = data;
    else 
        insert(data, probe+1);
}
int search(int data, int probe) {
    int index = (hash(data) + probe * hash2(data)) % tablesize;
    if (arr[index] == 0)
        return 0;
    if (arr[index] == data) 
        return 1;
    else 
        return search(data, probe + 1);
}
void display()  {
    for (int i = 0; i<tablesize; i++)   {
        if (arr[i] == 0)
            printf("HashTable [%d] : NULL\n",i);
        else 
            printf("HashTable [%d] : %d\n",i,arr[i]);
    }
}
void delete(int data, int probe)    {
    int index = (hash(data) + probe * hash2(data)) % tablesize;
    if (arr[index] == 0)
        return;
    if (arr[index] == data) 
        arr[index] = 0;
    else 
        delete(data, probe+1);
}
void rehash(double load)    {
    double curr = 0.0;
    for (int i = 0; i<tablesize; i++)   {
        if (arr[i] != 0)
            curr = curr + 1.0;
    }
    curr = curr / tablesize;
    if (curr <= load)   {
        printf("\nNo rehash required. Current load factor : %.2f\n",curr);
        return;
    }
    else {
        int j = 0;
        int buffer[tablesize];
        for (int i = 0; i<tablesize; i++)   {
            if (arr[i] != '\0')
                buffer[j++] = arr[i];
            arr[i] = '\0';
        }
        findNextPrime();
        int *new = (int *)realloc(arr, tablesize * sizeof(int));
        free(arr);
        arr = new;
        for (int i = 0; i<tablesize; i++)
            arr[i] = '\0';
        for (int i = 0; i<j; i++)   {
            insert(buffer[i], 0);
        }
    }
}
int main()  {
    printf("\nEnter initial table size : ");
    scanf("%d",&tablesize);
    arr = (int *)malloc(tablesize * sizeof(int));
    int data, ch;
    while (1)   {
        printf("\n1 - Insert\n2 - Search\n3 - Delete\n");
        printf("\nEnter choice : ");
        scanf("%d",&ch);
        switch(ch)  {
            case 1:
                printf("\nEnter data : ");
                scanf("%d",&data);
                insert(data, 0);
                rehash(0.7);
                display();
                break;
            case 2:
                printf("\nEnter data : ");
                scanf("%d",&data);
                printf("\nSearch status : %d",search(data, 0));
                rehash(0.7);
                display();
                break;
            case 3:
                printf("\nEnter data : ");
                scanf("%d",&data);
                delete(data, 0);
                display();
                break;
            default:
                return 0;
        }
    }
    return 0;
}
