#include <stdio.h>
#include <stdlib.h>

/* data structure */
typedef struct node* treePointer;
typedef struct node {
    int key;
    treePointer parent;
    treePointer leftChild, rightChild;
} Node;

treePointer root = NULL;

/* insert function */
void insertion(int key) {
    treePointer newNode = (treePointer)malloc(sizeof(Node));
    newNode->key = key;
    newNode->parent = NULL;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;

    if (root == NULL) {
        root = newNode;
        printf("Insert %d\n", key);
        return;
    }

    treePointer currentNode = root;
    while (currentNode != NULL) {
        if (currentNode->key == key) {
            printf("Exist number\n");
            free(newNode);
            return;
        }

        if (key > currentNode->key) {
            if (currentNode->rightChild != NULL) {
                currentNode = currentNode->rightChild;
            }
            else {
                currentNode->rightChild = newNode;
                newNode->parent = currentNode;
                printf("Insert %d\n", key);
                return;
            }
        }
        else {
            if (currentNode->leftChild != NULL) {
                currentNode = currentNode->leftChild;
            }
            else {
                currentNode->leftChild = newNode;
                newNode->parent = currentNode;
                printf("Insert %d\n", key);
                return;
            }
        }
    }
}

/* delete function - max key deletion */
void deletion() {
    if (root == NULL) {
        printf("The heap is empty\n");
        return;
    }

    treePointer currentNode = root;

    // Find the rightmost leaf node
    while (currentNode->rightChild != NULL) {
        currentNode = currentNode->rightChild;
    }

    int key = currentNode->key;

    if (currentNode->parent != NULL) {
        treePointer parent = currentNode->parent;

        // Remove the node
        if (parent->rightChild == currentNode) {
            parent->rightChild = NULL;
        }
        else {
            parent->leftChild = NULL;
        }

        free(currentNode);
    }
    else {
        // currentNode is the root
        free(currentNode);
        root = NULL;
    }

    printf("Delete %d\n", key);
}

int main() {
    char command;
    int key;

    // while loop 
    while (1) {
        scanf("%c", &command);

        // if input is 'q', the program will be quit
        if (command == 'q') {
            break;
        }

        if (command == 'i') {
            scanf("%d", &key);
            insertion(key);
        }
        else if (command == 'd') {
            deletion();
        }

        // Clear the input buffer
        while (getchar() != '\n');
    }

    return 0;
}