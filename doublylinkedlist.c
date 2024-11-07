//Doubly LInked List
#include <stdio.h>
#include <stdlib.h>
// Definition
typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} node;
// 0. Create a new node
struct node *createnode(int data) {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}
// 1. Create a list with n nodes
void createlist(node **head, int n) {
    int data;
    node *temp, *newnode;
    for (int i = 0; i < n; i++) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &data);
        newnode = createnode(data);
        
        if (*head == NULL) {
            *head = newnode;
        } else {
            temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newnode;
            newnode->prev = temp;
        }
    }
}
// 4. Insert at the end
void insertatend(node **head, int data) {
    node *newnode = createnode(data);
    if (*head == NULL) {
        *head = newnode;
        return;
    }
    node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newnode;
    newnode->prev = temp;
}
// 5. Insert at the beginning
void insertatbegin(node **head, int data) {
    node *newnode = createnode(data);
    if (*head != NULL) {
        (*head)->prev = newnode;
    }
    newnode->next = *head;
    *head = newnode;
}
// 2. Insert after a given position
void insertafterpos(node **head, int pos, int data) {
    if (*head == NULL && pos != 1) {
        printf("Invalid position\n");
        return;
    }
    node *temp = *head;
    for (int i = 1; i < pos; i++) {
        if (temp == NULL) {
            printf("Invalid position\n");
            return;
        }
        temp = temp->next;
    }
    node *newnode = createnode(data);
    newnode->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = newnode;
    }
    temp->next = newnode;
    newnode->prev = temp;
}
// 3. Insert before a given position
void insertbeforepos(node **head, int pos, int data) {
    if (pos < 1) {
        printf("Invalid position\n");
        return;
    }
    if (pos == 1) {
        insertatbegin(head, data);
        return;
    }
    node *temp = *head;
    for (int i = 1; i < pos - 1; i++) {
        if (temp == NULL) {
            printf("Invalid position\n");
            return;
        }
        temp = temp->next;
    }
    node *newnode = createnode(data);
    newnode->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = newnode;
    }
    temp->next = newnode;
    newnode->prev = temp;
}
// 9. Delete from the end
void deletefromend(node **head) {
    if (*head == NULL) {
        printf("List Empty\n");
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->prev->next = NULL;
    free(temp);
}
// 10. Delete from the beginning
void deletefrombegin(node **head) {
    if (*head == NULL) {
        printf("List Empty\n");
        return;
    }
    node *temp = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(temp);
}
// 6. Delete before a given position
void deletebeforepos(node **head, int pos) {
    if (*head == NULL || pos < 2) {
        printf("No node before\n");
        return;
    }
    if (pos == 2) {
        deletefrombegin(head);
        return;
    }
    node *temp = *head;
    for (int i = 1; i < pos - 2; i++) {
        if (temp == NULL || temp->next == NULL) {
            printf("Invalid position\n");
            return;
        }
        temp = temp->next;
    }
    node *delnode = temp->next;
    temp->next = delnode->next;
    if (delnode->next != NULL) {
        delnode->next->prev = temp;
    }
    free(delnode);
}
// 7. Delete at a given position
void deleteatpos(node **head, int pos) {
    if (*head == NULL) {
        printf("List Empty\n");
        return;
    }
    if (pos < 1) {
        printf("Invalid\n");
        return;
    }
    if (pos == 1) {
        deletefrombegin(head);
        return;
    }
    node *temp = *head;
    for (int i = 1; i < pos - 1; i++) {
        if (temp == NULL) {
            printf("Invalid position\n");
            return;
        }
        temp = temp->next;
    }
    node *delnode = temp->next;
    temp->next = delnode->next;
    if (delnode->next != NULL) {
        delnode->next->prev = temp;
    }
    free(delnode);
}
// 8. Delete after a given position
void deleteafterpos(node **head, int pos) {
    if (*head == NULL) {
        printf("List Empty\n");
        return;
    }
    node *temp = *head;
    for (int i = 1; i < pos; i++) {
        if (temp == NULL) {
            printf("Invalid position\n");
            return;
        }
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("No node to delete after\n");
        return;
    }
    node *delnode = temp->next;
    temp->next = delnode->next;
    if (delnode->next != NULL) {
        delnode->next->prev = temp;
    }
    free(delnode);
}
// 11. Searching for a value
void searchlist(node *head, int value) {
    int c = 1;
    node *temp = head;
    while (temp != NULL) {
        if (temp->data == value) {
            printf("Node found at position %d\n", c);
            return;
        }
        temp = temp->next;
        c++;
    }
    printf("Node not found\n");
}
// 12. Destroying the list
void destroylist(node **head) {
    node *temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}
// 13. Displaying the list
void displaylist(node **head) {
    node *temp = *head;
    while (temp != NULL) {
        printf("%d<->", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
// 14. Freeing list
void freelist(node **head) {
    destroylist(head);
}
int main() {
    node *head = NULL;
    int choice, n, value, pos, data;
    while (1) {
        printf("\nMenu\n\
        1. Create a linked list\n\
        2. Insert after a given position\n\
        3. Insert before a given position\n\
        4. Insert at the end\n\
        5. Insert at the beginning\n\
        6. Delete before a given position\n\
        7. Delete at a given position\n\
        8. Delete after a given position\n\
        9. Delete from the end\n\
        10. Delete from the beginning\n\
        11. Searching for a value\n\
        12. Destroying the list\n\
        13. Displaying the list\n\
        14. Exit\n\
        Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter no. of nodes: ");
                scanf("%d", &n);
                createlist(&head, n);
                break;
            case 2:
                printf("Enter position: ");
                scanf("%d", &pos);
                printf("Enter data for node: ");
                scanf("%d", &data);
                insertafterpos(&head, pos, data);
                break;
            case 3:
                printf("Enter position: ");
                scanf("%d", &pos);
                printf("Enter data for node: ");
                scanf("%d", &data);
                insertbeforepos(&head, pos, data);
                break;
            case 4:
                printf("Enter data for node: ");
                scanf("%d", &data);
                insertatend(&head, data);
                break;
            case 5:
                printf("Enter data for node: ");
                scanf("%d", &data);
                insertatbegin(&head, data);
                break;
            case 6:
                printf("Enter position: ");
                scanf("%d", &pos);
                deletebeforepos(&head, pos);
                break;
            case 7:
                printf("Enter position: ");
                scanf("%d", &pos);
                deleteatpos(&head, pos);
                break;
            case 8:
                printf("Enter position: ");
                scanf("%d", &pos);
                deleteafterpos(&head, pos);
                break;
            case 9:
                deletefromend(&head);
                break;
            case 10:
                deletefrombegin(&head);
                break;
            case 11:
                printf("Enter value: ");
                scanf("%d", &value);
                searchlist(head, value);
                break;
            case 12:
                destroylist(&head);
                break;
            case 13:
                displaylist(&head);
                break;
            case 14:
                freelist(&head);
                exit(0);
                break;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}


/*Sample Output
Menu
        1. Create a linked list
        2. Insert after a given position
        3. Insert before a given position
        4. Insert at the end
        5. Insert at the beginning
        6. Delete before a given position
        7. Delete at a given position
        8. Delete after a given position
        9. Delete from the end
        10. Delete from the beginning
        11. Searching for a value
        12. Destroying the list
        13. Displaying the list
        14. Exit
        Enter your choice: 1
Enter no. of nodes: 4
Enter data for node 1: 6
Enter data for node 2: 7
Enter data for node 3: 8
Enter data for node 4: 9

Menu
        1. Create a linked list
        2. Insert after a given position
        3. Insert before a given position
        4. Insert at the end
        5. Insert at the beginning
        6. Delete before a given position
        7. Delete at a given position
        8. Delete after a given position
        9. Delete from the end
        10. Delete from the beginning
        11. Searching for a value
        12. Destroying the list
        13. Displaying the list
        14. Exit
        Enter your choice: 13
6<->7<->8<->9<->NULL

Menu
        1. Create a linked list
        2. Insert after a given position
        3. Insert before a given position
        4. Insert at the end
        5. Insert at the beginning
        6. Delete before a given position
        7. Delete at a given position
        8. Delete after a given position
        9. Delete from the end
        10. Delete from the beginning
        11. Searching for a value
        12. Destroying the list
        13. Displaying the list
        14. Exit
        Enter your choice: 11
Enter value: 7
Node found at position 2

Menu
        1. Create a linked list
        2. Insert after a given position
        3. Insert before a given position
        4. Insert at the end
        5. Insert at the beginning
        6. Delete before a given position
        7. Delete at a given position
        8. Delete after a given position
        9. Delete from the end
        10. Delete from the beginning
        11. Searching for a value
        12. Destroying the list
        13. Displaying the list
        14. Exit
        Enter your choice: 5
Enter data for node: 2

Menu
        1. Create a linked list
        2. Insert after a given position
        3. Insert before a given position
        4. Insert at the end
        5. Insert at the beginning
        6. Delete before a given position
        7. Delete at a given position
        8. Delete after a given position
        9. Delete from the end
        10. Delete from the beginning
        11. Searching for a value
        12. Destroying the list
        13. Displaying the list
        14. Exit
        Enter your choice: 13
2<->6<->7<->8<->9<->NULL

Menu
        1. Create a linked list
        2. Insert after a given position
        3. Insert before a given position
        4. Insert at the end
        5. Insert at the beginning
        6. Delete before a given position
        7. Delete at a given position
        8. Delete after a given position
        9. Delete from the end
        10. Delete from the beginning
        11. Searching for a value
        12. Destroying the list
        13. Displaying the list
        14. Exit
        Enter your choice: 8
Enter position: 4

Menu
        1. Create a linked list
        2. Insert after a given position
        3. Insert before a given position
        4. Insert at the end
        5. Insert at the beginning
        6. Delete before a given position
        7. Delete at a given position
        8. Delete after a given position
        9. Delete from the end
        10. Delete from the beginning
        11. Searching for a value
        12. Destroying the list
        13. Displaying the list
        14. Exit
        Enter your choice: 13
2<->6<->7<->8<->NULL

Menu
        1. Create a linked list
        2. Insert after a given position
        3. Insert before a given position
        4. Insert at the end
        5. Insert at the beginning
        6. Delete before a given position
        7. Delete at a given position
        8. Delete after a given position
        9. Delete from the end
        10. Delete from the beginning
        11. Searching for a value
        12. Destroying the list
        13. Displaying the list
        14. Exit
        Enter your choice: 12

Menu
        1. Create a linked list
        2. Insert after a given position
        3. Insert before a given position
        4. Insert at the end
        5. Insert at the beginning
        6. Delete before a given position
        7. Delete at a given position
        8. Delete after a given position
        9. Delete from the end
        10. Delete from the beginning
        11. Searching for a value
        12. Destroying the list
        13. Displaying the list
        14. Exit
        Enter your choice: 13
NULL

Menu
        1. Create a linked list
        2. Insert after a given position
        3. Insert before a given position
        4. Insert at the end
        5. Insert at the beginning
        6. Delete before a given position
        7. Delete at a given position
        8. Delete after a given position
        9. Delete from the end
        10. Delete from the beginning
        11. Searching for a value
        12. Destroying the list
        13. Displaying the list
        14. Exit
        Enter your choice: 14
*/
