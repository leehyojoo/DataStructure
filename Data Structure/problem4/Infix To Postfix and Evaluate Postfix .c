#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 20

typedef struct {
    int top;
    char arr[MAX_SIZE];
} Stack;

void initStack(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

char peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Error: stack is empty.\n");
        exit(1);
    }
    return stack->arr[stack->top];
}

void push(Stack* stack, char c) {
    if (isFull(stack)) {
        printf("Error: Stack is full\n");
        exit(1);
    }
    stack->top++;
    stack->arr[stack->top] = c;
}

char pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Error: Stack is empty\n");
        exit(1);
    }
    char c = stack->arr[stack->top];
    stack->top--;
    return c;
}

int getPriority(char op) {
    switch (op) {
    case '#':
        return 3;
    case '*':
    case '/':
    case '%':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0; 
    }
}

// infix -> postfix
void infixToPostfix(char infix[], char postfix[]) {
    Stack stack;
    initStack(&stack);
    int i, j;
    char c;

    for (i = 0, j = 0; infix[i] != '\0'; i++) {
        c = infix[i];
        if (isdigit(c)) { 
            postfix[j] = c;
            j++;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') { // 연산자일 경우
            if (i == 0 || infix[i - 1] == '(') { // unary operator일 경우
                if (c == '-') {
                    c = '#';
                }
                else if (c == '+') {
                    continue; 
                }
            }
            while (!isEmpty(&stack) && getPriority(peek(&stack)) >= getPriority(c)) {
                postfix[j] = pop(&stack);
                j++;
            }
            push(&stack, c);
        }
        else if (c == '(') { 
            push(&stack, c);
        }
        else if (c == ')') { 
            while (peek(&stack) != '(') {
                postfix[j] = pop(&stack);
                j++;
            }
            pop(&stack); 
        }
    }
    while (!isEmpty(&stack)) {
        postfix[j] = pop(&stack);
        j++;
    }
    postfix[j] = '\0'; 
}

// postfix 
int evaluatePostfix(char postfix[]) {
    Stack stack;
    initStack(&stack);
    int i, operand1, operand2, result;
    char c;
    for (i = 0; postfix[i] != '\0'; i++) {
        c = postfix[i];
        if (isdigit(c)) { 
            push(&stack, c - '0'); 
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') { 
            operand2 = pop(&stack);
            operand1 = pop(&stack);
            switch (c) {
            case '+': result = operand1 + operand2; break;
            case '-': result = operand1 - operand2; break;
            case '*': result = operand1 * operand2; break;
            case '/': result = operand1 / operand2; break;
            case '%': result = operand1 % operand2; break;
            }
            push(&stack, result);
        }
        else if (c == '#') { // unary operator
            operand1 = pop(&stack);
            push(&stack, -operand1); 
        }
    }
    return pop(&stack); 
}


int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];
    printf("Input : ");
    fgets(infix, MAX_SIZE, stdin);
    infixToPostfix(infix, postfix);
    printf("Postfix : ");
    printf("%s\n", postfix);
    printf("Result : ");
    printf("%d\n", evaluatePostfix(postfix));
    return 0;
}
        