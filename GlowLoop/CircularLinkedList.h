// CircularLinkedList.h
// Student 1 — Circular Linked List
//
// Generic (templated) circular singly linked list. The final node always
// points back to head instead of nullptr, so the list can be walked forever
// (used by GlowLoop for the Morning and Night routines).
//
// Because this class is templated, the full implementation lives in this
// header so the compiler can generate code for whatever type T it is used
// with (e.g. CircularLinkedList<SkincareStep>).

#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include <iostream>
#include <functional>

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(const T& data) : data(data), next(nullptr) {}
};

template <typename T>
class CircularLinkedList {
private:
    Node<T>* head;
    int count;

public:
    CircularLinkedList();
    ~CircularLinkedList();

    // Adds a new item to the end of the list (right before it wraps back to head).
    void add(const T& item);

    // Removes the first item for which match(item) returns true.
    // Returns true if something was removed, false if nothing matched.
    bool remove(const std::function<bool(const T&)>& match);

    // Looks for the first item for which match(item) returns true.
    // If found, copies it into result and returns true; otherwise returns false.
    bool search(const std::function<bool(const T&)>& match, T& result) const;

    // Prints every item in the list, in order, once around the circle.
    // Assumes T has a displayStep() method, as SkincareStep does.
    void display() const;

    bool isEmpty() const;
    int size() const;
};

template <typename T>
CircularLinkedList<T>::CircularLinkedList() : head(nullptr), count(0) {}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
    if (head == nullptr) {
        return;
    }

    // Break the circle so a normal traversal terminates, then delete every node.
    Node<T>* tail = head;
    while (tail->next != head) {
        tail = tail->next;
    }
    tail->next = nullptr;

    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

template <typename T>
void CircularLinkedList<T>::add(const T& item) {
    Node<T>* newNode = new Node<T>(item);

    if (head == nullptr) {
        // First node in the list points to itself.
        head = newNode;
        newNode->next = head;
    } else {
        // Find the current tail (the node whose next is head), then insert after it.
        Node<T>* tail = head;
        while (tail->next != head) {
            tail = tail->next;
        }
        tail->next = newNode;
        newNode->next = head;
    }

    count++;
}

template <typename T>
bool CircularLinkedList<T>::remove(const std::function<bool(const T&)>& match) {
    if (head == nullptr) {
        return false;
    }

    // Special case: only one node in the list.
    if (head->next == head) {
        if (match(head->data)) {
            delete head;
            head = nullptr;
            count--;
            return true;
        }
        return false;
    }

    Node<T>* current = head;
    Node<T>* prev = nullptr;

    do {
        if (match(current->data)) {
            if (current == head) {
                // Removing the head: find the tail so it can point to the new head.
                Node<T>* tail = head;
                while (tail->next != head) {
                    tail = tail->next;
                }
                head = head->next;
                tail->next = head;
            } else {
                prev->next = current->next;
            }
            delete current;
            count--;
            return true;
        }
        prev = current;
        current = current->next;
    } while (current != head);

    return false;
}

template <typename T>
bool CircularLinkedList<T>::search(const std::function<bool(const T&)>& match, T& result) const {
    if (head == nullptr) {
        return false;
    }

    Node<T>* current = head;
    do {
        if (match(current->data)) {
            result = current->data;
            return true;
        }
        current = current->next;
    } while (current != head);

    return false;
}

template <typename T>
void CircularLinkedList<T>::display() const {
    if (head == nullptr) {
        std::cout << "The skincare routine is currently empty." << std::endl;
        return;
    }

    Node<T>* current = head;
    do {
        current->data.displayStep();
        current = current->next;
    } while (current != head);
}

template <typename T>
bool CircularLinkedList<T>::isEmpty() const {
    return head == nullptr;
}

template <typename T>
int CircularLinkedList<T>::size() const {
    return count;
}

#endif
