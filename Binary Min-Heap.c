#include<stdio.h>
#include<stdlib.h>
int top = 1, f = 1;
void heapify(int arr[], int size, int i)    {
    int s = i;
    int l = 2*i;
    int r = 2*i+1;
    if (l<=size && arr[s] > arr[l]) {
        s = l;
    }
    if (r<=size && arr[s] > arr[r]) {
        s = r;
    }
    if (s != i) {
        int temp = arr[i];
        arr[i] = arr[s];
        arr[s] = temp;
        heapify(arr, size, s);
    }
}
void buildheap(int arr[], int size) {
    for (int i = size/2; i>0; i--)  
        heapify(arr, size, i);
}
int delete(int arr[], int size) {
    int n = arr[1];
    arr[1] = arr[size];
    buildheap(arr, size);
    return n;
}
void decreaseKey(int arr[], int size, int data, int key) {
    for (int i = 1; i < size; i++) {
        if (arr[i] == data) {
            f = 0;
            arr[i] -= key;
            buildheap(arr, size);
            break;
        }
    }
}
void display(int arr[], int size)   {
    printf("\nHeap : ");
    for(int i = 1; i<size; i++) 
        printf("%d ",arr[i]);
    printf("\n");
}
void insert(int arr[], int size, int data)  {
    if (top >= size)
        return;
    arr[top] = data;
    buildheap(arr, top);
    if (top < size)
        top++;
}
int main()  {
    int n, ch, key;
    printf("\nEnter size of heap : ");
    scanf("%d",&n);
    int *arr = (int*)malloc(++n * sizeof(int));
    while (1)   {
        printf("\n1 - Insert\n2 - Delete root\n3 - Delete a data\n");
        printf("\nEnter choice : ");
        scanf("%d",&ch);
        switch(ch)  {
            case 1:
                printf("\nEnter data : ");
                scanf("%d",&ch);
                insert(arr, n, ch);
                display(arr, top);
                break;
            case 2:
                printf("\nDeleted root data : %d",delete(arr, --top));
                display(arr, top);
                break;
            case 3:
                printf("\nEnter data : ");
                scanf("%d",&ch);
                printf("\nEnter key  : ");
                scanf("%d",&key);
                decreaseKey(arr, top-1, ch, key);
                if (f == 0) {
                    delete(arr, --top);
                    printf("Deleted data : %d",ch);
                }
                else 
                    printf("\nData not found");
                display(arr, top);
                break;
        }
    }
    return 0;
}
