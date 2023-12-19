#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *left;
    struct node *right;
};

struct node * createNode(int data){
    struct node *ptr = (struct node*)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->left = NULL;
    ptr->right = NULL;
    
    return ptr;
}

void insert(struct node *ptr,int data){
    if(ptr->data< data){
        // right subtree
        if(ptr->right!= NULL){
            ptr = ptr->right;
            insert(ptr,data);
        }else{
            ptr->right = createNode(data);  
        }
    }
    else{
        //left subtree
        if(ptr->left!= NULL){
            ptr = ptr->left;
            insert(ptr,data);
        }else{
            ptr->left = createNode(data);  
        }
    }
}

void inorder(struct node *root){
    if(root!=NULL){
        inorder(root->left);
        printf("%d \t",root->data);
        inorder(root->right);
      }
      
}

void preorder(struct node *root){
    if(root!=NULL){
        printf("%d \t",root->data);
        preorder(root->left);
        preorder(root->right);
      }
      
}

void postorder(struct node *root){
    if(root!=NULL){
        postorder(root->left);
        postorder(root->right);
        printf("%d \t",root->data);
      }
      
}

int count = 0;
void internalNode(struct node *root){
    
    if(root!=NULL){
        internalNode(root->left);
        if(root->left!=NULL || root->right!=NULL){
            count++;
        }
        internalNode(root->right);
        }
}

int counth = 0;
void halfNode(struct node *root){
    
    if(root!=NULL){
        halfNode(root->left);
        if((root->left==NULL || root->right==NULL) && !(root->left==NULL && root->right==NULL)){
            counth++;
        }
        halfNode(root->right);
      }
}

int height(struct node *root){
    int left_h, right_h;
    if(root == NULL){
        return 0;
    }
    else if(root->left == NULL && root->right == NULL){
        return 0;
    }
    else{
        left_h = height(root->left);
        right_h = height(root->right);
        
        if(left_h> right_h){
            return left_h + 1;
        }
        else{
            return right_h + 1;
        } 
    }
       

}

int countLeafNode(struct node *root) {
    if (root == NULL) {
        return 0;
    } 
    else if (root->left == NULL && root->right == NULL) {
        return 1; // Node is a leaf
    } 
    else {
        return countLeafNode(root->left) + countLeafNode(root->right);
    }
}

int countNonLeafNode(struct node *root) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) {
        return 0;
    } 
    else {
        return 1 + countNonLeafNode(root->left) + countNonLeafNode(root->right);
    }
}

struct node *findMin(struct node *root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

struct node *deleteNode(struct node *root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        struct node *temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}


int main(){
    int rootN, data, n;
    printf("Enter the root node: ");
    scanf("%d", &rootN);
    struct node *root = createNode(rootN);
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    
    for(int i =0; i<n ; i++){
        scanf("%d", &data);
        insert(root,data);
    }
    
    printf("Inorder: \n");
    inorder(root);
    printf("\nPreorder: \n");
    preorder(root);
    printf("\nPostorder: \n");
    postorder(root);
    
    internalNode(root);
    printf("\nNumber of internal nodes: %d", count-1);
    
    halfNode(root);
    printf("\nNumber of half nodes: %d", counth);
    
    
    printf("\nHeight: %d", height(root));
    printf("\nNumber of Leaf Nodes: %d", countLeafNode(root));
    printf("\nNumber of Non-Leaf Nodes: %d", countNonLeafNode(root));
    return 0;
}