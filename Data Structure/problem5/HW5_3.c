#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PEOPLE 100

typedef struct Node {
    char name[20];
    struct Node* next;
} Node;

Node* people[MAX_PEOPLE];

// Create a new node
Node* createNode(const char* name) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}

// Find a person by name
Node* findPerson(const char* name) {
    int i;
    for (i = 0; i < MAX_PEOPLE; i++) {
        if (people[i] != NULL && strcmp(people[i]->name, name) == 0) {
            return people[i];
        }
    }
    return NULL;
}

// Push a person to the list
void push(const char* name) {
    if (findPerson(name) == NULL) {
        Node* newNode = createNode(name);
        int i;
        for (i = 0; i < MAX_PEOPLE; i++) {
            if (people[i] == NULL) {
                people[i] = newNode;
                return;
            }
        }
    }
    else
        printf("Already exist");
    printf("Error: Maximum number of people reached.\n");
}

// Pop a person from the list
void pop(const char* name) {
    Node* person = findPerson(name);
    if (person != NULL) {
        int i;
        for (i = 0; i < MAX_PEOPLE; i++) {
            if (people[i] == person) {
                people[i] = NULL;
                free(person);
                return;
            }
        }
    }
}

// Make two people friends
void makeFriends(const char* name1, const char* name2) {
    Node* person1 = findPerson(name1);
    Node* person2 = findPerson(name2);

    if (person1 != NULL && person2 != NULL) {
        Node* newname1 = createNode(name1);
        Node* newname2 = createNode(name2);

        newname1->next = person2->next;
        newname2->next = person1->next;

        person1->next = newname2;
        person2->next = newname1;
    }
}

// Remove friendship between two people
void removeFriendship(const char* name1, const char* name2) {
    Node* person1 = findPerson(name1);
    Node* person2 = findPerson(name2);
    if (person1 != NULL && person2 != NULL) {
        Node* prev1 = NULL;
        Node* prev2 = NULL;

        Node* current1 = person1->next;
        Node* current2 = person2->next;

        while (current1 != NULL && current2 != NULL) {
            if (strcmp(current1->name, name2) == 0) {
                if (prev1 == NULL) {
                    person1->next = current1->next;
                }
                else {
                    prev1->next = current1->next;
                }
                free(current1);
                current1 = person1->next;
            }
            else {
                prev1 = current1;
                current1 = current1->next;
            }

            if (strcmp(current2->name, name1) == 0) {
                if (prev2 == NULL) {
                    person2->next = current2->next;
                }
                else {
                    prev2->next = current2->next;
                }
                free(current2);
                current2 = person2->next;
            }
            else {
                prev2 = current2;
                current2 = current2->next;
            }
        }
    }
}

// Print the friend list of a person
void printFriendList(const char* name, FILE* outputFile) {
    Node* person = findPerson(name);
    if (person != NULL) {
        Node* current = person->next;
        while (current != NULL) {
            fprintf(outputFile, "%s ", current->name);
            current = current->next;
        }
        fprintf(outputFile, "\n");
    }
}

// Check if two people are friends
void checkFriendship(const char* name1, const char* name2, FILE* outputFile) {
    Node* person1 = findPerson(name1);
    Node* person2 = findPerson(name2);
    if (person1 != NULL && person2 != NULL) {
        Node* current = person1->next;
        while (current != NULL) {
            if (strcmp(current->name, name2) == 0) {
                fprintf(outputFile, "Yes\n");
                return;
            }
            current = current->next;
        }
    }
    fprintf(outputFile, "No\n");
}

int main() {
    FILE* inputFile = fopen("input_3.txt", "r");
    FILE* outputFile = fopen("output_3.txt", "w");
    char command[10];
    char name1[MAX_NAME_LENGTH];
    char name2[MAX_NAME_LENGTH];

    // Initialize people array
    for (int i = 0; i < MAX_PEOPLE; i++) {
        people[i] = NULL;
    }

    while (fscanf(inputFile, "%s", command) == 1) {
        if (strcmp(command, "P") == 0) {
            fscanf(inputFile, "%s", name1);
            push(name1);
        }
        else if (strcmp(command, "F") == 0) {
            fscanf(inputFile, "%s %s", name1, name2);
            makeFriends(name1, name2);
        }
        else if (strcmp(command, "U") == 0) {
            fscanf(inputFile, "%s %s", name1, name2);
            removeFriendship(name1, name2);
        }
        else if (strcmp(command, "L") == 0) {
            fscanf(inputFile, "%s", name1);
            printFriendList(name1, outputFile);
        }
        else if (strcmp(command, "Q") == 0) {
            fscanf(inputFile, "%s %s", name1, name2);
            checkFriendship(name1, name2, outputFile);
        }
        else if (strcmp(command, "X") == 0) {
            break;
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}