#ifndef DOUBLYLINKEDLISTNODE_H
#define DOUBLYLINKEDLISTNODE_H

#include <iostream>
#include <stdexcept>

using namespace std;

class DoublyLinkedList {
private:
    struct Node {
        int val;
        Node* next;
        Node* prev;

        Node () {
            val = 0;
            next = nullptr;
            prev = nullptr;
        }
        Node (int i) {
            val = i;
            next = nullptr;
            prev = nullptr;
        }
        Node (int i, Node* n) {
            val = i;
            next = n;
        }
        Node (int i, Node* n,  Node* p) {
            val = i;
            next = n;
            prev = p;
        }

    };  

    Node* head;
    Node* tail;

public:

    DoublyLinkedList () {
        head = nullptr;
        tail = nullptr;
    }

    ~DoublyLinkedList () {
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
        if (head == nullptr and tail == nullptr) {
            Node* n = new Node(value);
            head = n;
            tail = n;
        }
        else {
            Node* n = new Node(value);
            tail->next = n;
            n->prev = tail;
            n->next = nullptr;
            tail = n;
        }
        
    }

    void push_front (int value) {
        if (head == nullptr and tail == nullptr) {
            Node* n = new Node(value);
            head = n;
            tail = n;
        }   
        else {
            Node* n = new Node(value);
            n->next = head;
            head->prev = n;
            head = n;
        }
    }

    bool remove_key (int key) {
        if (head == nullptr and tail == nullptr) {
            return false;
        }

        Node* current = head;

        if (current->val == key) {
            if (current->next == nullptr) {
                delete head;
                head = nullptr;
                tail = nullptr;
            }
            else {
                head = head->next;
                head->prev = nullptr;
                delete current;
            }
            return true;
        }

        while (current != nullptr) {
            if (current->val == key) {
                if (current == tail) {
                    tail = current->prev;
                    tail->next = nullptr;
                }
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
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

    Node* get_tail () {
        return tail;
    }

    friend ostream& operator<<(ostream& o, const DoublyLinkedList& l) {
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