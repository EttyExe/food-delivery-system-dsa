#include <iostream>
#include <string>
using namespace std;

// ================= ORDER STRUCTURE =================

struct Order
{
    int orderID;
    string customerName;
    string foodItem;
    string status;
    string riderName;
};

// ================= QUEUE =================

const int MAX_ORDERS = 100;

Order orderQueue[MAX_ORDERS];
int frontQ = 0;
int rearQ = -1;
int orderCount = 0;
int nextOrderID = 1001;

void placeOrder()
{
    if (rearQ == MAX_ORDERS - 1)
    {
        cout << "\nQueue Full!\n";
        return;
    }

    Order newOrder;

    newOrder.orderID = nextOrderID++;

    cout << "\nEnter Customer Name: ";
    cin.ignore();
    getline(cin, newOrder.customerName);

    cout << "Enter Food Item: ";
    getline(cin, newOrder.foodItem);

    newOrder.status = "Pending";
    newOrder.riderName = "Not Assigned";

    rearQ++;
    orderQueue[rearQ] = newOrder;
    orderCount++;

    cout << "\nOrder Placed Successfully!";
    cout << "\nOrder ID: " << newOrder.orderID << endl;
}

// ================= STACK =================

Order deliveryHistory[MAX_ORDERS];
int topStack = -1;

void pushHistory(Order order)
{
    if (topStack < MAX_ORDERS - 1)
    {
        topStack++;
        deliveryHistory[topStack] = order;
    }
}

void viewDeliveryHistory()
{
    if (topStack == -1)
    {
        cout << "\nNo Delivered Orders Found!\n";
        return;
    }

    cout << "\n===== DELIVERY HISTORY =====\n";

    for (int i = topStack; i >= 0; i--)
    {
        cout << "\nOrder ID: "
             << deliveryHistory[i].orderID
             << "\nCustomer: "
             << deliveryHistory[i].customerName
             << "\nFood: "
             << deliveryHistory[i].foodItem
             << "\nStatus: "
             << deliveryHistory[i].status
             << endl;
    }
}

// ================= LINKED LIST =================

struct Rider
{
    int riderID;
    string riderName;
    bool available;
    Rider *next;
};

Rider *head = NULL;
int nextRiderID = 1;

void addRider()
{
    Rider *newRider = new Rider();

    newRider->riderID = nextRiderID++;

    cout << "\nEnter Rider Name: ";
    cin.ignore();
    getline(cin, newRider->riderName);

    newRider->available = true;
    newRider->next = NULL;

    if (head == NULL)
    {
        head = newRider;
    }
    else
    {
        Rider *temp = head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newRider;
    }

    cout << "\nRider Added Successfully!\n";
}

void displayRiders()
{
    if (head == NULL)
    {
        cout << "\nNo Riders Available!\n";
        return;
    }

    Rider *temp = head;

    cout << "\n===== RIDERS =====\n";

    while (temp != NULL)
    {
        cout << "\nID: " << temp->riderID;
        cout << "\nName: " << temp->riderName;
        cout << "\nAvailable: "
             << (temp->available ? "Yes" : "No");
        cout << "\n-------------------\n";

        temp = temp->next;
    }
}

void removeRider()
{
    int id;

    cout << "\nEnter Rider ID: ";
    cin >> id;

    Rider *temp = head;
    Rider *prev = NULL;

    while (temp != NULL && temp->riderID != id)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        cout << "\nRider Not Found!\n";
        return;
    }

    if (prev == NULL)
    {
        head = head->next;
    }
    else
    {
        prev->next = temp->next;
    }

    delete temp;

    cout << "\nRider Removed Successfully!\n";
}

// ================= DISPLAY ORDERS =================

void viewAllOrders()
{
    if (orderCount == 0)
    {
        cout << "\nNo Orders Found!\n";
        return;
    }

    cout << "\n===== ALL ORDERS =====\n";

    for (int i = frontQ; i <= rearQ; i++)
    {
        cout << "\nOrder ID: " << orderQueue[i].orderID;
        cout << "\nCustomer: " << orderQueue[i].customerName;
        cout << "\nFood: " << orderQueue[i].foodItem;
        cout << "\nStatus: " << orderQueue[i].status;
        cout << "\nRider: " << orderQueue[i].riderName;
        cout << "\n---------------------\n";
    }
}

// ================= SEARCH ORDER =================

void searchOrder()
{
    int id;

    cout << "\nEnter Order ID: ";
    cin >> id;

    for (int i = frontQ; i <= rearQ; i++)
    {
        if (orderQueue[i].orderID == id)
        {
            cout << "\nOrder Found!\n";

            cout << "Customer: "
                 << orderQueue[i].customerName
                 << endl;

            cout << "Food: "
                 << orderQueue[i].foodItem
                 << endl;

            cout << "Status: "
                 << orderQueue[i].status
                 << endl;

            return;
        }
    }

    cout << "\nOrder Not Found!\n";
}

