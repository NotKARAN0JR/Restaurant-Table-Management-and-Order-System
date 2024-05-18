#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct TableNode {
    int tableNumber;
    int status;
    int reservationTimeSlot;
    struct TableNode* next;
} TableNode;

typedef struct Queue {
    TableNode* front;
    TableNode* rear;
} Queue;

typedef struct FoodItem {
    int itemNumber;
    char itemName[50];
    double itemPrice;
} FoodItem;

typedef struct OrderNode {
    int orderNumber;
    int tableNumber;
    int menuNumber;
    int quantity;
    struct OrderNode* next;
} OrderNode;

typedef struct OrderQueue {
    OrderNode* front;
    OrderNode* rear;
} OrderQueue;

void initializeQueue(Queue* queue) {
    queue->front = queue->rear = NULL;
}

int isQueueEmpty(Queue* queue) {
    return (queue->front == NULL);
}

void enqueue(Queue* queue, int tableNumber, int status, int reservationTimeSlot) {
    TableNode* newNode = (TableNode*)malloc(sizeof(TableNode));
    newNode->tableNumber = tableNumber;
    newNode->status = status;
    newNode->reservationTimeSlot = reservationTimeSlot;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

TableNode* dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        return NULL;
    }

    TableNode* temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    return temp;
}

void initializeOrderQueue(OrderQueue* orderQueue) {
    orderQueue->front = orderQueue->rear = NULL;
}

int isOrderQueueEmpty(OrderQueue* orderQueue) {
    return (orderQueue->front == NULL);
}

void enqueueOrder(OrderQueue* orderQueue, int orderNumber, int tableNumber, int menuNumber, int quantity) {
    OrderNode* newNode = (OrderNode*)malloc(sizeof(OrderNode));
    newNode->orderNumber = orderNumber;
    newNode->tableNumber = tableNumber;
    newNode->menuNumber = menuNumber;
    newNode->quantity = quantity;
    newNode->next = NULL;

    if (orderQueue->rear == NULL) {
        orderQueue->front = orderQueue->rear = newNode;
    } else {
        orderQueue->rear->next = newNode;
        orderQueue->rear = newNode;
    }
}

OrderNode* dequeueOrder(OrderQueue* orderQueue) {
    if (isOrderQueueEmpty(orderQueue)) {
        return NULL;
    }

    OrderNode* temp = orderQueue->front;
    orderQueue->front = orderQueue->front->next;

    if (orderQueue->front == NULL) {
        orderQueue->rear = NULL;
    }

    return temp;
}
FoodItem menu[5] = {
    {1, "Burger", 5.99},
    {2, "Pizza", 8.99},
    {3, "Pasta", 7.49},
    {4, "Salad", 4.99},
    {5, "Drink", 1.99}
};
void displayOrdersForTable(OrderNode* head, int tableNumber) {
    int currentOrderNumber = -1;
    OrderNode* temp = head;
        printf("\033[0;32m"); 

    printf("**************\n");
    printf("Orders for Table %d:\n", tableNumber);
    printf("**************\n");
        printf("\033[0;0m"); 

    while (head != NULL) {
        if (head->tableNumber == tableNumber && head->orderNumber != currentOrderNumber) {
            printf("** Order %d **\n", head->orderNumber);
            printf("Item: %s (%d)\n", menu[head->menuNumber - 1].itemName, head->menuNumber);
            printf("Quantity: %d\n", head->quantity);
            currentOrderNumber = head->orderNumber;
        }
        head = head->next;
    }

    printf("**************\n");
}

void displayTables(TableNode* head, OrderQueue* orderQueue) {
    printf("Table Status:\n");
    while (head != NULL) {
        printf("Table %d: ", head->tableNumber);
        if (head->status == 0) {
            printf("Vacant\n");
        } else if (head->status == 1) {
            printf("Reserved (Time Slot: %d)\n", head->reservationTimeSlot);
        } else {
            printf("Occupied\n");
        }

        head = head->next;
    }
}


