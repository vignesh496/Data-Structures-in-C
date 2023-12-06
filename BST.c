#include<stdio.h>
#include<stdlib.h>
struct Node {
  int data;
  struct Node *left, *right;
};
struct Node* insert(struct Node *root, int data) {
  struct Node *temp = NULL;
  if (root == NULL) {
    temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    root = temp;
    return root;
  }
  else if (root->data < data){
    root->right = insert(root->right, data);
  }
  else if (root->data > data) {
    root->left = insert(root->left, data);
  }
  return root;
}
int search(struct Node *root, int data)  {
  if (root == NULL)
    return 0;
  if (root->data == data)
    return 1;
  else if (root->data > data)
    return  search(root->left, data);
  else if (root->data < data)
    return  search(root->right, data);
}
void inorder(struct Node *root) {
  if (root == NULL)
    return;
  inorder(root->left);
  printf("%d",root->data);
  inorder(root->right);
}
struct Node *findMin(struct Node *root) {
  if (root->left == NULL)
    return root;
  return findMin(root->left);
}
struct Node *delete(struct Node *root, int data)  {
  if (root == NULL)
    return NULL;
  if (root->data < data)
    root->right = delete(root->right, data);
  else if (root->data > data)
    root->left = delete(root->left, data);
  else {
    struct Node *temp;
    if (root->left == NULL && root->right == NULL) {
      free(root);
      return NULL;
    }
    else if (root->left == NULL)  {
      temp = root->right;
      free(root);
      return temp;
    }
    else if (root->right == NULL) {
      temp = root->left;
      free(root);
      return temp;
    }
    else {
      temp = findMin(root->right);
      root->data = temp->data;
      root->right = delete(root->right, temp->data);
      return root;
    }
  }
  return root;
}


int main()  { 
  int data, ch;
  struct Node *root = NULL;
  while(1)  {
    printf("\nEnter choice : ");
    scanf("%d",&ch);
    switch(ch)  {
      case 1:
        printf("\nEnter data : ");
        scanf("%d",&data);
        root = insert(root, data);
        inorder(root);
        break;
      case 2:
        printf("\nEnter data : ");
        scanf("%d",&data);
        printf("\nSearch status : %d\n",search(root, data));
        inorder(root);
        break;
      case 3:
        printf("\nEnter data : ");
        scanf("%d",&data);
        if (search(root, data) == 1)  {
          root = delete(root, data);
        }
        inorder(root);
    }
  }
  return 0;
}
