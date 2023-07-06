#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode* insertNode(struct TreeNode* root, int val) {
    if (root == NULL) {
        return createNode(val);
    }
    if (val < root->val) {
        root->left = insertNode(root->left, val);
    }
    else {
        root->right = insertNode(root->right, val);
    }
    return root;
}

struct TreeNode* findMaxNode(struct TreeNode* node) {
    struct TreeNode* current = node;
    while (current->right != NULL) {
        current = current->right;
    }
    return current;
}

struct TreeNode* deleteNode(struct TreeNode* root, int val) {
    if (root == NULL) {
        return root;
    }
    if (val < root->val) {
        root->left = deleteNode(root->left, val);
    }
    else if (val > root->val) {
        root->right = deleteNode(root->right, val);
    }
    else {
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        struct TreeNode* temp = findMaxNode(root->left);
        root->val = temp->val;
        root->left = deleteNode(root->left, temp->val);
    }
    return root;
}

void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->val);
        inorderTraversal(root->right);
    }
}

void preorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->val);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

struct TreeNode* constructTree(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        exit(1);
    }

    int n;
    fscanf(file, "%d", &n);
    struct TreeNode* root = NULL;

    for (int i = 0; i < n; i++) {
        int val;
        fscanf(file, "%d", &val);
        root = insertNode(root, val);
    }

    fclose(file);
    return root;
}

struct TreeNode* deleteNodes(struct TreeNode* root, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        exit(1);
    }

    int val;
    while (fscanf(file, "%d", &val) == 1 && val != 0) {
        root = deleteNode(root, val);
    }

    fclose(file);
    return root;
}

int main() {
    const char* input_file = "input.txt";
    const char* delete_file = "delete.txt";

    struct TreeNode* tree = constructTree(input_file);
    tree = deleteNodes(tree, delete_file);

    printf("inorder: ");
    inorderTraversal(tree);
    printf("\n");

    printf("preorder: ");
    preorderTraversal(tree);
    printf("\n");

    return 0;
}