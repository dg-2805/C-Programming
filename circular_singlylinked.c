#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void createList(struct Node** head,int n) {
    int data;
    struct Node* temp;

    for (int i = 1; i <= n; i++) {
        printf("Enter data for node %d: ", i);
        scanf("%d", &data);
        struct Node* newNode = createNode(data);

        if (*head == NULL) {
            *head = newNode;
            (*head)->next = *head;
            temp = *head;
        } else {
            temp->next = newNode;
            newNode->next = *head;
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

    struct Node* temp = *head;
    struct Node* newNode = createNode(data);
    while (temp->next != *head) {
        temp = temp->next;
    }

    newNode->next = *head;
    temp->next = newNode;
    *head = newNode;
    printf("Node inserted at the beginning.\n");
}
void insertAfterPosition(struct Node** head, int data, int pos) {
    if (*head == NULL) {
        printf("List is empty. Create the list first.\n");
        return;
    }

    struct Node* temp = *head;
    struct Node* newNode = createNode(data);
    int count = 1;
    do {
        if (count == pos) {
            newNode->next = temp->next;
            temp->next = newNode;
            printf("Node inserted after position %d.\n", pos);
            return;
        }
        temp = temp->next;
        count++;
    } while (temp != *head);

    printf("Position out of range.\n");
}

void insertBeforePosition(struct Node** head, int data, int pos) {
    if (*head == NULL) {
        printf("List is empty. Create the list first.\n");
        return;
    }

    if (pos == 1) {
        insertAtBeginning(head, data);
        return;
    }

    struct Node* temp = *head;
    struct Node* newNode = createNode(data);
    int count = 1;
    do {
        if (count == pos - 1) {
            newNode->next = temp->next;
            temp->next = newNode;
            printf("Node inserted before position %d.\n", pos);
            return;
        }
        temp = temp->next;
        count++;
    } while (temp != *head);

    printf("Position out of range.\n");
}

void insertAtEnd(struct Node** head, int data) {
    if (*head == NULL) {
        printf("List is empty. Create the list first.\n");
        return;
    }

    struct Node* temp = *head;
    struct Node* newNode = createNode(data);
    do {
        temp = temp->next;
    } while (temp->next != *head);

    temp->next = newNode;
    newNode->next = *head;
    printf("Node inserted at the end.\n");
}
void deleteAfterPosition(struct Node** head, int pos) {
    if (*head == NULL) {
        printf("List is empty. Create the list first.\n");
        return;
    }

    struct Node* temp = *head;
    int count = 1;
    do {
        if (count == pos) {
            struct Node* delNode = temp->next;
            if (delNode == *head) {
                printf("Cannot delete the head node with this operation.\n");
                return;
            }
            temp->next = delNode->next;
            free(delNode);
            printf("Node deleted after position %d.\n", pos);
            return;
        }
        temp = temp->next;
        count++;
    } while (temp != *head);

    printf("Position out of range.\n");
}

void deleteFromEnd(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty. Create the list first.\n");
        return;
    }

    struct Node* temp = *head;
    struct Node* prev = NULL;
    while (temp->next != *head) {
        prev = temp;
        temp = temp->next;
    }

    if (prev != NULL) {
        prev->next = *head;
        free(temp);
        printf("Node deleted from the end.\n");
    } else {
        printf("Cannot delete the only node with this operation.\n");
    }
}

void deleteFromBeginning(struct Node** head) {
    if (*head == NULL) {
        printf("List is empty. Create the list first.\n");
        return;
    }

    struct Node* temp = *head;
    while (temp->next != *head) {
        temp = temp->next;
    }

    struct Node* delNode = *head;
    if (*head == temp) {  // Only one node in the list
        free(delNode);
        *head = NULL;
    } else {
        temp->next = (*head)->next;
        *head = (*head)->next;
        free(delNode);
    }
    printf("Node deleted from the beginning.\n");
}

void searchValue(struct Node* head, int value) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* temp = head;
    int pos = 1;
    do {
        if (temp->data == value) {
            printf("Value %d found at position %d.\n", value, pos);
            return;
        }
        temp = temp->next;
        pos++;
    } while (temp != head);

    printf("Value %d not found in the list.\n", value);
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

void displayList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* temp = head;
    printf("List: ");
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("%d (head)\n", head->data);
}

