#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

/* create new node */
Node* create(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

/* insert node in binary search tree */
Node* insertNode(Node* root, int value) {
    if (root == NULL) {
        return create(value);
    }

    if (value < root->value) {
        root->left = insertNode(root->left, value);
    }
    else if (value > root->value) {
        root->right = insertNode(root->right, value);
    }

    return root;
}


/* create binary search tree from file */
Node* bst(const char* file_name) {

    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Failed to open the file: %s\n", file_name);
        return NULL;
    }

    int n;
    fscanf(file, "%d", &n);
    Node* root = NULL;

    for (int i = 0; i < n; i++) {
        int value;
        fscanf(file, "%d", &value);
        root = insertNode(root, value);
    }

    fclose(file);
    return root;
}

/* compare two node in position & value */
int compare(Node* node1, Node* node2) {
    if (node1 == NULL && node2 == NULL) {
        return 1;
    }

    if (node1 == NULL || node2 == NULL) {
        return 0;
    }

    if (node1->value != node2->value) {
        return 0;
    }

    int leftResult = compare(node1->left, node2->left);
    int rightResult = compare(node1->right, node2->right);

    return (leftResult && rightResult);
}

/* compare and check */
void checkSameNodes(const char* input_file1, const char* input_file2) {

    Node* root1 = bst(input_file1);
    Node* root2 = bst(input_file2);

    if (compare(root1, root2)) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }
}

int main() {

    const char* input_file1 = "input1.txt";
    const char* input_file2 = "input2.txt";

    checkSameNodes(input_file1, input_file2);
    return 0;
}