void displayOrderNumbers(OrderNode* head) {
        printf("\033[0;32m"); 

    printf("\n********************\n");
    printf("          Order Numbers\n");
    printf("******************\n");

        printf("\033[0;0m"); 

    if (head == NULL) {
        printf("No orders available.\n");
    } else {
        printf("%-10s%-10s%-25s%-10s%-10s\n", "Order No", "Table No", "Item", "Quantity", "Price");
        printf("----------------------------------------------------\n");

        int orderNumber = 1;
        while (head != NULL) {
            printf("%-10d%-10d%-25s%-10d$%-10.2f\n", orderNumber++, head->tableNumber,
                   menu[head->menuNumber - 1].itemName, head->quantity,
                   menu[head->menuNumber - 1].itemPrice * head->quantity);

            head = head->next;
        }
    }

    printf("******************\n");
}




void displayMenu() {
        printf("\033[0;32m"); 

    printf("\n**************\n");
    printf("                 Food Menu\n");
    printf("**************\n");
        printf("\033[0;0m"); 

    printf("%-5s%-20s%-10s\n", "Menu #", "Item", "Price");
    printf("--------------------------------------\n");
    
    for (int i = 0; i < 5; ++i) {
        printf("%-5d%-20s$%-10.2f\n", menu[i].itemNumber, menu[i].itemName, menu[i].itemPrice);
    }

    printf("**************\n");
    printf("6. Exit\n");
}
void displayTimeSlots() {
        printf("\033[0;32m"); 

    printf("\n**************\n");
    printf(" Available Time Slots for Reservation\n");
    printf("**************\n");
        printf("\033[0;0m"); 

    printf("%-5s%-22s\n", "Slot #", "Time");
    printf("--------------------------------------\n");
    printf("%-5d%-22s\n", 1, "12:00 PM - 1:00 PM");
    printf("%-5d%-22s\n", 2, "1:00 PM - 2:00 PM");
    printf("%-5d%-22s\n", 3, "6:00 PM - 7:00 PM");
    printf("%-5d%-22s\n", 4, "7:00 PM - 8:00 PM");
    printf("%-5d%-22s\n", 5, "8:00 PM - 9:00 PM");
    printf("**************\n");
}
const char* getTimeSlotDescription(int timeSlot) {
    switch (timeSlot) {
        case 1:
            return "12:00 PM - 1:00 PM";
        case 2:
            return "1:00 PM - 2:00 PM";
        case 3:
            return "6:00 PM - 7:00 PM";
        case 4:
            return "7:00 PM - 8:00 PM";
        case 5:
            return "8:00 PM - 9:00 PM";
        default:
            return "Invalid Time Slot";
    }
}


void reserveTable(TableNode* table, int tableNumber, OrderQueue* orderQueue) {
    if (table->status == 1 && table->reservationTimeSlot == 5) {
        printf("Table %d has already reached the maximum number of reservations (5).\n", tableNumber);
        return;
    }

    if (table->status == 1) {
        printf("Table %d is already reserved for Time Slot %d.\n", tableNumber, table->reservationTimeSlot);
        printf("Choose a different time slot.\n");
        return;
    }

    int remainingSlots = 5 - table->reservationTimeSlot;

    printf("Remaining Time Slots for Table %d:\n", tableNumber);

    for (int i = 1; i <= remainingSlots; ++i) {
        printf("%d. %s\n", i, getTimeSlotDescription(table->reservationTimeSlot + i));
    }

    int timeSlotChoice;

    printf("Enter the number corresponding to the desired time slot: ");
    scanf("%d", &timeSlotChoice);

    if (timeSlotChoice < 1 || timeSlotChoice > remainingSlots) {
        printf("Invalid time slot choice. Please enter a number between 1 and %d.\n", remainingSlots);
        return;
    }

    table->status = 1;
    table->reservationTimeSlot += timeSlotChoice;

    printf("Table %d has been reserved for Time Slot %d (%s).\n", tableNumber, table->reservationTimeSlot, getTimeSlotDescription(table->reservationTimeSlot));

    int orderNumber = 1;
    int orderChoice;

    do {
        displayMenu();
        printf("Enter the menu number to order (1-5) or 6 to exit: ");
        scanf("%d", &orderChoice);

        if (orderChoice >= 1 && orderChoice <= 5) {
            int quantity;

            do {
                printf("Enter the quantity (1-100): ");
                scanf("%d", &quantity);

                if (quantity < 1 || quantity > 100) {
                    printf("Invalid quantity. Please enter a quantity between 1 and 100.\n");
                }

            } while (quantity < 1 || quantity > 100);

            printf("Ordered %d %s(s) for Table %d.\n", quantity, menu[orderChoice - 1].itemName, tableNumber);
            enqueueOrder(orderQueue, orderNumber++, tableNumber, orderChoice, quantity);

        } else if (orderChoice != 6) {
            printf("Invalid menu number. Please enter a number between 1 and 5, or 6 to exit.\n");
        }

    } while (orderChoice != 6);
}


