//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0

#define FALSE 0
#define TRUE (!FALSE)

struct node {
	struct node *next;
	int 	data;
};

struct word_list {
	struct word_list *next;
	char 	*word;
};

struct node *list_append(struct node *list1, struct node *list2);
int non_decreasing(int n, int a[n]);
void printf_fn(int flag);

struct word_list *strings_to_list(int len, char *strings[]);
void print_list(struct word_list *head);
void free_list(struct word_list *head);
int find_index(int x, int n, int a[n]);

int main(void) {
	char s[] = "Hello World!";
	char *cp = s;
	char *cp2 = &s[8];
	printf("%s\n", cp);
	printf("%c\n", *cp);
	printf("%c\n", cp[6]);
	printf("%s\n",cp2);
	printf("%c\n",*cp2);


	int size = 5;
	int test[] = {1, 2, 3, 4, 5};
	printf_fn(non_decreasing(size, test));
	int neg[] = {1, -1, 2, 3, 4};
	printf_fn(non_decreasing(size, neg));
	int end_test[] = {1, 2, 3, 4, 1};
	printf_fn(non_decreasing(size, end_test));

    	char *powers[] = {"2", "4", "8", "16"};
    	char *yo_mama[] = {"Baby Shark", "DO DO DO DO DO DO", "Baby Shark", "DO DOD OD OD OD OD", "BABY HARK ODODODODOODO", "MUMMY sharK"};
    	struct word_list *head = strings_to_list(6, yo_mama);
	print_list(head);
	free_list(head);
    	head = strings_to_list(4, powers);
	print_list(head);
	free_list(head);

	return EXIT_SUCCESS;
}

void free_list(struct word_list *head) {
	struct word_list *curr = head;
	while (curr != NULL) {
		struct word_list *temp = curr->next;
		free(curr->word);
		free(curr);
		curr = temp;
	}
}

void print_list(struct word_list *head) {
	struct word_list *curr = head;
	printf("[%s", curr->word);
	while (curr->next != NULL) {
		printf(", %s", curr->next->word);
		curr = curr->next;
	}
	printf("]\n");
}

void printf_fn(int flag) {
	if (flag) {printf("TRUE\n");}
	else {printf("FALSE\n");}

}


struct node *list_append(struct node *list1, struct node *list2) {
	struct node *curr = list1;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = list2;
	return list1;
}

int non_decreasing(int n, int a[n]) {
	for (int i = 0; i < n-1; i++) {
		if (a[i] > a[i+1]) {
			return 0;
		}
	}
	return 1;
}

struct word_list *strings_to_list(int len, char *strings[]) {

	if (len == 0) {
		return NULL;
	}
	struct word_list *prev = NULL;
	struct word_list *first = NULL;

	int i = 0;
	while (i < len) {
		struct word_list *new_node = malloc( sizeof (struct word_list));
		if (i == 0) {
			first = new_node;
			prev = new_node;
			new_node->word = malloc(sizeof(char) * strlen(strings[i]));
			strcpy(new_node->word, strings[i]);
		} else {
			prev->next = new_node;
			new_node->word = malloc(sizeof(char) * strlen(strings[i]));
			strcpy(new_node->word, strings[i]);
			prev = new_node;
		}
		i++;
	}
	prev->next = NULL;
	return first;
}


int find_index(int x, int n, int a[n]) {
	for (int i = 0; i < n; i++) {
		if (a[i] == x) {
			return i;
		}
	}
	return -1;
}

int improved_find_index(int x, int n, int a[n], int lo, int hi) {
	int mid = (lo+hi) / 2;
	if (lo > hi) {
		return -1;
	} else {
		if (x == a[mid]) {
			return 1;
		} else if ( x < a[mid]) {
			return improved_find_index(x, n, a, lo, mid);
		} else {
			return improved_find_index(x, n, a, mid+1, hi);
		}
	}
}




