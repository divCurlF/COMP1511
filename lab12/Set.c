//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>

#include "Set.h"

#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)

typedef struct _node *Node;

struct _set {
	Node top;
	Node tail;
	int num_items;
};

struct _node {
	Node next;
	item data;
};

Set newSet (void) {
	Set newset = malloc(sizeof(struct _set));
	newset->top = NULL;
	newset->tail = NULL;
	newset->num_items = 0;
	return newset;
}

void setAdd(Set set, item data) {

	Node newNode = malloc(sizeof(struct _node));
	newNode->next = NULL;
	newNode->data = data;

	if (set->num_items == 0) {
		set->top = newNode;
		set->tail = newNode;
		set->num_items++;
		return;
	}

	if (setContains(set, data) == FALSE) {
		newNode->next = set->top;
		set->top = newNode;
		set->num_items++;
	} else {
		free(newNode);
	}
}

void destroySet(Set set) {
	Node curr = set->top;
	if (curr == NULL) {
		free(set);
		return;
	}
	Node temp;
	while (curr != NULL) {
		temp = curr->next;
		free(curr);
		curr = temp;
	}
	free(set);
}

int setSize(Set set) {
	return set->num_items;
}

Set setUnion(Set a, Set b) {
	Set result = newSet();
	Node curr = a->top;
	while (curr != NULL) {
		setAdd(result, curr->data);
		curr = curr->next;
	}
	curr = b->top;
	while (curr != NULL) {
		if (!setContains(result, curr->data)) {
			setAdd(result, curr->data);
		}
		curr = curr->next;
	}
	return result;
}

Set setIntersection (Set a, Set b) {
	Set result = newSet();
	Node curr = a->top;
	while (curr != NULL) {
		if (setContains(b, curr->data)) {
			setAdd(result, curr->data);
		}
		curr = curr->next;
	}
	return result;
}

bool setSubset(Set a, Set b) {
	Node curr = a->top;
	while (curr != NULL) {
		if (!setContains(b, curr->data)) {
			return FALSE;
		}
		curr = curr->next;
	}
	return TRUE;
}

bool setEqual(Set a, Set b) {
	return setSubset(a, b) && setSubset(b, a);
}

bool setContains(Set set, item data) {
	Node curr = set->top;
	while (curr != NULL) {
		if (curr->data == data) {
			return TRUE;
		}
		curr = curr->next;
	}
	return FALSE;
}

void setRemove(Set set, item data) {
	Node curr = set->top;
	Node temp;

	if (curr->data == data) {
		temp = curr->next;
		set->top = temp;
		free(curr);
		set->num_items--;
		return;
	}

	while (curr->next != NULL) {
		if (curr->next->data == data) {
			temp = curr->next;
			curr->next = temp->next;
			free(temp);
			set->num_items--;
			break;
		}
		curr = curr->next;
	}
}