int main() {
    struct Node* head = NULL;
    int choice, data, pos;

    do {
        printf("\nCircular Singly Linked List Operations:\n");
        printf("1. Create a linked list\n");
        printf("2. Insert after a given position\n");
        printf("3. Insert before a given position\n");
        printf("4. Insert at the end\n");
        printf("5. Insert at the beginning\n");
        printf("6. Delete after a given position\n");
        printf("7. Delete from the end\n");
        printf("8. Delete from the beginning\n");
        printf("9. Search for a value\n");
        printf("10. Destroy the list\n");
        printf("11. Display the list\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            	int n;
            	printf("No of nodes:");
            	scanf("%d",&n);
                createList(&head,n);
                break;
            case 2:
                printf("Enter the position after which to insert: ");
                scanf("%d", &pos);
                printf("Enter the data: ");
                scanf("%d", &data);
                insertAfterPosition(&head, data, pos);
                break;
            case 3:
                printf("Enter the position before which to insert: ");
                scanf("%d", &pos);
                printf("Enter the data: ");
                scanf("%d", &data);
                insertBeforePosition(&head, data, pos);
                break;
            case 4:
                printf("Enter the data to insert at the end: ");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                break;
            case 5:
                printf("Enter the data to insert at the beginning: ");
                scanf("%d", &data);
                insertAtBeginning(&head, data);
                break;
            case 6:
                printf("Enter the position after which to delete: ");
                scanf("%d", &pos);
                deleteAfterPosition(&head, pos);
                break;
            case 7:
                deleteFromEnd(&head);
                break;
            case 8:
                deleteFromBeginning(&head);
                break;
            case 9:
                printf("Enter the value to search: ");
                scanf("%d", &data);
                searchValue(head, data);
                break;
            case 10:
                destroyList(&head);
                break;
            case 11:
                displayList(head);
                break;
            case 12:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 12);

    return 0;
}


/*Sample Output
Circular Singly Linked List Operations:
1. Create a linked list
2. Insert after a given position
3. Insert before a given position
4. Insert at the end
5. Insert at the beginning
6. Delete after a given position
7. Delete from the end
8. Delete from the beginning
9. Search for a value
10. Destroy the list
11. Display the list
12. Exit
Enter your choice: 1
No of nodes:3
Enter data for node 1: 1
Enter data for node 2: 2
Enter data for node 3: 3
List created with 3 nodes.

Circular Singly Linked List Operations:
1. Create a linked list
2. Insert after a given position
3. Insert before a given position
4. Insert at the end
5. Insert at the beginning
6. Delete after a given position
7. Delete from the end
8. Delete from the beginning
9. Search for a value
10. Destroy the list
11. Display the list
12. Exit
Enter your choice: 11
List: 1 -> 2 -> 3 -> 1 (head)

Circular Singly Linked List Operations:
1. Create a linked list
2. Insert after a given position
3. Insert before a given position
4. Insert at the end
5. Insert at the beginning
6. Delete after a given position
7. Delete from the end
8. Delete from the beginning
9. Search for a value
10. Destroy the list
11. Display the list
12. Exit
Enter your choice: 4
Enter the data to insert at the end: 30
Node inserted at the end.

Circular Singly Linked List Operations:
1. Create a linked list
2. Insert after a given position
3. Insert before a given position
4. Insert at the end
5. Insert at the beginning
6. Delete after a given position
7. Delete from the end
8. Delete from the beginning
9. Search for a value
10. Destroy the list
11. Display the list
12. Exit
Enter your choice: 11
List: 1 -> 2 -> 3 -> 30 -> 1 (head)

Circular Singly Linked List Operations:
1. Create a linked list
2. Insert after a given position
3. Insert before a given position
4. Insert at the end
5. Insert at the beginning
6. Delete after a given position
7. Delete from the end
8. Delete from the beginning
9. Search for a value
10. Destroy the list
11. Display the list
12. Exit
Enter your choice: 8
Node deleted from the beginning.

Circular Singly Linked List Operations:
1. Create a linked list
2. Insert after a given position
3. Insert before a given position
4. Insert at the end
5. Insert at the beginning
6. Delete after a given position
7. Delete from the end
8. Delete from the beginning
9. Search for a value
10. Destroy the list
11. Display the list
12. Exit
Enter your choice: 11
List: 2 -> 3 -> 30 -> 2 (head)

Circular Singly Linked List Operations:
1. Create a linked list
2. Insert after a given position
3. Insert before a given position
4. Insert at the end
5. Insert at the beginning
6. Delete after a given position
7. Delete from the end
8. Delete from the beginning
9. Search for a value
10. Destroy the list
11. Display the list
12. Exit
Enter your choice: 9
Enter the value to search: 5
Value 5 not found in the list.

Circular Singly Linked List Operations:
1. Create a linked list
2. Insert after a given position
3. Insert before a given position
4. Insert at the end
5. Insert at the beginning
6. Delete after a given position
7. Delete from the end
8. Delete from the beginning
9. Search for a value
10. Destroy the list
11. Display the list
12. Exit
Enter your choice: 12
Exiting... */
