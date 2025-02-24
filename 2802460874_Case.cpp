#include<stdio.h>
#include<stdlib.h>

struct tnode {
	int x;
	struct tnode *next;
	struct tnode *prev;
}*head, *tail, *curr;

void pushFront(int value) {
	struct tnode *node = (tnode*) malloc(sizeof(tnode));
	node->x = value;
	
	if(head==NULL) {
		node->next = NULL;
		node->prev = NULL;
		head = tail = node;
	}
	else {
		node->next = head;
		head->prev = node;
		head = node;
		head->prev = NULL;
	}
}

void pushBack(int value) {
	struct tnode *node = (tnode*) malloc(sizeof(tnode));
	node->x = value;
	
	if(head==NULL) {
		node->next = NULL;
		node->prev = NULL;
		head = tail = node;
	}
	else {
		node->prev = tail;
		tail->next = node;
		tail = node;
		tail->next = NULL;
	}
}

void pushMid(int value, int searchKey) {
	struct tnode *node = (tnode*) malloc(sizeof(tnode));
	node->x = value;
	
	if(head == NULL) {
		node->next = NULL;
		node->prev = NULL;
		head = tail = node;
	}
	else {
		struct tnode *curr = head;
		while(curr != NULL) {
			if(curr->x == searchKey) {
				if(curr == tail) {
					pushBack(value);
				}
				else {
					node->next = curr->next;
                    node->prev = curr;
                    curr->next->prev = node;
                    curr->next = node;
				}
				break;
			}
			curr = curr->next;
		}
		if(curr == NULL) {
			printf("Data %d is not found in the linked list\n", searchKey);
		}
	}
}

void deleteFront() {
	if(head==NULL) {
		printf("There is no data\n");
	}
	else {
		if(head==tail) {
			free(head);
			head = tail = NULL;
		}
		else {
			struct tnode *del = head;
			head = head->next;
			head->prev = NULL;
			free(del);
		}
	}
}

void deleteBack() {
    if(head == NULL) {
        printf("There is no data\n");
    }
    else {
        if(head == tail) {
            free(head);
            head = tail = NULL;
        }
        else {
            struct tnode *del = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(del);
        }
    }
}

void deleteMid(int key) {
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    struct tnode *curr = head;
    while(curr != NULL) {
        if(curr->x == key) {
            if(curr == head) {
                deleteFront();
            }
            else if(curr == tail) {
                deleteBack();
            }
            else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                free(curr);
            }
            return;
        }
        curr = curr->next;
    }
    printf("Data %d not found in the linked list\n", key);
}

void printList() {
	if (head==NULL) {
		printf("List empty\n");
		return;
	}
	
	struct tnode *curr = head;
	
	while(curr != NULL) {
		printf("%d ", curr->x);
		curr = curr->next;
	}
}

void reversePrint() {
	curr = tail;
	while(curr != NULL) {
		printf("%d ", curr->x);
		curr = curr->prev;
	}
}

int main() {
	printf("Linked list\n");
	pushBack(13);
	pushBack(1);
	pushBack(3);
	deleteFront();
	pushBack(99);
	printList();getchar();
	return 0;
}