void generateBillForTable(OrderNode* head, int tableNumber) {
    double totalAmount = 0.0;

        printf("\033[0;32m"); 

    printf("\n**************\n");
    printf("Bill for Table %d:\n", tableNumber);
    printf("**************\n");
        printf("\033[0;0m"); 


    printf("%-15s %-10s %-10s %-10s\n", "Item", "Menu #", "Quantity", "Subtotal");
    printf("--------------------------------------\n");

    while (head != NULL) {
        if (head->tableNumber == tableNumber) {
            double itemPrice = menu[head->menuNumber - 1].itemPrice;
            double subtotal = itemPrice * head->quantity;

            printf("%-15s %-10d %-10d $%-10.2f\n", menu[head->menuNumber - 1].itemName, head->menuNumber, head->quantity, subtotal);
            totalAmount += subtotal;
        }
        head = head->next;
    }

    printf("**************\n");
    printf("Total Amount for Table %d: $%-10.2f\n", tableNumber, totalAmount);
    printf("**************\n");
}



char Fb[10][100];
int n=-1;

void giveFeedback() {
    char feedback[100];
    printf("\nEnter your feedback (max 100 characters):\n");
    scanf(" %[^\n]", feedback);
    strcpy(Fb[++n],feedback);
    printf("Thank you for your feedback!\n");
}
void displayFeedback() {
        printf("\033[0;32m"); 

    printf("\n**************\n");
    printf("            Customer Feedbacks\n");
    printf("**************\n");

        printf("\033[0;0m"); 

    if (n == -1) {
        printf("\033[0;31m"); 

        printf("No feedback available.\n");
        printf("\033[0;0m"); 

    } else {
        printf("%-5s%-100s\n", "S. No", "Feedback");
        printf("--------------------------------------\n");

        for (int i = 0; i <= n; i++) {
            printf("%-5d%-100s\n", i + 1, Fb[i]);
        }
    }

    printf("**************\n");
}


