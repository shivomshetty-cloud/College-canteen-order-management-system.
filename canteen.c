#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FOOD 100

/* =========================
   STRUCTURES
   ========================= */

struct Food
{
    int id;
    char name[50];
    float price;
};

struct Order
{
    int orderId;
    char studentName[50];
    int foodId;
    char foodName[50];
    int quantity;
    float total;
};

/* Node for Queue / Linked List */
struct OrderNode
{
    struct Order data;
    struct OrderNode *next;
};

/* =========================
   GLOBAL VARIABLES
   ========================= */

struct Food menu[MAX_FOOD];
int foodCount = 0;

struct OrderNode *front = NULL;
struct OrderNode *rear = NULL;

int nextOrderId = 1;

/* =========================
   FUNCTION DECLARATIONS
   ========================= */

void addFood();
void displayMenu();
void searchFood();
void sortFoodByPrice();

void placeOrder();
void displayOrders();
void processNextOrder();
void cancelOrder();

struct Food *findFoodById(int id);

void clearInputBuffer();

/* =========================
   MAIN FUNCTION
   ========================= */

int main()
{
    int choice;

    /* Default food items */
    menu[foodCount++] = (struct Food){101, "Samosa", 15.00};
    menu[foodCount++] = (struct Food){102, "Burger", 50.00};
    menu[foodCount++] = (struct Food){103, "Chowmein", 60.00};
    menu[foodCount++] = (struct Food){104, "Tea", 10.00};
    menu[foodCount++] = (struct Food){105, "Cold Coffee", 40.00};

    do
    {
        printf("\n============================================\n");
        printf("       COLLEGE CANTEEN ORDER SYSTEM\n");
        printf("============================================\n");

        printf("\n------------- MENU OPERATIONS -------------\n");
        printf("1. Add Food Item\n");
        printf("2. Display Food Menu\n");
        printf("3. Search Food Item\n");
        printf("4. Sort Food Items by Price\n");

        printf("\n------------- ORDER OPERATIONS -------------\n");
        printf("5. Place Order\n");
        printf("6. Display All Orders\n");
        printf("7. Process Next Order\n");
        printf("8. Cancel Order\n");

        printf("\n9. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            addFood();
            break;

        case 2:
            displayMenu();
            break;

        case 3:
            searchFood();
            break;

        case 4:
            sortFoodByPrice();
            break;

        case 5:
            placeOrder();
            break;

        case 6:
            displayOrders();
            break;

        case 7:
            processNextOrder();
            break;

        case 8:
            cancelOrder();
            break;

        case 9:
            printf("\nThank you for using College Canteen Order System!\n");
            break;

        default:
            printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 9);

    return 0;
}

/* =========================
   CLEAR INPUT BUFFER
   ========================= */

void clearInputBuffer()
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* Clear input buffer */
    }
}

/* =========================
   ADD FOOD ITEM
   ========================= */

void addFood()
{
    if (foodCount >= MAX_FOOD)
    {
        printf("\nFood menu is full!\n");
        return;
    }

    struct Food newFood;

    printf("\n========== ADD FOOD ITEM ==========\n");

    printf("Enter Food ID: ");
    scanf("%d", &newFood.id);
    clearInputBuffer();

    /* Check duplicate ID */
    if (findFoodById(newFood.id) != NULL)
    {
        printf("\nFood ID already exists!\n");
        return;
    }

    printf("Enter Food Name: ");
    fgets(newFood.name, sizeof(newFood.name), stdin);
    newFood.name[strcspn(newFood.name, "\n")] = '\0';

    printf("Enter Food Price: ");
    scanf("%f", &newFood.price);
    clearInputBuffer();

    if (newFood.price <= 0)
    {
        printf("\nPrice must be greater than 0.\n");
        return;
    }

    menu[foodCount] = newFood;
    foodCount++;

    printf("\nFood item added successfully!\n");
}

/* =========================
   DISPLAY MENU
   ========================= */

void displayMenu()
{
    int i;

    if (foodCount == 0)
    {
        printf("\nNo food items available.\n");
        return;
    }

    printf("\n==================== CANTEEN MENU ====================\n");

    printf("%-10s %-25s %-10s\n", "ID", "FOOD ITEM", "PRICE");
    printf("-------------------------------------------------------\n");

    for (i = 0; i < foodCount; i++)
    {
        printf("%-10d %-25s Rs. %.2f\n",
               menu[i].id,
               menu[i].name,
               menu[i].price);
    }

    printf("=======================================================\n");
}

/* =========================
   SEARCH FOOD
   ========================= */

