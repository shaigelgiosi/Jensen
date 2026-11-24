#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// User node definition
typedef struct Node {
    char name[50];
    int level; // 1=Normal, 2=VIP, 3=SVIP
    struct Node* next;
} Node;

// Queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Initialize the queue
// Parameter: q - the queue
void initQueue(Queue* q) {
    // TODO: complete the queue initialization; the head is front and the tail is rear
    q->front = NULL;
    q->rear = NULL;
}

// Create a node
Node* createNode(const char* name, int level) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->level = level;
    newNode->next = NULL;
    return newNode;
}

// Request operation: enqueue (with priority-aware insertion)
// Parameters: q - the queue, name - the username, level - the user level
void request(Queue* q, const char* name, int level) {
    Node* newNode = createNode(name, level);
    // If the queue is empty, add it directly
    if (q->front == NULL) {
        // TODO: complete the logic for the empty-queue case
        q->front = newNode;
        q->rear = newNode;
    }
    // Insertion rule: higher-level users are placed before lower-level ones; equal levels line up behind
    else
    {
        Node* prev = NULL;
        Node* curr = q->front;

        // Skip nodes whose level is higher than the new user's
        while (curr != NULL && curr->level > level) {
            prev = curr;
            curr = curr->next;
        }

        // Skip all nodes of the same level so the new user lines up behind them
        while (curr != NULL && curr->level == level) {
            prev = curr;
            curr = curr->next;
        }

        newNode->next = curr;

        if (prev == NULL) {
            q->front = newNode;
        } else {
            prev->next = newNode;
        }

        if (curr == NULL) {
            q->rear = newNode;
        }
    }
}

// Download operation: output the front element and remove it
// Parameter: q - the queue
void download(Queue* q) {
    if (q->front == NULL) {
        printf("The line is empty,we don't have task to download.\n");
        return;
    }
    Node* temp = q->front;
    printf("Downloading:%s (level=%d)\n", temp->name, temp->level);
    // Remove the front element
    q->front = temp->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
}

// Remove operation: delete the specified user
// Parameters: q - the queue, name - the username
void removeUser(Queue* q, const char* name) {
    if (q->front == NULL) {
        printf("The line is empty so we can't delete it.\n");
        return;
    }
    Node* prev = NULL;
    Node* curr = q->front;
    while (curr != NULL && strcmp(curr->name, name) != 0) {
        // TODO: complete the logic for locating the specified user
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("We don't find the user:%s\n", name);
        return;
    }
    // Delete the specified user; make sure to handle the head and tail cases
    // TODO: complete this part
    if(prev == NULL)
    {
        q->front = curr->next;
        if(q->front == NULL)
            q->rear = NULL;
    }
    else
    {
        prev->next = curr->next;
        if(curr == q->rear)
            q->rear = prev;
    }
    free(curr);
    printf("The user has been deleted:%s\n", name);
}

// Display operation: show the queue
// Parameter: q - the queue
void display(Queue* q) {
    if (q->front == NULL) {
        printf("The line is empty.\n");
        return;
    }
    Node* curr = q->front;
    printf("The line is downloading now:\n");
    while (curr != NULL) {
        printf("User_name: %-10s | level: %d\n", curr->name, curr->level);
        // TODO: complete the remaining logic
        curr = curr->next;
    }
}

// Main function: simulate operation commands
int main() {
    Queue q;
    initQueue(&q);

    char command[50];
    char name[50];
    int level;
    printf("=== Some network disk level sorting design ===\n"); 
    printf("Supported order：Request User_name level | Download | Remove User_name | Display | Exit\n");
    printf("Please input the order:\n");
    while (1) {
        scanf("%s", command);
        if (strcmp(command, "Request") == 0) {
            scanf("%s %d", name, &level);
            // Complete the user level validation: when an invalid level is entered, output “Invalid user level, please input 1(common) 2(VIP) 3(SVIP).” and then a newline.
            // TODO:
            if(level < 1 || level > 3)
            {
                printf("Invalid user level, please input 1(common) 2(VIP) 3(SVIP).\n");
                continue;
            }
            request(&q, name, level);
            printf("User %s (level=%d) has get in the line.\n", name, level);

        } else if (strcmp(command, "Download") == 0) {
            download(&q);

        } else if (strcmp(command, "Remove") == 0) {
            scanf("%s", name);
            removeUser(&q, name);

        } else if (strcmp(command, "Display") == 0) {
            display(&q);

        } else if (strcmp(command, "Exit") == 0) {
            printf("The code has been exited.\n");
            break;
        } 
        // Complete the code logic: when an invalid command is entered, output “Invalid order, Please input again.” and then a newline
        // TODO:
        else
        {
            printf("Invalid order, Please input again.\n");
        }
    }

    return 0;
}
