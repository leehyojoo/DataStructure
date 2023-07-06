#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 32
#define MAX_COL 32
#define TRUE 1
#define FALSE 0

/* define stack structure */
typedef struct Node {
    int row;
    int col;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} DoublyLinkedList;

typedef struct {
    int vert;
    int horiz;
} offsets;

offsets move[8] = { {-1,0}, {-1,-1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} };

int EXIT_ROW = 8, EXIT_COL = 8;
int maze[MAX_ROW][MAX_COL];
int mark[MAX_ROW][MAX_COL];
DoublyLinkedList path_list;

/* initialize a new doubly linked list */
void initializeList(DoublyLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
}

/* add a new node to the end of the doubly linked list */
void addNode(DoublyLinkedList* list, int row, int col) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->row = row;
    new_node->col = col;
    new_node->prev = list->tail;
    new_node->next = NULL;
    if (list->head == NULL) {
        list->head = new_node;
    }
    else {
        list->tail->next = new_node;
    }
    list->tail = new_node;
}

/* define function to pop element from the end of doubly linked list */
Node* pop() {
    if (path_list.head == NULL) {
        fprintf(stderr, "List is empty\n");
        exit(EXIT_FAILURE);
    }
    Node* temp = path_list.tail;
    path_list.tail = temp->prev;
    if (path_list.tail == NULL) {
        path_list.head = NULL;
    }
    else {
        path_list.tail->next = NULL;
    }
    return temp;
}

void dfs(int row, int col) {
    int i, nextRow, nextCol;

    mark[row][col] = 1;
    if (row == EXIT_ROW && col == EXIT_COL) {
        addNode(&path_list, row, col);
        return;
    }

    for (i = 0; i < 8; i++) {
        // move in direction i
        nextRow = row + move[i].vert;
        nextCol = col + move[i].horiz;
        if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
            addNode(&path_list, row, col);
            dfs(nextRow, nextCol);
            if (path_list.tail->row == EXIT_ROW && path_list.tail->col == EXIT_COL) {
                return;
            }
            pop();
        }
    }
}

int main() {
    int i, j;
    FILE* fp = fopen("maze.txt", "r");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            fscanf(fp, "%d", &maze[i][j]);
        }
    }
    fclose(fp);

    // Initialize the mark and path list
    for (i = 0; i < MAX_ROW; i++) {
        for (j = 0; j < MAX_COL; j++) {
            mark[i][j] = 0;
        }
    }
    initializeList(&path_list);

    // Check if the maze has a valid path
    if (maze[1][1] != 0 || maze[EXIT_ROW][EXIT_COL] != 0) {
        printf("The maze does not have a valid path.\n");
        return 0;
    }

    // Find the path using depth-first search (DFS)
    dfs(1, 1);

    // Write the path to the file
    FILE* path_fp = fopen("path.txt", "w");
    if (path_fp == NULL) {
        printf("Failed to create path file.\n");
        return 1;
    }

    Node* current = path_list.head;
    while (current != NULL) {
        fprintf(path_fp, "%d %d\n", current->row, current->col);
        current = current->next;
    }
    fclose(path_fp);

    return 0;
}