void searchFood()
{
    int id;
    struct Food *food;

    printf("\n========== SEARCH FOOD ==========\n");

    printf("Enter Food ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    food = findFoodById(id);

    if (food == NULL)
    {
        printf("\nFood item not found!\n");
        return;
    }

    printf("\nFood Found!\n");
    printf("-------------------------\n");
    printf("Food ID   : %d\n", food->id);
    printf("Food Name : %s\n", food->name);
    printf("Price     : Rs. %.2f\n", food->price);
}

/* =========================
   LINEAR SEARCH
   ========================= */

struct Food *findFoodById(int id)
{
    int i;

    for (i = 0; i < foodCount; i++)
    {
        if (menu[i].id == id)
        {
            return &menu[i];
        }
    }

    return NULL;
}

/* =========================
   BUBBLE SORT
   ========================= */

void sortFoodByPrice()
{
    int i, j;
    struct Food temp;

    if (foodCount < 2)
    {
        printf("\nNot enough food items to sort.\n");
        return;
    }

    for (i = 0; i < foodCount - 1; i++)
    {
        for (j = 0; j < foodCount - i - 1; j++)
        {
            if (menu[j].price > menu[j + 1].price)
            {
                temp = menu[j];
                menu[j] = menu[j + 1];
                menu[j + 1] = temp;
            }
        }
    }

    printf("\nFood items sorted by price successfully!\n");

    displayMenu();
}

/* =========================
   PLACE ORDER
   ========================= */

void placeOrder()
{
    struct Order newOrder;
    struct OrderNode *newNode;
    struct Food *food;

    printf("\n========== PLACE ORDER ==========\n");

    printf("Enter Student Name: ");
    fgets(newOrder.studentName,
          sizeof(newOrder.studentName),
          stdin);

    newOrder.studentName[
        strcspn(newOrder.studentName, "\n")
    ] = '\0';

    if (strlen(newOrder.studentName) == 0)
    {
        printf("\nStudent name cannot be empty.\n");
        return;
    }

    displayMenu();

    printf("\nEnter Food ID: ");
    scanf("%d", &newOrder.foodId);
    clearInputBuffer();

    food = findFoodById(newOrder.foodId);

    if (food == NULL)
    {
        printf("\nFood item not found!\n");
        return;
    }

    printf("Enter Quantity: ");
    scanf("%d", &newOrder.quantity);
    clearInputBuffer();

    if (newOrder.quantity <= 0)
    {
        printf("\nQuantity must be greater than 0.\n");
        return;
    }

    newOrder.orderId = nextOrderId++;

    strcpy(newOrder.foodName, food->name);

    newOrder.total =
        food->price * newOrder.quantity;

    /* Create new node */
    newNode =
        (struct OrderNode *)malloc(sizeof(struct OrderNode));

    if (newNode == NULL)
    {
        printf("\nMemory allocation failed!\n");
        return;
    }

    newNode->data = newOrder;
    newNode->next = NULL;

    /* Queue insertion */
    if (rear == NULL)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }

    printf("\n====================================\n");
    printf("          ORDER PLACED SUCCESSFULLY\n");
    printf("====================================\n");

    printf("Order ID     : %d\n", newOrder.orderId);
    printf("Student Name : %s\n", newOrder.studentName);
    printf("Food         : %s\n", newOrder.foodName);
    printf("Quantity     : %d\n", newOrder.quantity);
    printf("Total Amount : Rs. %.2f\n", newOrder.total);
    printf("Status       : Pending\n");
}

/* =========================
   DISPLAY ALL ORDERS
   ========================= */

void displayOrders()
{
    struct OrderNode *temp;

    if (front == NULL)
    {
        printf("\nNo pending orders.\n");
        return;
    }

    temp = front;

    printf("\n========================= PENDING ORDERS =========================\n");

    printf("%-8s %-20s %-20s %-8s %-12s\n",
           "ID",
           "STUDENT",
           "FOOD",
           "QTY",
           "TOTAL");

    printf("-------------------------------------------------------------------\n");

    while (temp != NULL)
    {
        printf("%-8d %-20s %-20s %-8d Rs. %-8.2f\n",
               temp->data.orderId,
               temp->data.studentName,
               temp->data.foodName,
               temp->data.quantity,
               temp->data.total);

        temp = temp->next;
    }

    printf("===================================================================\n");
}

/* =========================
   PROCESS NEXT ORDER
   ========================= */

void processNextOrder()
{
    struct OrderNode *temp;

    if (front == NULL)
    {
        printf("\nNo pending orders to process.\n");
        return;
    }

    temp = front;

    printf("\n========== PROCESSING ORDER ==========\n");

    printf("Order ID     : %d\n",
           temp->data.orderId);

    printf("Student Name : %s\n",
           temp->data.studentName);

    printf("Food         : %s\n",
           temp->data.foodName);

    printf("Quantity     : %d\n",
           temp->data.quantity);

    printf("Total Amount : Rs. %.2f\n",
           temp->data.total);

    printf("\nOrder processed successfully!\n");

    /* Move FRONT to next node */
    front = front->next;

    /* If queue becomes empty */
    if (front == NULL)
    {
        rear = NULL;
    }

    free(temp);
}

/* =========================
   CANCEL ORDER
   ========================= */

void cancelOrder()
{
    int orderId;
    struct OrderNode *temp;
    struct OrderNode *previous;

    if (front == NULL)
    {
        printf("\nNo orders available.\n");
        return;
    }

    printf("\n========== CANCEL ORDER ==========\n");

    printf("Enter Order ID to cancel: ");
    scanf("%d", &orderId);
    clearInputBuffer();

    temp = front;
    previous = NULL;

    /* Search order */
    while (temp != NULL &&
           temp->data.orderId != orderId)
    {
        previous = temp;
        temp = temp->next;
    }

    /* Order not found */
    if (temp == NULL)
    {
        printf("\nOrder ID %d not found!\n", orderId);
        return;
    }

    /* If first order */
    if (previous == NULL)
    {
        front = temp->next;
    }
    else
    {
        previous->next = temp->next;
    }

    /* If last order */
    if (temp == rear)
    {
        rear = previous;
    }

    printf("\nOrder cancelled successfully!\n");

    printf("Order ID : %d\n",
           temp->data.orderId);

    printf("Student  : %s\n",
           temp->data.studentName);

    free(temp);
}