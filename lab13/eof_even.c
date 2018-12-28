//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)

struct List {
	struct node * head;
	struct node * tail;
};

struct node {
	struct node *next;
	int value;
};

struct node *createNode(int value);
struct List *createList(void);
void appendList(struct List *list, int value);
void deleteList(struct List *list);
void printList(struct List *list);

int main(void) {
	int num;
	struct List *list = createList();
	while (scanf("%d", &num) != EOF) {
		if (num % 2 == 0) {
			appendList(list, num);
		}
	}
	printList(list);
	deleteList(list);
	return EXIT_SUCCESS;
}

void printList(struct List *list) {
	struct node *curr = list->head;
	while (curr != NULL) {
		printf("%d", curr->value);
		if (curr->next != NULL) {
			printf(" ");
		}
		curr = curr->next;
	}
	printf("\n");
}

struct node * createNode(int value) {
	struct node *new_node = malloc(sizeof(struct node));
	new_node->next = NULL;
	new_node->value = value;
	return new_node;
}

struct List * createList() {
	struct List *list = malloc(sizeof(struct List));
	list->head = NULL;
	list->tail = NULL;
	return list;
}

void appendList(struct List *list, int value) {
	struct node *new_node = createNode(value);
	if (list->head == NULL) {
		list->head = new_node;
		list->tail = new_node;
	} else {
		list->tail->next = new_node;
		list->tail = new_node;
	}
}

void deleteList(struct List *list) {
	struct node *head = list->head;
	if (head == NULL) {
		return;
	}

	struct node *curr = head;
	struct node *temp;
	while (curr != NULL) {
		temp = curr->next;
		free(curr);
		curr = temp;
	}
	free(list);
}
