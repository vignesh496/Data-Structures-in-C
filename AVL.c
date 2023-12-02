#include<stdio.h>
#include<stdlib.h>
struct Node {
    int data, height;
    struct Node *left, *right;
};
int root1(struct Node *root)	{
	return (root == NULL)?-1:root->data;	
}
int height(struct Node *root)   {
    return (root == NULL)? -1 : root->height;
}
int search(struct Node *root, int data)    {
    if (root == NULL)
        return 0;
    if (root->data == data) 
        return 1;
    return (root->data < data)? search(root->right, data): search(root->left, data);
}
int max(int a, int b) {
    return (a > b) ? a : b;
}
struct Node *single_left_rotation(struct Node *root)    {
    struct Node *temp;
    temp = root->left;
    root->left = temp->right;
    temp->right = root;
    root->height = max(height(root->left), height(root->right))+1;
    temp->height = max(height(temp->left), root->height)+1;
    return temp;
}
struct Node *double_left_rotation(struct Node *root)    {
    root->left = single_left_rotation(root->left);
    return (single_left_rotation(root));
}
struct Node *single_right_rotation(struct Node *root) {
    struct Node *temp;
    temp = root->right;
    root->right = temp->left;
    temp->left = root;
    root->height = 1 + max(height(root->left), height(root->right));
    temp->height = 1 + max(height(temp->right), root->height);
    return temp;
}
struct Node *double_right_rotation(struct Node *root) {
    root->right = single_left_rotation(root->right);
    return single_right_rotation(root);
}
struct Node *insert(struct Node *root, int data) {
    if (root == NULL) {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->height = 0;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (data < root->data) 
        root->left = insert(root->left, data);
    else if (data > root->data) 
        root->right = insert(root->right, data);
    else 
        return root;
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = height(root->left) - height(root->right);
    if (balance > 1) {
        if (data < root->left->data) 
            root = single_left_rotation(root);
        else {
            root->left = single_right_rotation(root->left);
            root = single_left_rotation(root);
        }
    }
    if (balance < -1) {
        if (data > root->right->data) 
            root = single_right_rotation(root);
        else {
            root->right = single_left_rotation(root->right);
            root = single_right_rotation(root);
        }
    }
    return root;
}
struct Node *find_min(struct Node *node) {
    while (node->left != NULL) 
        node = node->left;
    return node;
}
struct Node *delete(struct Node *root, int data) {
    if (root == NULL) 
        return root;
    if (data < root->data) 
        root->left = delete(root->left, data);
    else if (data > root->data) 
        root->right = delete(root->right, data);
    else {
        if (root->left == NULL || root->right == NULL) {
            struct Node *temp = (root->left) ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } 
            else 
                *root = *temp; 
            free(temp);
        } 
        else {
            struct Node *temp = find_min(root->right);
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
        }
    }
    if (root == NULL) 
        return root;
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = height(root->left) - height(root->right);
    if (balance > 1) {
        if (height(root->left->left) >= height(root->left->right)) 
            root =  single_left_rotation(root);
        else {
            root->left = single_right_rotation(root->left);
            root = single_left_rotation(root);
        }
    }
    if (balance < -1) {
        if (height(root->right->right) >= height(root->right->left)) 
        	root = single_right_rotation(root);
        else {
            root->right = single_left_rotation(root->right);
            root = single_right_rotation(root);
        }
    }
    return root;
}
void inorder(struct Node *root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
}
int main()  {
    struct Node *root = NULL;
    while(1)    {
        int ch;
        printf("\n1 - Insert\n2 - Search\n3 - Delete\n");
        printf("\nEnter choice : ");
        scanf("%d",&ch);
        switch(ch)  {
            case 1:
                printf("\nEnter data : ");
                scanf("%d",&ch);
                (search(root, ch) == 0)? printf("\nData %d inserted\n",ch): printf("\nData already exits in AVL Tree\n");
                root = insert(root, ch);
				printf("\nRoot : %d\n",root1(root));
                inorder(root);
                printf("\n");
                break;
            case 2:
                printf("\nEnter data : ");
                scanf("%d",&ch);
                (search(root, ch) == 1)? printf("\nData exist in AVL tree\n"): printf("\nData not found\n");
				printf("\nRoot : %d\n",root1(root));
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("\nEnter data to be deleted : ");
                scanf("%d",&ch);
                if (search(root, ch) == 1)    {
                    root = delete(root, ch);
                    printf("\nData %d deleted\n", ch);
					printf("\nRoot : %d\n",root1(root));
                    inorder(root);
                    printf("\n");
                }
                else 
                    printf("\nData not found\n");
                break;
            default:
                printf("\nExit successfully\n");
                return 0;      
        }
    }
}
