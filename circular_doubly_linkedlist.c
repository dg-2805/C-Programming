#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void createList(struct Node** head, int n) {
    int data;
    struct Node* temp;

    for (int i = 1; i <= n; i++) {
        printf("Enter data for node %d: ", i);
        scanf("%d", &data);
        struct Node* newNode = createNode(data);

        if (*head == NULL) {
            *head = newNode;
            (*head)->next = *head;
            (*head)->prev = *head;
            temp = *head;
        } else {
            newNode->next = *head;
            newNode->prev = temp;
            temp->next = newNode;
            (*head)->prev = newNode;
            temp = newNode;
        }
    }
    printf("List created with %d nodes.\n", n);
}

void insertAtBeginning(struct Node** head, int data) {
    if (*head == NULL) {
        printf("List is empty. Create the list first.\n");
        return;
    }

    struct Node* newNode = createNode(data);
    struct Node* last = (*head)->prev;

    newNode->next = *head;
    newNode->prev = last;
    last->next = newNode;
    (*head)->prev = newNode;
    *head = newNode;

    printf("Node inserted at the beginning.\n");
}

void insertAtEnd(struct Node** head, int data) {
    if (*head == NULL) {
        printf("List is empty. Create the list first.\n");
        return;
    }

    struct Node* newNode = createNode(data);
    struct Node* last = (*head)->prev;

    newNode->next = *head;
    newNode->prev = last;
    last->next = newNode;
    (*head)->prev = newNode;

    printf("Node inserted at the end.\n");
}

void insertAfterPosition(struct Node** head, int data, int pos) {
    if (*head == NULL) {
        printf("List is empty. Create the list first.\n");
        return;
    }

    struct Node* temp = *head;
    int count = 1;

    do {
        if (count == pos) {
            struct Node* newNode = createNode(data);
            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next->prev = newNode;
            temp->next = newNode;
            printf("Node inserted after position %d.\n", pos);
            return;
        }
        temp = temp->next;
        count++;
    } while (temp != *head);

    printf("Position out of range.\n");
}

void deleteFromBeginning(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty. Create the list first.\n");
        return;
    }

    struct Node* last = (*head)->prev;
    struct Node* delNode = *head;

    if (*head == (*head)->next) {
        free(delNode);
        *head = NULL;
    } else {
        last->next = (*head)->next;
        (*head)->next->prev = last;
        *head = (*head)->next;
        free(delNode);
    }

    printf("Node deleted from the beginning.\n");
}

void deleteFromEnd(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty. Create the list first.\n");
        return;
    }

    struct Node* last = (*head)->prev;
    
    if (*head == last) {
        free(last);
        *head = NULL;
    } else {
        last->prev->next = *head;
        (*head)->prev = last->prev;
        free(last);
    }

    printf("Node deleted from the end.\n");
}

void displayList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* temp = head;
    printf("List: ");
    do {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(head)\n");
}

void destroyList(struct Node** head) {
    if (*head == NULL) {
        printf("List is already empty.\n");
        return;
    }

    struct Node* temp = *head;
    do {
        struct Node* nextNode = temp->next;
        free(temp);
        temp = nextNode;
    } while (temp != *head);

    *head = NULL;
    printf("List destroyed.\n");
}

int main() {
    struct Node* head = NULL;
    int choice, data, pos;

    do {
        printf("\nCircular Doubly Linked List Operations:\n");
        printf("1. Create a linked list\n");
        printf("2. Insert at the beginning\n");
        printf("3. Insert at the end\n");
        printf("4. Insert after a position\n");
        printf("5. Delete from the beginning\n");
        printf("6. Delete from the end\n");
        printf("7. Display the list\n");
        printf("8. Destroy the list\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of nodes: ");
                int n;
                scanf("%d", &n);
                createList(&head, n);
                break;
            case 2:
                printf("Enter the data to insert at the beginning: ");
                scanf("%d", &data);
                insertAtBeginning(&head, data);
                break;
            case 3:
                printf("Enter the data to insert at the end: ");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                break;
            case 4:
                printf("Enter the position after which to insert: ");
                scanf("%d", &pos);
                printf("Enter the data: ");
                scanf("%d", &data);
                insertAfterPosition(&head, data, pos);
                break;
            case 5:
                deleteFromBeginning(&head);
                break;
            case 6:
                deleteFromEnd(&head);
                break;
            case 7:
                displayList(head);
                break;
            case 8:
                destroyList(&head);
                break;
            case 9:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    } while (choice != 9);

    return 0;
}
