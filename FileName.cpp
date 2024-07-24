#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    Node* next;
    char VIPorNot;
    int arrivalTH, arrivalTM, arrivalTS;
    int departureTH, departureTM, departureTS;
    string vehicleName, vehicleNumber, vehicleDriverName;
    int fees;

    Node() : next(nullptr), VIPorNot('n'), arrivalTH(0), arrivalTM(0), arrivalTS(0), 
             departureTH(0), departureTM(0), departureTS(0), fees(0) {}
};

class LinkedListAndQueue {
    Node* front;
    Node* rear;

public:
    LinkedListAndQueue() : front(nullptr), rear(nullptr) {}

    bool isEmpty() const {
        return front == nullptr;
    }

    bool checkIfNodeExist(const string& vehicleNumber) const {
        for (auto temp = front; temp != nullptr; temp = temp->next) {
            if (temp->vehicleNumber == vehicleNumber) {
                return true;
            }
        }
        return false;
    }

    void enqueue(Node* n) {
        if (isEmpty()) {
            front = rear = n;
            cout << " *** Record Enqueued successfully ***" << endl;
        } else if (checkIfNodeExist(n->vehicleNumber)) {
            cout << " ***Record already exists with this vehicle number. ***" 
                 << " *** Enter a different vehicle number ***" << endl;
        } else {
            rear->next = n;
            rear = n;
            cout << "*** Record enqueued successfully ***" << endl;
        }
    }

    Node* dequeue() {
        if (isEmpty()) {
            cout << "QUEUE is Empty" << endl;
            return nullptr;
        }
        Node* temp = front;
        if (front == rear) {
            front = rear = nullptr;
        } else {
            front = front->next;
        }
        cout << "Successfully deleted" << endl;
        return temp;
    }

    int count() const {
        int count = 0;
        for (auto temp = front; temp != nullptr; temp = temp->next) {
            count++;
        }
        return count;
    }

    void showRecordof(const string& val) const {
        if (isEmpty()) {
            cout << "QUEUE is Empty" << endl;
        } else {
            for (auto temp = front; temp != nullptr; temp = temp->next) {
                if (temp->vehicleNumber == val) {
                    displayNode(temp);
                }
            }
        }
    }

    void showAllRecordUsingLinkedlist() const {
        if (isEmpty()) {
            cout << "queue is Empty" << endl;
        } else {
            for (auto temp = front; temp != nullptr; temp = temp->next) {
                displayNode(temp);
            }
        }
    }

    int fee(char VIPorNot, int arrivalTH, int arrivalTM, int arrivalTS, 
            int departureTH, int departureTM, int departureTS) const {
        int totalTH = departureTH - arrivalTH;
        int totalTM = departureTM - arrivalTM;
        int totalTS = departureTS - arrivalTS;
        if (totalTH > 2 || (totalTH == 2 && totalTM > 30)) {
            return (VIPorNot == 'y') ? 20 * totalTH : 25 * totalTH;
        } else {
            return (VIPorNot == 'y') ? 10 * totalTH : 15 * totalTH;
        }
    }

    void EnterVehicleRecord() {
        auto newNode = new Node();
        cout << "Enter vehicle name: ";
        cin >> newNode->vehicleName;
        cout << "Enter vehicle Driver name: ";
        cin >> newNode->vehicleDriverName;
        cout << "Enter vehicle Number: ";
        cin >> newNode->vehicleNumber;
        cout << "Enter arrival Hours of vehicle: ";
        cin >> newNode->arrivalTH;
        cout << "Enter arrival minutes of vehicle: ";
        cin >> newNode->arrivalTM;
        cout << "Enter arrival seconds of vehicle: ";
        cin >> newNode->arrivalTS;
        cout << "Enter departure Hours of vehicle: ";
        cin >> newNode->departureTH;
        cout << "Enter departure minutes of vehicle: ";
        cin >> newNode->departureTM;
        cout << "Enter departure seconds of vehicle: ";
        cin >> newNode->departureTS;
        cout << "VIP person y/n: ";
        cin >> newNode->VIPorNot;
        newNode->fees = fee(newNode->VIPorNot, newNode->arrivalTH, newNode->arrivalTM, newNode->arrivalTS,
                            newNode->departureTH, newNode->departureTM, newNode->departureTS);
        enqueue(newNode);
    }

private:
    void displayNode(Node* node) const {
        cout << endl << "*** Vehicle Number ***" << endl;
        cout << "\t" << node->vehicleNumber << endl;
        cout << "*** Vehicle Driver Name ***" << endl;
        cout << "\t" << node->vehicleDriverName << endl;
        cout << "*** Vehicle Name ***" << endl;
        cout << "\t" << node->vehicleName << endl;
        cout << "*** Departure time: ***" << endl;
        cout << "\t" << node->departureTH << ":" << node->departureTM << ":" << node->departureTS << endl;
        cout << "*** Arrival Time: ***" << endl;
        cout << "\t" << node->arrivalTH << ":" << node->arrivalTM << ":" << node->arrivalTS << endl;
        cout << "*** Fees ***" << endl;
        cout << "\t" << node->fees << endl;
    }
};