int main() {
    TableNode* tables = NULL;
    for (int i = 10; i >= 1; --i) {
        TableNode* newNode = (TableNode*)malloc(sizeof(TableNode));
        newNode->tableNumber = i;
        newNode->status = 0;
        newNode->reservationTimeSlot = 0;
        newNode->next = tables;
        tables = newNode;
    }

    Queue reservedQueue;
    initializeQueue(&reservedQueue);

    FoodItem menu[5] = {
        {1, "Burger", 5.99},
        {2, "Pizza", 8.99},
        {3, "Pasta", 7.49},
        {4, "Salad", 4.99},
        {5, "Drink", 1.99}
    };

    OrderQueue orderQueue;
    initializeOrderQueue(&orderQueue);
    printf("\033[0;33m"); 
        printf("\n\n*************\n\tRestaurant System\n*************\n");
        printf("\033[0;m"); 

    int choice;
    do {
        printf("\033[0;32m"); 
        printf("\t  Main Menu\n");
        printf("\033[0;m"); 

        printf("1. Display Tables\n");
        printf("2. Display Order Numbers\n");
        printf("3. Reserve or Occupy Table\n");
        printf("4. Display Orders for a Table\n");
        printf("5. Generate bill\n");
        printf("6. Feedback\n");
        printf("7. Display all Feedbacks\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayTables(tables, &orderQueue);
                break;

            case 2:
                displayOrderNumbers(orderQueue.front);
                break;

            case 3:
                printf("\033[0;33Sm"); 
                printf("Enter the table number (1-10) to reserve or occupy (0 to exit): ");
                printf("\033[0;0m"); 

                scanf("%d", &choice);

                if (choice >= 1 && choice <= 10) {
                    TableNode* current = tables;
                    while (current != NULL && current->tableNumber != choice) {
                        current = current->next;
                    }

                    if (current != NULL) {
                        if (current->status == 0) {
                            int tableChoice;
                            printf("Do you want to:\n");
                            printf("1. Reserve the table\n");
                            printf("2. Occupy the table\n");
                            printf("\033[0;32m"); 

                            printf("Enter your choice: ");
                            printf("\033[0;0m"); 

                            scanf("%d", &tableChoice);

                            if (tableChoice == 1) {
                                reserveTable(current, choice, &orderQueue);
                            } else if (tableChoice == 2) {
                                current->status = 2;
                                printf("Table %d has been occupied.\n", choice);

                                int orderNumber = 1;
                                int orderChoice;
                                do {
                                    displayMenu();

                                    printf("Enter the menu number to order (1-5) or 6 to exit: ");
                                    scanf("%d", &orderChoice);
                                    if (orderChoice >= 1 && orderChoice <= 5) {
                                        int quantity;
                                        printf("Enter the quantity: ");
                                        scanf("%d", &quantity);

                                         if ((quantity >= 1) && (quantity <= 100)) {
                                            printf("Ordered %d %s(s) for Table %d.\n", quantity, menu[orderChoice - 1].itemName, choice);
                                            enqueueOrder(&orderQueue, orderNumber++, choice, orderChoice, quantity);
                                        }
                                        else{
                                            while(!((quantity >= 1) && (quantity <= 100))){
                                                printf("please enter valid input\n");
                                                scanf("%d", &quantity);
                                            }
                                            printf("Ordered %d %s(s) for Table %d.\n", quantity, menu[orderChoice - 1].itemName, choice);
                                            enqueueOrder(&orderQueue, orderNumber++, choice, orderChoice, quantity);
                                        }
                                       

                                    } else if (orderChoice != 6) {
                                        printf("Invalid menu number. Please enter a number between 1 and 5, or 6 to exit.\n");
                                    }
                                } while (orderChoice != 6);
                            } else {
                                printf("Invalid choice. Please enter 1 or 2.\n");
                            }
                        } else {
                            printf("Table %d is not available.\n", choice);
                        }
                    }
                } else if (choice != 0) {
                    printf("Invalid input. Please enter a number between 1 and 10, or 0 to exit.\n");
                }
                break;

            case 4:
                printf("Enter the table number (1-10) to display orders (0 to exit): ");
                scanf("%d", &choice);

                if (choice >= 1 && choice <= 10) {
                    displayOrdersForTable(orderQueue.front, choice);
                } else if (choice != 0) {
                    printf("Invalid input. Please enter a number between 1 and 10, or 0 to exit.\n");
                }
                break;
                
            case 5:
                printf("Enter the table number (1-10) to generate bill (0 to exit): ");
                scanf("%d", &choice);

                if (choice >= 1 && choice <= 10) {
                 generateBillForTable(orderQueue.front, choice);
               } else if (choice != 0) {
               printf("Invalid input. Please enter a number between 1 and 10, or 0 to exit.\n");
               }
             break;

           case 6:
                giveFeedback();
                break;
            case 7:
                displayFeedback();
                break;
            case 0:
                break;

            default:
                printf("Invalid choice. Please enter a number between 0 and 4.\n");
        }

    } while (choice != 0);

    TableNode* currentTable = tables;
    while (currentTable != NULL) {
        TableNode* nextTable = currentTable->next;
        free(currentTable);
        currentTable = nextTable;
    }

    OrderNode* currentOrder = orderQueue.front;
    while (currentOrder != NULL) {
        OrderNode* nextOrder = currentOrder->next;
        free(currentOrder);
        currentOrder = nextOrder;
    }

    printf("Program exited.\n");
    return  0;
}
