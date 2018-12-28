#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

int second_last(struct node *head);
struct node *strings_to_list(int len, char *strings[]);

// DO NOT CHANGE THIS MAIN FUNCTION

int main(int argc, char *argv[]) {
    // create linked list from command line arguments
    struct node *head = strings_to_list(argc - 1, &argv[1]);

    int result = second_last(head);
    printf("%d\n", result);

    return 0;
}


// Return value of second-last element in linked list.
// The list assumed to have at least 2 elements.

int second_last(struct node *head) {
	struct node *curr = head;
	assert(curr != NULL);
	assert(curr->next != NULL);

	int return_value = 0;
	while (curr != NULL) {
		if (curr->next->next == NULL) {
			return_value = curr->data;
			break;
		}
		curr = curr->next;
	}
    return return_value;

}


// DO NOT CHANGE THIS FUNCTION

// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    for (int i = len - 1; i >= 0; i = i - 1) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
    }
    return head;
}
