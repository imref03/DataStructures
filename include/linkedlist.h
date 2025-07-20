#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H

#include <iostream>
#include <stdexcept>

using namespace std;

class LinkedList {
private:
    struct Node {
        int val;
        Node* next;
        Node () {
            val = 0;
            next = nullptr;
        }
        Node (int i) {
            val = i;
            next = nullptr;
        }
        Node (int i, Node* n) {
            val = i;
            next = n;
        }

    };  
    Node* head;
public:

    LinkedList () {
        head = nullptr;
    }
    ~LinkedList () {
        Node* current = head;
        while (current != nullptr) {
            Node* n = current->next;
            delete current;
            current = n;
        }
    }
    
    bool contains (int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->val == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void push_back (int value) {

        if (head == nullptr) {
            head = new Node(value);
            return;
        }

        Node* current = head;

        while (current->next != nullptr) {
            current = current->next;    
        }
        
        current->next = new Node(value);
    }

    void push_front (int value) {
        if (head == nullptr) {
            head = new Node(value);
            return;
        }
        head = new Node(value, head);
    }

    bool remove_key (int key) {
        if (head == nullptr) {
            return false;
        }

        Node* current = head;

        if (current->val == key) {
            if (current->next == nullptr) {
                delete head;
                head = nullptr;
            }
            else {
                Node* del = head;
                head = head->next;
                delete del;
            }
            return true;
        }

        while (current->next != nullptr) {
            if (current->next->val == key) {
                Node* del = current->next;
                current->next = del->next;
                delete del;
                return true;
            }
            current = current->next;
        }

        return false;
    }

    int size() {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    Node* get_head () {
        return head;
    }

    friend ostream& operator<<(ostream& o, const LinkedList& l) {
        Node* current = l.head;
        while (current != nullptr) {
            o << "value: ";
            o << current->val;
            o << "\n";
            current = current->next;
        }
        return o;
    }

};

#endif