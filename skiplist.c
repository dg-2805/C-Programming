//Write a C program to implement skip list.

#CODE

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define PLUS_INFINITY INT_MAX
#define MINUS_INFINITY INT_MIN

int c = 0;

typedef struct node {
    int key;
    struct node *f;
    struct node *b;
    struct node *u;
    struct node *d;
} node;

typedef struct skiplist {
    node *head;
    node *tail;
    int level;
    int size;
} skiplist;

int toss() {
    return rand() % 2;
}

node *createNode(int key) {
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->f = NULL;
    newNode->b = NULL;
    newNode->u = NULL;
    newNode->d = NULL;
    return newNode;
}

skiplist *createSkiplist() {
    skiplist *sl = (skiplist *)malloc(sizeof(skiplist));
    if (sl == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    node *p2 = createNode(PLUS_INFINITY);
    node *p1 = createNode(MINUS_INFINITY);

    p1->f = p2;
    p2->b = p1;
    sl->head = p1;
    sl->tail = p2;
    sl->level = 0;
    sl->size = 0;

    return sl;
}

void addEmptyList(skiplist *sl) {
    node *p1 = createNode(MINUS_INFINITY);
    node *p2 = createNode(PLUS_INFINITY);

    p1->f = p2;
    p1->d = sl->head;

    p2->b = p1;
    p2->d = sl->tail;

    sl->head->u = p1;
    sl->tail->u = p2;

    sl->head = p1;
    sl->tail = p2;

    sl->level++;
}

node *search(skiplist *sl, int value) {
    node *t = sl->head;
    while (1) {
        while (t->f->key != PLUS_INFINITY && t->f->key <= value) {
            t = t->f;
            c++;
        }
        if (t->d) {
            t = t->d;
            c++;
        } else
            break;
    }
    return t;
}

void insert(skiplist *sl, int value) {
    c = 0;
    node *p = search(sl, value);
    if (p->key == value) {
        printf("Value %d already exists in the skiplist. Comparisons: %d\n", value, c);
        return;
    }
    node *newNode = createNode(value);
    newNode->f = p->f;
    newNode->b = p;
    p->f->b = newNode;
    p->f = newNode;
    
    int current_level = 0;
    node *curr_node = newNode; 
    while (toss()) {
        if (current_level >= sl->level)
            addEmptyList(sl);

        while (p->b && p->u == NULL) 
            p = p->b;

        if (p->u == NULL)
            break;
        p = p->u;

        node *newNodeUp = createNode(value);
        newNodeUp->f = p->f;
        newNodeUp->b = p;
        newNodeUp->d = curr_node;
        p->f->b = newNodeUp;
        p->f = newNodeUp;
        curr_node->u = newNodeUp;
        curr_node = newNodeUp;

        current_level++;
    }
    if (sl->head->f != sl->tail) {
        addEmptyList(sl);
    }
    sl->size++;
    printf("Value %d inserted. Comparisons: %d\n", value, c);
}

void deleteExtras(skiplist *sl) {
    while (sl->head->d != NULL && sl->head->f->key == PLUS_INFINITY) {
        node* old_left = sl->head;
        node* old_right = sl->tail;

        sl->head = old_left->d;
        sl->tail = old_right->d;

        if (sl->head)
            sl->head->u = NULL;
        if (sl->tail)
            sl->tail->u = NULL;

        free(old_left);
        free(old_right);

        sl->level--;
    }
}

void deleteValue(skiplist *sl, int value) {
    c = 0;
    node *p = search(sl, value);
    if (p->key != value) {
        printf("Value %d not found. Comparisons: %d\n", value, c);
        return;
    }

    while (p) {
        p->b->f = p->f;
        p->f->b = p->b;
        node *temp = p;
        p = p->u;
        free(temp); 
    }
    sl->size--; 
    printf("Value %d deleted. Comparisons: %d\n", value, c);
    deleteExtras(sl);
    
    if (sl->head->f != sl->tail) {
        addEmptyList(sl);
    }
}

void searchValue(skiplist *sl, int value) {
    c = 0;
    node *p = search(sl, value);
    if (p->key == value)
        printf("Value %d found. Comparisons: %d\n", value, c);
    else
        printf("Value %d not found. Comparisons: %d\n", value, c);
}

void display(skiplist *sl) {
    node *t = sl->head;
    while (t) {
        node *q = t;
        printf("-INF -> ");
        while (q->f->key != PLUS_INFINITY) {
            printf("%d -> ", q->f->key);
            q = q->f;
        }
        printf("+INF\n");
        t = t->d;
    }
}

int main() {
    srand(time(NULL));
    skiplist *sl = createSkiplist();

    int choice, value;
    do {
        printf("\n1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            insert(sl, value);
            break;
        case 2:
            printf("Enter value to search: ");
            scanf("%d", &value);
            searchValue(sl, value);
            break;
        case 3:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            deleteValue(sl, value);
            break;
        case 4:
            display(sl);
            break;
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

/*
#OUTPUT

1. Insert
2. Search
3. Delete
4. Display
5. Exit
Enter your choice: 4
-INF -> +INF

1. Insert
2. Search
3. Delete
4. Display
5. Exit
Enter your choice: 1
Enter value to insert: 23
Value 23 inserted. Comparisons: 0

1. Insert
2. Search
3. Delete
4. Display
5. Exit
Enter your choice: 4
-INF -> +INF
-INF -> 23 -> +INF
-INF -> 23 -> +INF

1. Insert
2. Search
3. Delete
4. Display
5. Exit
Enter your choice: 1
Enter value to insert: 56
Value 56 inserted. Comparisons: 3

1. Insert
2. Search
3. Delete
4. Display
5. Exit
Enter your choice: 4
-INF -> +INF
-INF -> 23 -> +INF
-INF -> 23 -> 56 -> +INF

1. Insert
2. Search
3. Delete
4. Display
5. Exit
Enter your choice: 1
Enter value to insert: -800
Value -800 inserted. Comparisons: 2

1. Insert
2. Search
3. Delete
4. Display
5. Exit
Enter your choice: 1
Enter value to insert: 34
Value 34 inserted. Comparisons: 3

1. Insert
2. Search
3. Delete
4. Display
5. Exit
Enter your choice: 1
Enter value to insert: -4
Value -4 inserted. Comparisons: 3

1. Insert
2. Search
3. Delete
4. Display
5. Exit
Enter your choice: 4
-INF -> +INF
-INF -> -4 -> +INF
-INF -> -4 -> 23 -> +INF
-INF -> -800 -> -4 -> 23 -> 34 -> 56 -> +INF

1. Insert
2. Search
3. Delete
4. Display
5. Exit
Enter your choice: 3
Enter value to delete: -4
Value -4 deleted. Comparisons: 4

1. Insert
2. Search
3. Delete
4. Display
5. Exit
Enter your choice: 4
-INF -> +INF
-INF -> 23 -> +INF
-INF -> -800 -> 23 -> 34 -> 56 -> +INF

1. Insert
2. Search
3. Delete
4. Display
5. Exit
Enter your choice: 3
Enter value to delete: 23
Value 23 deleted. Comparisons: 3

1. Insert
2. Search
3. Delete
4. Display
5. Exit
Enter your choice: 4
-INF -> +INF
-INF -> -800 -> 34 -> 56 -> +INF

1. Insert
2. Search
3. Delete
4. Display
5. Exit
Enter your choice: 1
Enter value to insert: 197850
Value 197850 inserted. Comparisons: 4

1. Insert
2. Search
3. Delete
4. Display
5. Exit
Enter your choice: 4
-INF -> +INF
-INF -> 197850 -> +INF
-INF -> 197850 -> +INF
-INF -> -800 -> 34 -> 56 -> 197850 -> +INF

1. Insert
2. Search
3. Delete
4. Display
5. Exit
Enter your choice: 2
Enter value to search: 34
Value 34 found. Comparisons: 5

1. Insert
2. Search
3. Delete
4. Display
5. Exit
Enter your choice: 2
Enter value to search: 197850
Value 197850 found. Comparisons: 4

1. Insert
2. Search
3. Delete
4. Display
5. Exit
Enter your choice: 5
Exiting...
*/
