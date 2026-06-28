/* Assignment #3, Ahmad Ramadan */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// --- Node structure for Stack (Linked List) ---
struct Node {
    int data;
    Node* next;
};

// --- Stack Class Implemented via Linked List ---
class Stack {
private:
    Node* top;

public:
    Stack() {
        top = nullptr;
    }

    // Push function
    void push(int value) {
        Node* newNode = new Node{value, top};
        top = newNode;
    }

    // Pop function
    int pop() {
        if (isEmpty()) {
            return -1; // Stack underflow
        }
        int value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return value;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

// --- Helper Function: Extract first word (IP) from a log line ---
string extractIP(string line) {
    if (!line.empty() && line.back() == '\r') line.pop_back();
    stringstream ss(line);
    string ip;
    if (ss >> ip) return ip;
    return "";
}

// --- Helper Function: Convert decimal to specified base using Stack ---
string convertBase(int num, int base, int padLength) {
    if (num == 0) {
        string zeroStr = "";
        for (int i = 0; i < padLength; i++) zeroStr += "0";
        return zeroStr;
    }

    Stack s;
    // Repetitious division by the base
    while (num > 0) {
        s.push(num % base);
        num /= base;
    }

    string result = "";
    // Taking the remainders in reverse order
    while (!s.isEmpty()) {
        int val = s.pop();
        if (val < 10) {
            result += to_string(val);
        } else {
            // For Hexadecimal: 10 -> a, 11 -> b, etc.
            result += (char)('a' + (val - 10));
        }
    }

    // Pad with leading zeros to match assignment examples
    while (result.length() < padLength) {
        result = "0" + result;
    }

    return result;
}

// --- Main Program ---
int main() {
    ifstream file("Apache_Logs.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open Apache_Logs.txt" << endl;
        return 1;
    }

    int choice;
    string line;

    while (true) {
        cout << "MENU" << endl;
        cout << "Binary (0), Octal (1), Hexadecimal (2)" << endl;
        cout << "Exit Program (3)" << endl;
        cout << "Choose? ";
        cin >> choice;

        if (choice == 3) {
            break;
        }

        if (choice < 0 || choice > 3) {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        // Read the next line for each command chosen
        if (getline(file, line)) {
            // Skip short/empty lines
            if (line.length() < 5) continue;

            string ip = extractIP(line);
            
            // Parse the 4 parts of the IP address (separated by dots)
            stringstream ss(ip);
            string segment;
            int parts[4];
            int i = 0;
            
            while (getline(ss, segment, '.') && i < 4) {
                parts[i] = stoi(segment);
                i++;
            }

            int base = 2;
            int pad = 8;
            string type = "(binary)";

            if (choice == 1) {
                base = 8;
                pad = 4;
                type = "(octal)";
            } else if (choice == 2) {
                base = 16;
                pad = 2;
                type = "(hexadecimal)";
            }

            // Convert and print each part
            cout << ip << " -> ";
            cout << convertBase(parts[0], base, pad) << "."
                 << convertBase(parts[1], base, pad) << "."
                 << convertBase(parts[2], base, pad) << "."
                 << convertBase(parts[3], base, pad) << " " << type << endl;

        } else {
            cout << "No more log records available in the file." << endl;
            break;
        }
    }

    file.close();
    return 0;
}