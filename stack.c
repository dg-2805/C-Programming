#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
    int size;
} Stack;

Stack *create_stack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void display(Stack *stack) {
    if (stack->size == 0) {
        printf("Stack is empty\n");
        printf("Top index: none\n");
        return;
    }

    Node *current = stack->top;
    printf("Stack contents: ");
    for (int i = 0; current != NULL; i++) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\nTop index: %d\n", stack->size - 1);
}

void push(Stack *stack, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
    printf("Pushed %d onto the stack.\n", value);
    display(stack);
}

int pop(Stack *stack) {
    if (stack->size == 0) {
        printf("Stack underflow\n");
        return -1;
    }
    Node *temp = stack->top;
    int poppedValue = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    printf("Popped value: %d\n", poppedValue);
    display(stack);
    return poppedValue;
}

int peek(Stack *stack) {
    if (stack->size == 0) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->top->data;
}

int is_empty(Stack *stack) {
    return stack->size == 0;
}

int main() {
    Stack *stack = create_stack();
    int choice, value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Check if empty\n");
        printf("5. Display stack\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(stack, value);
                break;
            case 2:
                pop(stack);
                break;
            case 3:
                value = peek(stack);
                if (value != -1) {
                    printf("Top value: %d\n", value);
                }
                break;
            case 4:
                if (is_empty(stack)) {
                    printf("Stack is empty\n");
                } else {
                    printf("Stack is not empty\n");
                }
                break;
            case 5:
                display(stack);
                break;
            case 6:
                while (!is_empty(stack)) {
                    pop(stack);
                }
                free(stack);
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}

/* Sample Output
Menu:
1. Push
2. Pop
3. Peek
4. Check if empty
5. Display stack
6. Exit
Enter your choice: 1
Enter value to push: 7
Pushed 7 onto the stack.
Stack contents: 7 
Top index: 0

Menu:
1. Push
2. Pop
3. Peek
4. Check if empty
5. Display stack
6. Exit
Enter your choice: 1
Enter value to push: 2
Pushed 2 onto the stack.
Stack contents: 2 7 
Top index: 1

Menu:
1. Push
2. Pop
3. Peek
4. Check if empty
5. Display stack
6. Exit
Enter your choice: 1
Enter value to push: 9
Pushed 9 onto the stack.
Stack contents: 9 2 7 
Top index: 2

Menu:
1. Push
2. Pop
3. Peek
4. Check if empty
5. Display stack
6. Exit
Enter your choice: 5
Stack contents: 9 2 7 
Top index: 2

Menu:
1. Push
2. Pop
3. Peek
4. Check if empty
5. Display stack
6. Exit
Enter your choice: 3
Top value: 9

Menu:
1. Push
2. Pop
3. Peek
4. Check if empty
5. Display stack
6. Exit
Enter your choice: 2
Popped value: 9
Stack contents: 2 7 
Top index: 1

Menu:
1. Push
2. Pop
3. Peek
4. Check if empty
5. Display stack
6. Exit
Enter your choice: 1
Enter value to push: 4
Pushed 4 onto the stack.
Stack contents: 4 2 7 
Top index: 2

Menu:
1. Push
2. Pop
3. Peek
4. Check if empty
5. Display stack
6. Exit
Enter your choice: 4
Stack is not empty

Menu:
1. Push
2. Pop
3. Peek
4. Check if empty
5. Display stack
6. Exit
Enter your choice: 2
Popped value: 4
Stack contents: 2 7 
Top index: 1

Menu:
1. Push
2. Pop
3. Peek
4. Check if empty
5. Display stack
6. Exit
Enter your choice: 2
Popped value: 2
Stack contents: 7 
Top index: 0

Menu:
1. Push
2. Pop
3. Peek
4. Check if empty
5. Display stack
6. Exit
Enter your choice: 2
Popped value: 7
Stack is empty
Top index: none

Menu:
1. Push
2. Pop
3. Peek
4. Check if empty
5. Display stack
6. Exit
Enter your choice: 4
Stack is empty

Menu:
1. Push
2. Pop
3. Peek
4. Check if empty
5. Display stack
6. Exit
Enter your choice: 5
Stack is empty
Top index: none

Menu:
1. Push
2. Pop
3. Peek
4. Check if empty
5. Display stack
6. Exit
Enter your choice: 6 */
