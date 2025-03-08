#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 10

typedef struct Node {
    int key;
    struct Node* next;
} Node;

int hash_mid_square(int key) {
    int squared = key * key;
    int mid = (squared / 10) % TABLE_SIZE;
    return mid % TABLE_SIZE;
}

int hash_division(int key) {
    return key % TABLE_SIZE;
}

int hash_folding(int key) {
    int sum = 0;
    while (key > 0) {
        sum += key % 100;
        key /= 100;
    }
    return sum % TABLE_SIZE;
}

int hash_digit_extraction(int key) {
    return (key / 10) % TABLE_SIZE;
}

int hash_rotating(int key) {
    int last_digit = key % 10;
    key = (key / 10) + (last_digit * 10000);
    return key % TABLE_SIZE;
}

void linear_probing(int table[], int key) {
    int index = hash_division(key);
    while (table[index] != -1) {
        index = (index + 1) % TABLE_SIZE;
    }
    table[index] = key;
}

void chaining(Node* table[], int index, int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = table[index];
    table[index] = newNode;
}


void display_table(int table[], Node* chainTable[]) {
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        if (table[i] != -1) {
            printf("%d", table[i]);
        }
        Node* temp = chainTable[i];
        while (temp) {
            printf(" -> %d", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int table[TABLE_SIZE];
    Node* chainTable[TABLE_SIZE] = {NULL};
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = -1;
    }

    int choice, key, collision_method;
    do {
        printf("\nMenu:\n");
        printf("1. Mid-Square Hashing\n");
        printf("2. Division Hashing\n");
        printf("3. Folding Hashing\n");
        printf("4. Digit Extraction Hashing\n");
        printf("5. Rotating Hashing\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        if (choice >= 1 && choice <= 5) {
            printf("Enter key: ");
            scanf("%d", &key);
            
            int index;
            switch (choice) {
                case 1: index = hash_mid_square(key); break;
                case 2: index = hash_division(key); break;
                case 3: index = hash_folding(key); break;
                case 4: index = hash_digit_extraction(key); break;
                case 5: index = hash_rotating(key); break;
            }
            
            if (table[index] == -1) {
                table[index] = key;
            } else {
            	puts("");
                printf("Collision occurred! Choose a resolution method:\n");
                printf("1. Linear Probing\n");
                printf("2. Chaining\n");
                printf("Enter choice: ");
                scanf("%d", &collision_method);
                
                if (collision_method == 1) {
                    linear_probing(table, key);
                } else if (collision_method == 2) {
                    chaining(chainTable, index, key);
                }
            }
        }
    } while (choice != 6);
    
    display_table(table, chainTable);
    
    return 0;
}
