#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node of the singly linked list
typedef struct list_node {
	int data;
	struct list_node* link;
}list_node;


// Function to add a node to the end of the linked list
list_node* add_node(list_node* head, int data) {

    // Allocate memory for the new node
    list_node* new_node = (list_node*)malloc(sizeof(list_node));
    new_node->data = data;
    new_node->link = NULL;

    // If the linked list is empty, set the new node as the head
    if (head == NULL) {
        head = new_node;
    }
    
    else {
        // Traverse the linked list to find the last node
        list_node* curr_node = head;
        while (curr_node->link != NULL) {
            curr_node = curr_node->link;
        }
        // Set the new node as the last node
        curr_node->link = new_node;
    }

    return head;
}


// Function to sort the linked list in ascending order
void sort_list(list_node* head) {

    // If the given linked list is empty, simply return without doing anything
    if (head == NULL) {
        return;
    }

    // Loop through the linked list twice, comparing each pair of adjacent nodes and swapping them if they are in the wrong order
    list_node* i, * j;
    int temp;
    for (i = head; i != NULL; i = i->link) {
        for (j = i->link; j != NULL; j = j->link) {
            if (i->data > j->data) {
                // Swap the data values of the nodes, to sort the linked list in ascending order
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}


// Free the memory allocated for each node in the linked list
void free_list(list_node* head) {

    // Initialize a pointer to the current node as the head node
    list_node* curr_node = head;

    // Continue until the current node becomes NULL
    while (curr_node != NULL) {
        // Create a temporary pointer to the current node
        list_node* temp_node = curr_node;

        // Move the current node pointer to the next node
        curr_node = curr_node->link;

        // Free the memory allocated to the temporary node pointer
        free(temp_node);
    }
}


// The main function reads integers from a file and stores them in a singly linked list
// The linked list is then sorted in ascending order and written to an output file
int main() {
    int n, i, data;
    list_node* head = NULL;
    FILE* in_file, * out_file;

    // Read input from the input file
    in_file = fopen("input_1.txt", "r");
    out_file = fopen("output_1.txt", "w");

    fscanf(in_file, "%d", &n);

    for (i = 0; i < n; i++) {
        fscanf(in_file, "%d", &data);
        head = add_node(head, data);
    }

    // Sort the linked list in ascending order
    sort_list(head);

    // Write the sorted linked list to the output file
    list_node* curr_node = head;
    while (curr_node != NULL) {
        fprintf(out_file, "%d ", curr_node->data);
        curr_node = curr_node->link;
    }

    // Free the memory allocated for the linked list
    fclose(in_file);
    fclose(out_file);
    free_list(head);

    return 0;
}