class NodeForBST {
public:
    char VIPorNot;
    int arrivalTH, arrivalTM, arrivalTS;
    int departureTH, departureTM, departureTS;
    string vehicleName, vehicleNumber, vehicleDriverName;
    int fees;
    int position;
    NodeForBST* left;
    NodeForBST* right;

    NodeForBST() : VIPorNot('n'), arrivalTH(0), arrivalTM(0), arrivalTS(0), 
                   departureTH(0), departureTM(0), departureTS(0), 
                   fees(0), position(0), left(nullptr), right(nullptr) {}
};

class BT {
private:
    NodeForBST* root;

    void insertNode(NodeForBST* new_node) {
        if (!root) {
            root = new_node;
            cout << "*** Record Inserted as root node! ***" << endl;
        } else {
            auto temp = root;
            while (temp) {
                if (new_node->position == temp->position) {
                    cout << "*** Record Already exists, Insert another record! ***" << endl;
                    return;
                } else if (new_node->position < temp->position) {
                    if (!temp->left) {
                        temp->left = new_node;
                        cout << "*** Record Inserted to the left! ***" << endl;
                        break;
                    }
                    temp = temp->left;
                } else {
                    if (!temp->right) {
                        temp->right = new_node;
                        cout << "*** Record Inserted to the right! ***" << endl;
                        break;
                    }
                    temp = temp->right;
                }
            }
        }
    }

    void inorder(NodeForBST* tree) const {
        if (!tree) return;
        inorder(tree->left);
        displayNode(tree);
        inorder(tree->right);
    }

public:
    BT() : root(nullptr) {}

    bool isEmpty() const {
        return root == nullptr;
    }

    int count(NodeForBST* r) const {
        if (!r) return 0;
        return count(r->left) + count(r->right) + 1;
    }

    void insert() {
        auto new_node = new NodeForBST();
        cout << "Enter vehicle name: ";
        cin >> new_node->vehicleName;
        cout << "Enter vehicle Driver name: ";
        cin >> new_node->vehicleDriverName;
        cout << "Enter vehicle Number: ";
        cin >> new_node->vehicleNumber;
        cout << "Enter arrival Hours of vehicle: ";
        cin >> new_node->arrivalTH;
        cout << "Enter arrival minutes of vehicle: ";
        cin >> new_node->arrivalTM;
        cout << "Enter arrival seconds of vehicle: ";
        cin >> new_node->arrivalTS;
        cout << "Enter departure Hours of vehicle: ";
        cin >> new_node->departureTH;
        cout << "Enter departure minutes of vehicle: ";
        cin >> new_node->departureTM;
        cout << "Enter departure seconds of vehicle: ";
        cin >> new_node->departureTS;
        cout << "VIP person y/n: ";
        cin >> new_node->VIPorNot;
        cout << "Enter Position: ";
        cin >> new_node->position;
        insertNode(new_node);
    }

    void display() const {
        inorder(root);
    }

    NodeForBST* getRoot() const {
        return root;
    }

private:
    void displayNode(NodeForBST* node) const {
        cout << endl << "*** Vehicle Number ***" << endl;
        cout << "\t" << node->vehicleNumber << endl;
        cout << "*** Vehicle Driver Name ***" << endl;
        cout << "\t" << node->vehicleDriverName << endl;
        cout << "*** Vehicle Name ***" << endl;
        cout << "\t" << node->vehicleName << endl;
        cout << "*** Departure time: ***" << endl;
        cout << "\t" << node->departureTH << ":" << node->departureTM << ":" << node->departureTS << endl;
        cout << "*** Arrival Time: ***" << endl;
        cout << "\t" << node->arrivalTH << ":" << node->arrivalTM << ":" << node->arrivalTS << endl;
        cout << "*** Fees ***" << endl;
        cout << "\t" << node->fees << endl;
    }
};

int main() {
    BT bst;
    LinkedListAndQueue obj;
    int option;

    do {
        cout << "\nWhat operation do you want to perform? "
             << "Select Option number. Enter 0 to exit." << endl;
        cout << "1. Enqueue" << endl;
        cout << "2. Dequeue" << endl;
        cout << "3. Check if empty" << endl;
        cout << "4. Count records" << endl;
        cout << "5. Show specific record" << endl;
        cout << "6. Show all records" << endl;
        cout << "7. Insert vehicle record in BST" << endl;
        cout << "8. Display BST records" << endl;
        cout << "0. Exit" << endl;
        cin >> option;

        switch (option) {
            case 0:
                cout << "Exiting..." << endl;
                break;
            case 1:
                obj.EnterVehicleRecord();
                break;
            case 2:
                delete obj.dequeue();
                break;
            case 3:
                cout << "Queue is " << (obj.isEmpty() ? "empty" : "not empty") << endl;
                break;
            case 4:
                cout << "Queue contains " << obj.count() << " records" << endl;
                break;
            case 5: {
                string vehicleNumber;
                cout << "Enter the vehicle number to search: ";
                cin >> vehicleNumber;
                obj.showRecordof(vehicleNumber);
                break;
            }
            case 6:
                obj.showAllRecordUsingLinkedlist();
                break;
            case 7:
                bst.insert();
                break;
            case 8:
                bst.display();
                break;
            default:
                cout << "Enter a proper option" << endl;
        }
    } while (option != 0);

    return 0;
}
