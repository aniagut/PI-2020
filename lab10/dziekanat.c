#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char MAX_NAME_SIZE = 35;

typedef struct node {
    struct node *left, *right, *parent;
    char* number;
    char* name;
} node;

node* create_node(int val,char *name) {
    node* tmp = (node*)malloc(sizeof(node));
    tmp->name = malloc(MAX_NAME_SIZE*sizeof(char));
    tmp->number=malloc(MAX_NAME_SIZE*sizeof(char));

    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parent = NULL;
    strcpy(tmp->name, name);
    tmp->number=val;

    return tmp;
}

void delete_tree(node* root){
    if(root == NULL) return;
    delete_tree(root->left);
    delete_tree(root->right);
    free(root);
}

void insert (node* root, node* element){
    node* tmpRoot = root;
    node* prevRoot = NULL;

    // Find the father of a new node
    while(tmpRoot != NULL)
    {
        prevRoot = tmpRoot;

        if(element->number > tmpRoot->number)
            tmpRoot = tmpRoot->right;
        else
            tmpRoot = tmpRoot->left;
    }

    // Insert the new node
    if(prevRoot->number < element->number)
        prevRoot->right = element;
    else
        prevRoot->left = element;

    element->parent = prevRoot;
}

node* find (node* root, int number) {
    if(root == NULL) return NULL;
    if(root->number == number) return root;
    node *tmp = root;

    while( tmp != NULL && tmp->number != number )
    {
        if( tmp != NULL && number > tmp->number)
            tmp = tmp->right;

        if( tmp != NULL && number < tmp->number)
            tmp = tmp->left;

        if( tmp != NULL && number == tmp->number)
            return tmp;
    }
    return NULL;
}

node* minimalNode(node* root){
    if(root == NULL) return NULL;
    if(root->left == NULL) return root;
    return minimalNode(root->left);
}

node* delete(node* root, int number) {
    if(root == NULL) return root;

    if(number < root->number)
        root->left = delete(root->left, number);
    else if(number > root->number)
        root->right = delete(root->right, number);
    else
    {
        if(root->left == NULL)
        {
            node *tmp = root->right;
            free(root);
            return tmp;
        }

        else if(root->right == NULL)
        {
            node *tmp = root->left;
            free(root);
            return tmp;
        }

        node *tmp = minimalNode(root->right);
        root->number = tmp->number;
        root->name = tmp->name;

        root->right = delete(root->right,root->number);
    }

    return root;
}

int main() {
    int a, r, f;
    scanf("%d", &a);
    scanf("%d", &r);
    scanf("%d", &f);

    node* root = NULL;
    int number;
    char* name = malloc(MAX_NAME_SIZE*sizeof(char));

    if (a--> 0)
    {
        scanf("%d", &number);
        scanf("%s", name);
        root = create_node(number, name);

    }

    while (a--> 0)
    {
        scanf("%d", &number);
        scanf("%s", name);

        insert(root, create_node(number, name));
    }

    while (r--> 0)
    {
        scanf("%d", &number);
        root = delete(root, number);

    }

    while (f--> 0)
    {
        scanf("%d", &number);
        node* x = find(root, number);
        printf("%s\n", x == NULL ? "NO" : x->name);

    }

    delete_tree(root);
    free(name);
}

