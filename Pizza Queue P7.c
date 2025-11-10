#include <stdio.h>
#include <stdlib.h>

#define MAX_ORDERS 5 // Maximum number of orders (M)

// Global variables for the queue
int orders[MAX_ORDERS];
int front = -1;
int rear = -1;

// Function to check if the queue is empty
int isEmpty() {
    return front == -1;
}

// Function to check if the queue is full
int isFull() {
    return (front == 0 && rear == MAX_ORDERS - 1) || (front == rear + 1);
}

// Function to add a job (order) to the queue
void addJob(int orderNumber) {
    if (isFull()) {
        printf("Queue is full. Cannot accept more orders.\n");
    } else {
        if (isEmpty()) {
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % MAX_ORDERS;
        }
        orders[rear] = orderNumber;
        printf("Order %d placed successfully.\n", orderNumber);
    }
}

// Function to delete a job (order) from the queue
void deleteJob() {
    if (isEmpty()) {
        printf("No orders to serve. Queue is empty.\n");
    } else {
        int servedOrder = orders[front];
        printf("Serving order %d.\n", servedOrder);
        if (front == rear) { // Last element in the queue
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % MAX_ORDERS;
        }
    }
}

// Function to display the orders in the queue
void displayOrders() {
    if (isEmpty()) {
        printf("No orders in the queue.\n");
    } else {
        printf("Current orders in queue:\n");
        int i = front;
        while (1) {
            printf("Order %d\n", orders[i]);
            if (i == rear) break;
            i = (i + 1) % MAX_ORDERS;
        }
    }
}

int main() {
    int choice, orderNum = 1;

    do {
        printf("\nPizza Parlor Order Management System\n");
        printf("1. Place Order\n");
        printf("2. Serve Order\n");
        printf("3. Display Orders\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addJob(orderNum++);
                break;
            case 2:
                deleteJob();
                break;
            case 3:
                displayOrders();
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