// ================= SEARCH RIDER =================

void searchRider()
{
    int id;

    cout << "\nEnter Rider ID: ";
    cin >> id;

    Rider *temp = head;

    while (temp != NULL)
    {
        if (temp->riderID == id)
        {
            cout << "\nRider Found!\n";
            cout << "Name: " << temp->riderName << endl;
            return;
        }

        temp = temp->next;
    }

    cout << "\nRider Not Found!\n";
}

// ================= ASSIGN RIDER =================

void assignRider()
{
    int orderID;
    int riderID;

    cout << "\nEnter Order ID: ";
    cin >> orderID;

    cout << "Enter Rider ID: ";
    cin >> riderID;

    Rider *temp = head;

    while (temp != NULL)
    {
        if (temp->riderID == riderID)
            break;

        temp = temp->next;
    }

    if (temp == NULL)
    {
        cout << "\nRider Not Found!\n";
        return;
    }

    for (int i = frontQ; i <= rearQ; i++)
    {
        if (orderQueue[i].orderID == orderID)
        {
            orderQueue[i].riderName = temp->riderName;
            temp->available = false;

            cout << "\nRider Assigned Successfully!\n";
            return;
        }
    }

    cout << "\nOrder Not Found!\n";
}

// ================= UPDATE STATUS =================

void updateStatus()
{
    int id;

    cout << "\nEnter Order ID: ";
    cin >> id;

    for (int i = frontQ; i <= rearQ; i++)
    {
        if (orderQueue[i].orderID == id)
        {
            cout << "\n1. Preparing";
            cout << "\n2. Picked Up";
            cout << "\n3. Out For Delivery";
            cout << "\n4. Delivered";

            int choice;
            cout << "\nChoose Status: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                orderQueue[i].status = "Preparing";
                break;

            case 2:
                orderQueue[i].status = "Picked Up";
                break;

            case 3:
                orderQueue[i].status = "Out For Delivery";
                break;

            case 4:
                orderQueue[i].status = "Delivered";
                pushHistory(orderQueue[i]);
                break;

            default:
                cout << "\nInvalid Choice!";
                return;
            }

            cout << "\nStatus Updated!\n";
            return;
        }
    }

    cout << "\nOrder Not Found!\n";
}

// ================= CANCEL ORDER =================

void cancelOrder()
{
    int id;

    cout << "\nEnter Order ID: ";
    cin >> id;

    for (int i = frontQ; i <= rearQ; i++)
    {
        if (orderQueue[i].orderID == id)
        {
            orderQueue[i].status = "Cancelled";

            cout << "\nOrder Cancelled!\n";
            return;
        }
    }

    cout << "\nOrder Not Found!\n";
}

// ================= SORT ORDERS =================

void sortOrders()
{
    for (int i = frontQ; i < rearQ; i++)
    {
        for (int j = frontQ; j < rearQ - (i - frontQ); j++)
        {
            if (orderQueue[j].orderID >
                orderQueue[j + 1].orderID)
            {
                swap(orderQueue[j],
                     orderQueue[j + 1]);
            }
        }
    }

    cout << "\nOrders Sorted Successfully!\n";
}

// ================= MAIN =================

int main()
{
    int choice;

    do
    {
        cout << "\n\n========== FOOD DELIVERY SYSTEM ==========\n";
        cout << "1. Place Order\n";
        cout << "2. View All Orders\n";
        cout << "3. Search Order\n";
        cout << "4. Cancel Order\n";
        cout << "5. Add Rider\n";
        cout << "6. Remove Rider\n";
        cout << "7. Display Riders\n";
        cout << "8. Search Rider\n";
        cout << "9. Assign Rider\n";
        cout << "10. Update Delivery Status\n";
        cout << "11. View Delivery History\n";
        cout << "12. Sort Orders\n";
        cout << "13. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            placeOrder();
            break;

        case 2:
            viewAllOrders();
            break;

        case 3:
            searchOrder();
            break;

        case 4:
            cancelOrder();
            break;

        case 5:
            addRider();
            break;

        case 6:
            removeRider();
            break;

        case 7:
            displayRiders();
            break;

        case 8:
            searchRider();
            break;

        case 9:
            assignRider();
            break;

        case 10:
            updateStatus();
            break;

        case 11:
            viewDeliveryHistory();
            break;

        case 12:
            sortOrders();
            break;

        case 13:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 13);

    return 0;
}