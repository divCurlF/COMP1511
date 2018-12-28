//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)

struct node {
	struct node *next;
	int data;
};

struct list {
	struct node 	*head;
	int 		size;
};

typedef struct node *Node;
typedef struct list *List;
void insert_node(List list, int data);
int pop(List list);
void print_list(List list);
void reverse_list(List head);

List create_list(int data);

int main(void) {
	List l = create_list(1);
	print_list(l);
	insert_node(l, 2);
	print_list(l);
	insert_node(l, 5);
	print_list(l);
	insert_node(l, 6);
	print_list(l);
	insert_node(l, 2);
	print_list(l);
	pop(l);
	print_list(l);
	reverse_list(l);
	print_list(l);
	return EXIT_SUCCESS;
}

void print_list(List list) {
	Node curr = list->head;
	printf("[%d", curr->data);
	while (curr->next != NULL) {
		printf(", %d", curr->next->data);
		curr = curr->next;
	}
	printf("]\n");
}

void reverse_list(List list) {
	Node curr = list->head;
	Node next = NULL;
	Node prev = NULL;

	if (curr == NULL) {
		return ;
	}
	while (curr->next != NULL) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	curr->next = prev;
	list->head = curr;
}

List create_list(int data) {
	Node head = malloc(sizeof(head));
	if (head == NULL) {
		fprintf(stderr, "Out of memory\n");
		exit(1);
	}
	head->next = NULL;
	head->data = data;

	List list = malloc(sizeof(list));
	if (list == NULL) {
		fprintf(stderr, "Out of memory\n");
		exit(1);
	}
	list->head = head;
	list->size = 1;
	return list;
}

void insert_node(List list, int data) {
	if (list->head == NULL) {
		fprintf(stderr, "Not a valid list\n");
		exit(1);
	}
	Node n = malloc(sizeof(n));
	n->next = NULL;
	n->data = data;
	if (n == NULL) {
		fprintf(stderr, "Memory error\n");
		exit(1);
	}
	if (list->head->next == NULL) {
		list->head->next = n;
		list->size++;
	} else {
		Node temp = list->head->next;
		list->head->next = n;
		n->next = temp;
		list->size++;
	}
}

int pop(List list) {
	if (list->head == NULL) {
		fprintf(stderr, "Invalid List\n");
		exit(1);
	}

	Node curr = list->head;
	while (curr->next != NULL) {
		if (curr->next->next == NULL) {
			int value = curr->next->data;
			free(curr->next);
			curr->next = NULL;
			return value;
		}
		curr = curr->next;
	}
	return 0;
}

