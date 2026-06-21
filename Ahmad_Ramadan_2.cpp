/* Assignment #2, Ahmad Ramadan */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct NodeSLL {
    string ip;
    NodeSLL* next;
};

struct NodeDLL {
    string ip;
    NodeDLL* prev;
    NodeDLL* next;
};

NodeSLL* sllHead = nullptr;

NodeDLL* dllHead = nullptr;
NodeDLL* dllTail = nullptr;

string extractIP(string line) {
    return line.substr(0, line.find(' '));
}

void SLL_InsertHead(string ip) {
    NodeSLL* newNode = new NodeSLL{ip, sllHead};
    sllHead = newNode;
}

void SLL_InsertTail(string ip) {
    NodeSLL* newNode = new NodeSLL{ip, nullptr};
    if (!sllHead) { sllHead = newNode; return; }
    NodeSLL* temp = sllHead;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
}

void SLL_DeleteHead() {
    if (!sllHead) { cout << "Empty list!" << endl; return; }
    NodeSLL* temp = sllHead;
    sllHead = sllHead->next;
    delete temp;
}

void SLL_DeleteTail() {
    if (!sllHead) { cout << "Empty list!" << endl; return; }
    if (!sllHead->next) { delete sllHead; sllHead = nullptr; return; }
    NodeSLL* temp = sllHead;
    while (temp->next->next) temp = temp->next;
    delete temp->next;
    temp->next = nullptr;
}

void SLL_SearchDelete(string ip) {
    if (!sllHead) { cout << "Empty list!" << endl; return; }
    if (sllHead->ip == ip) { SLL_DeleteHead(); return; }
    NodeSLL* temp = sllHead;
    while (temp->next && temp->next->ip != ip) temp = temp->next;
    if (temp->next) {
        NodeSLL* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
    } else {
        cout << "There is no such node in the list!" << endl;
    }
}

void SLL_Print() {
    NodeSLL* temp = sllHead;
    while (temp) {
        cout << temp->ip << " ";
        temp = temp->next;
    }
    cout << endl;
}

void DLL_InsertHead(string ip) {
    NodeDLL* newNode = new NodeDLL{ip, nullptr, dllHead};
    if (dllHead) dllHead->prev = newNode;
    else dllTail = newNode;
    dllHead = newNode;
}

void DLL_InsertTail(string ip) {
    NodeDLL* newNode = new NodeDLL{ip, dllTail, nullptr};
    if (dllTail) dllTail->next = newNode;
    else dllHead = newNode;
    dllTail = newNode;
}

void DLL_DeleteHead() {
    if (!dllHead) { cout << "Empty list!" << endl; return; }
    NodeDLL* temp = dllHead;
    dllHead = dllHead->next;
    if (dllHead) dllHead->prev = nullptr;
    else dllTail = nullptr;
    delete temp;
}

void DLL_DeleteTail() {
    if (!dllTail) { cout << "Empty list!" << endl; return; }
    NodeDLL* temp = dllTail;
    dllTail = dllTail->prev;
    if (dllTail) dllTail->next = nullptr;
    else dllHead = nullptr;
    delete temp;
}

void DLL_SearchDelete(string ip) {
    NodeDLL* temp = dllHead;
    while (temp && temp->ip != ip) temp = temp->next;
    if (!temp) { cout << "There is no such node in the list!" << endl; return; }
    if (temp == dllHead) DLL_DeleteHead();
    else if (temp == dllTail) DLL_DeleteTail();
    else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
    }
}

void DLL_Print() {
    NodeDLL* temp = dllHead;
    while (temp) {
        cout << temp->ip << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    ifstream file("Apache_Logs.txt");
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.empty()) continue;
            string ip = extractIP(line);
            SLL_InsertTail(ip);
            DLL_InsertTail(ip);
        }
        file.close();
    }

    int choice;
    string ip;
    while (true) {
        cout << "M E N U" << endl;
        cout << "SLL: IH(0), IT(1), DH(2), DT(3), SD(4), PS(5)" << endl;
        cout << "DLL: IH(6), IT(7), DH(8), DT(9), SD(10), PD(11)" << endl;
        cout << "Exit Program (12)" << endl;
        cout << "Choose? ";
        cin >> choice;

        if (choice == 12) break;
        if (choice >= 4 && choice <= 10 && choice != 5 && choice != 6 && choice != 9) cin >> ip;

        switch (choice) {
            case 0: cout << "Enter IP: "; cin >> ip; SLL_InsertHead(ip); break;
            case 1: cout << "Enter IP: "; cin >> ip; SLL_InsertTail(ip); break;
            case 2: SLL_DeleteHead(); break;
            case 3: SLL_DeleteTail(); break;
            case 4: SLL_SearchDelete(ip); break;
            case 5: SLL_Print(); break;
            case 6: cout << "Enter IP: "; cin >> ip; DLL_InsertHead(ip); break;
            case 7: cout << "Enter IP: "; cin >> ip; DLL_InsertTail(ip); break;
            case 8: DLL_DeleteHead(); break;
            case 9: DLL_DeleteTail(); break;
            case 10: DLL_SearchDelete(ip); break;
            case 11: DLL_Print(); break;
        }
    }
    return 0;
}
