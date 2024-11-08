#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct CircularQueue {
    Node *front;
    Node *rear;
} CircularQueue;

CircularQueue *create_queue() {
    CircularQueue *queue = (CircularQueue *)malloc(sizeof(CircularQueue));
    queue->front = queue->rear = NULL;
    return queue;
}

void display(CircularQueue *queue) {
    if (queue->front == NULL) {
        printf("Queue is empty\n");
        printf("Front: none, Rear: none\n");
        return;
    }

    Node *current = queue->front;
    printf("Queue contents: ");
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != queue->front);
    
    printf("\nFront: %d, Rear: %d\n", queue->front->data, queue->rear->data);
}

void enqueue(CircularQueue *queue, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        newNode->next = newNode;
    } else {
        newNode->next = queue->front;
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    printf("Enqueued %d to the queue.\n", value);
    display(queue);
}

int dequeue(CircularQueue *queue) {
    if (queue->front == NULL) {
        printf("Queue underflow\n");
        return -1;
    }

    int dequeuedValue;
    if (queue->front == queue->rear) {
        dequeuedValue = queue->front->data;
        free(queue->front);
        queue->front = queue->rear = NULL;
    } else {
        Node *temp = queue->front;
        dequeuedValue = temp->data;
        queue->front = queue->front->next;
        queue->rear->next = queue->front;
        free(temp);
    }

    printf("Dequeued value: %d\n", dequeuedValue);
    display(queue);
    return dequeuedValue;
}

int is_empty(CircularQueue *queue) {
    return queue->front == NULL;
}

int main() {
    CircularQueue *queue = create_queue();
    int choice, value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(queue, value);
                break;
            case 2:
                dequeue(queue);
                break;
            case 3:
                display(queue);
                break;
            case 4:
                free(queue);
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}

/* Sample Output
Menu:
1. Enqueue
2. Dequeue
3. Display queue
4. Exit
Enter your choice: 1
Enter value to enqueue: 5
Enqueued 5 to the queue.
Queue contents: 5 
Front: 5, Rear: 5

Menu:
1. Enqueue
2. Dequeue
3. Display queue
4. Exit
Enter your choice: 1
Enter value to enqueue: 8
Enqueued 8 to the queue.
Queue contents: 5 8 
Front: 5, Rear: 8

Menu:
1. Enqueue
2. Dequeue
3. Display queue
4. Exit
Enter your choice: 1
Enter value to enqueue: 9
Enqueued 9 to the queue.
Queue contents: 5 8 9 
Front: 5, Rear: 9

Menu:
1. Enqueue
2. Dequeue
3. Display queue
4. Exit
Enter your choice: 1
Enter value to enqueue: 3
Enqueued 3 to the queue.
Queue contents: 5 8 9 3 
Front: 5, Rear: 3

Menu:
1. Enqueue
2. Dequeue
3. Display queue
4. Exit
Enter your choice: 3
Queue contents: 5 8 9 3 
Front: 5, Rear: 3

Menu:
1. Enqueue
2. Dequeue
3. Display queue
4. Exit
Enter your choice: 2
Dequeued value: 5
Queue contents: 8 9 3 
Front: 8, Rear: 3

Menu:
1. Enqueue
2. Dequeue
3. Display queue
4. Exit
Enter your choice: 2
Dequeued value: 8
Queue contents: 9 3 
Front: 9, Rear: 3

Menu:
1. Enqueue
2. Dequeue
3. Display queue
4. Exit
Enter your choice: 2
Dequeued value: 9
Queue contents: 3 
Front: 3, Rear: 3

Menu:
1. Enqueue
2. Dequeue
3. Display queue
4. Exit
Enter your choice: 2
Dequeued value: 3
Queue is empty
Front: none, Rear: none

Menu:
1. Enqueue
2. Dequeue
3. Display queue
4. Exit
Enter your choice: 3
Queue is empty
Front: none, Rear: none

Menu:
1. Enqueue
2. Dequeue
3. Display queue
4. Exit
Enter your choice: 4
*/
