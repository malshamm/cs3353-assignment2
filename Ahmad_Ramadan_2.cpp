/* Assignment #2, Ahmad Ramadan */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct SLLNode {
    string ip;
    SLLNode* next;
    
    SLLNode(string value) {
        ip = value;
        next = nullptr;
    }
};

class SLL {
private:
    SLLNode* head;
    SLLNode* tail;

public:
    SLL() {
        head = nullptr;
        tail = nullptr;
    }

    void insertHead(string ip) {
        SLLNode* newNode = new SLLNode(ip);
        newNode->next = head;
        head = newNode;
        if (tail == nullptr) {
            tail = head;
        }
    }

    void insertTail(string ip) {
        SLLNode* newNode = new SLLNode(ip);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void deleteHead() {
        if (head == nullptr) {
            cout << "Error: The list is empty!" << endl;
            return;
        }
        SLLNode* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) {
            tail = nullptr;
        }
    }

    void deleteTail() {
        if (head == nullptr) {
            cout << "Error: The list is empty!" << endl;
            return;
        }
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            return;
        }
        SLLNode* curr = head;
        while (curr->next != tail) {
            curr = curr->next;
        }
        delete tail;
        tail = curr;
        tail->next = nullptr;
    }

    void searchAndDelete(string targetIP) {
        if (head == nullptr) {
            cout << "Error: The list is empty!" << endl;
            return;
        }
        
        // If the target is the head
        if (head->ip == targetIP) {
            deleteHead();
            return;
        }

        SLLNode* curr = head;
        while (curr->next != nullptr && curr->next->ip != targetIP) {
            curr = curr->next;
        }

        if (curr->next != nullptr) {
            SLLNode* temp = curr->next;
            curr->next = temp->next;
            if (temp == tail) {
                tail = curr;
            }
            delete temp;
        } else {
            cout << "There is no such node in the list!" << endl;
        }
    }

    void printList() {
        SLLNode* curr = head;
        while (curr != nullptr) {
            cout << curr->ip << " ";
            curr = curr->next;
        }
        cout << endl;
    }
};


struct DLLNode {
    string ip;
    DLLNode* prev;
    DLLNode* next;
    
    DLLNode(string value) {
        ip = value;
        prev = nullptr;
        next = nullptr;
    }
};

class DLL {
private:
    DLLNode* head;
    DLLNode* tail;

public:
    DLL() {
        head = nullptr;
        tail = nullptr;
    }

    void insertHead(string ip) {
        DLLNode* newNode = new DLLNode(ip);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insertTail(string ip) {
        DLLNode* newNode = new DLLNode(ip);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void deleteHead() {
        if (head == nullptr) {
            cout << "Error: The list is empty!" << endl;
            return;
        }
        DLLNode* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
    }

    void deleteTail() {
        if (tail == nullptr) {
            cout << "Error: The list is empty!" << endl;
            return;
        }
        DLLNode* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
    }

    void searchAndDelete(string targetIP) {
        if (head == nullptr) {
            cout << "Error: The list is empty!" << endl;
            return;
        }

        DLLNode* curr = head;
        while (curr != nullptr && curr->ip != targetIP) {
            curr = curr->next;
        }

        if (curr != nullptr) {
            if (curr == head) {
                deleteHead();
            } else if (curr == tail) {
                deleteTail();
            } else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                delete curr;
            }
        } else {
            cout << "There is no such node in the list!" << endl;
        }
    }

    void printList() {
        DLLNode* curr = head;
        while (curr != nullptr) {
            cout << curr->ip << " ";
            curr = curr->next;
        }
        cout << endl;
    }
};



int main() {
    ifstream logFile("Apache_Logs.txt");
    if (!logFile.is_open()) {
        cout << "Error: Could not open Apache_Logs.txt. Ensure the file is in the same directory." << endl;
        return 1;
    }

    SLL sll;
    DLL dll;
    int choice;
    string fileIp;

    while (true) {
        cout << "M E N U" << endl;
        cout << "SLL: IH(0), IT(1), DH(2), DT(3), SD(4), PS(5)" << endl;
        cout << "DLL: IH(6), IT(7), DH(8), DT(9), SD(10), PD(11)" << endl;
        cout << "Exit Program (12)" << endl;
        cout << "Choose? ";
        
        cin >> choice;

        if (choice == 12) {
            break;
        }

        // For insertion operations, we fetch the next IP address from the file
        if (choice == 0 || choice == 1 || choice == 6 || choice == 7) {
            if (logFile >> fileIp) {
                string dummy;
                getline(logFile, dummy); // skip the rest of the line to position for the next IP
            } else {
                cout << "Error: End of file reached. No more IP addresses to read." << endl;
                continue;
            }
        }

        string searchIp;

        switch (choice) {
            // SLL Operations
            case 0:
                sll.insertHead(fileIp);
                break;
            case 1:
                sll.insertTail(fileIp);
                break;
            case 2:
                sll.deleteHead();
                break;
            case 3:
                sll.deleteTail();
                break;
            case 4:
                cin >> searchIp;
                sll.searchAndDelete(searchIp);
                break;
            case 5:
                sll.printList();
                break;
                
            // DLL Operations
            case 6:
                dll.insertHead(fileIp);
                break;
            case 7:
                dll.insertTail(fileIp);
                break;
            case 8:
                dll.deleteHead();
                break;
            case 9:
                dll.deleteTail();
                break;
            case 10:
                cin >> searchIp;
                dll.searchAndDelete(searchIp);
                break;
            case 11:
                dll.printList();
                break;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }

    logFile.close();
    return 0;
}