#include "headers.h"

int size(const struct Stack *head) {
	
	int size = 0;
	while (head) {
		size++;
		head = head->next;
	}

	return size;
}

struct Stack * push(struct Stack *head, struct Data data) {

	struct Stack *tmp = (struct Stack *)malloc(sizeof(struct Stack));
	if (tmp == NULL)
		exit(1);

	tmp->next = head;
	tmp->threadInfo = data.threadInfo;
	tmp->index = data.number;
	head = tmp;
	
	return head;
}

struct Stack * pop(struct Stack *head) {

	struct Stack *out;

	if (!head)
		exit(0);

	out = head;
	head = head->next;

	free(out);

	return head;
}
