#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 10
#define MAX_COL 10
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0

/* define stack structure */
typedef struct {
    short int row;
    short int col;
    short int dir;
} element;
element stack[MAX_STACK_SIZE];


typedef struct {
    short int vert;
    short int horiz;
}offsets;
offsets move[8] = { {-1,0}, {-1,-1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} };


int top = -1;
int EXIT_ROW, EXIT_COL;
int maze[MAX_ROW][MAX_COL];
int mark[MAX_ROW][MAX_COL];

/* define function to push element to stack */
void push(element item) {
    if (top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "Stack is full\n");
        exit(EXIT_FAILURE);
    }
    stack[++top] = item;
}

/* define function to pop element from stack */
element pop() {
    if (top == -1) {
        fprintf(stderr, "Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack[top--];
}

void path() {
    int i, row, col, nextRow, nextCol, dir, found = FALSE;

    element position;
    mark[1][1] = 1;
    top = 0;
    stack[0].row = 1; stack[0].col = 1; stack[0].dir = 2;

    while (top > -1 && !found) {
        position = pop();
        row = position.row;
        col = position.col;
        dir = position.dir;
        while (dir < 8 && !found) {
            /*  move in direction dir  */
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            if (nextRow == EXIT_ROW && nextCol == EXIT_COL)
                found = TRUE;
            else  if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
                mark[nextRow][nextCol] = 1;
                position.row = row;  position.col = col;
                position.dir = ++dir;
                push(position);
                row = nextRow;  col = nextCol;  dir = 0;
            }
            else  ++dir;
        }
    }
    if (found) {
        printf("*** The path ***\n");
       
        for (i = 0; i <= top; i++)
            printf("%d %d\n", stack[i].row-1, stack[i].col-1);
        printf("%d %d\n", row-1, col-1);
        printf("%d %d\n", EXIT_ROW-1, EXIT_COL-1);
    }
    else  printf("The maze does not have a path \n");
}

int main() {
    int n, m, i, j;

    /* get maze size */
    printf("Enter maze size (n, m): ");
    scanf("%d %d", &EXIT_ROW, &EXIT_COL);

    if (EXIT_ROW < 0 || EXIT_COL < 0) {
        printf("error\n");
        exit(1);
    }

    if (EXIT_ROW + 2 > MAX_ROW || EXIT_COL + 2 > MAX_COL) {
        printf("size is too large\n");
        exit(1);
    }

    for (int i = 0; i < EXIT_ROW + 2; i++) {
        for (int j = 0; j < EXIT_COL + 2; j++) {
            maze[i][j] = 1;
        }
    }
    
    printf("*** Enter your maze in (n, m) size ***\n");
    for (int i = 1; i < EXIT_ROW + 1; i++) {
        for (int j = 1; j < EXIT_COL + 1; j++) {
            scanf("%d", &maze[i][j]);
        }
    }

    if (maze[1][1] != 0) {
        printf("The maze does not have a path \n");
        return 0;
    }

    if (maze[EXIT_ROW][EXIT_COL] != 0) {
        printf("The maze does not have a path \n");
        return 0;
    }

    for (i = 0; i < EXIT_ROW + 2; i++)
        for (j = 0; j < EXIT_COL + 2; j++)
            mark[i][j] = 0;
    
    path();

    return 0;
}