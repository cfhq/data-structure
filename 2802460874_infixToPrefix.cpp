#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char items[MAX];
    int top;
} stack;

void initStack(stack *s) {
    s->top = -1;
}

int isEmpty(stack *s) {
    return s->top == -1;
}

void push(stack *s, char c) {
    if (s->top < MAX - 1)
        s->items[++(s->top)] = c;
}

char pop(stack *s) {
    if (!isEmpty(s))
        return s->items[(s->top)--];
    return '\0';
}

char peek(stack *s) {
    if (!isEmpty(s))
        return s->items[s->top];
    return '\0';
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

void reverse(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

void infixToPrefix(char *infix, char *prefix) {
    stack operators;
    initStack(&operators);
    reverse(infix);
    
    int j = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            prefix[j++] = c;
        }
        
        else if (c == ')') {
            push(&operators, c);
        }
        
        else if (c == '(') {
            while (!isEmpty(&operators) && peek(&operators) != ')') {
                prefix[j++] = pop(&operators);
            }
            pop(&operators);
        }
        
        else if (isOperator(c)) {
            while (!isEmpty(&operators) && precedence(peek(&operators)) >= precedence(c)) {
                prefix[j++] = pop(&operators);
            }
            push(&operators, c);
        }
    }
    
    
    while (!isEmpty(&operators)) {
        prefix[j++] = pop(&operators);
    }
    prefix[j] = '\0';
    reverse(prefix);
}

int main() {
    char infix[MAX], prefix[MAX];
    printf("Enter infix expression: ");
    scanf("%[^\n]", infix);
    infixToPrefix(infix, prefix);
    printf("Prefix expression: %s\n", prefix);
    return 0;
}
