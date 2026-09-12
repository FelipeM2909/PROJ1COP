// CircularLinkedList.h defines a generic, templated circular singly linked
// list used to store the Morning and Night skincare routines. Its final
// node always points back to head so callers can cycle through steps
// endlessly, and every operation keeps the head/tail pointers in sync.

#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include <cstddef>
#include <functional>
#include <utility>

// Stores generic values in a cycle whose final node points back to the head.
template <typename T> class CircularLinkedList {
private:
  // Represents one value and the link to the next value in the cycle.
  struct Node {
    T data;
    Node *next;

    // Creates a node containing a copy of the supplied value.
    explicit Node(const T &value) : data(value), next(nullptr) {}
  };

  Node *head;
  Node *tail;
  std::size_t itemCount;

public:
  // Creates an empty circularly linked list.
  CircularLinkedList() : head(nullptr), tail(nullptr), itemCount(0) {}

  // Releases every node owned by the list.
  ~CircularLinkedList() { clear(); }

  // Prevents accidental shallow copies of node pointers.
  CircularLinkedList(const CircularLinkedList &) = delete;
  CircularLinkedList &operator=(const CircularLinkedList &) = delete;

  // Adds an item to the end of the cycle.
  void add(const T &item) {
    Node *newNode = new Node(item);

    if (head == nullptr) {
      head = newNode;
      tail = newNode;
      newNode->next = head;
    } else {
      newNode->next = head;
      tail->next = newNode;
      tail = newNode;
    }

    ++itemCount;
  }

  // Inserts an item before the first larger item according to a comparison.
  template <typename Compare>
  void addInOrder(const T &item, Compare comesBefore) {
    if (head == nullptr || comesBefore(item, head->data)) {
      Node *newNode = new Node(item);

      if (head == nullptr) {
        head = newNode;
        tail = newNode;
        newNode->next = head;
      } else {
        newNode->next = head;
        head = newNode;
        tail->next = head;
      }

      ++itemCount;
      return;
    }

    Node *current = head;
    while (current != tail && !comesBefore(item, current->next->data)) {
      current = current->next;
    }

    Node *newNode = new Node(item);
    newNode->next = current->next;
    current->next = newNode;

    if (current == tail) {
      tail = newNode;
    }

    ++itemCount;
  }

  // Removes the first item for which the predicate returns true.
  template <typename Predicate> bool removeIf(Predicate matches) {
    if (head == nullptr) {
      return false;
    }

    Node *current = head;
    Node *previous = tail;

    do {
      if (matches(current->data)) {
        if (itemCount == 1) {
          head = nullptr;
          tail = nullptr;
        } else {
          previous->next = current->next;

          if (current == head) {
            head = current->next;
            tail->next = head;
          }

          if (current == tail) {
            tail = previous;
            tail->next = head;
          }
        }

        delete current;
        --itemCount;
        return true;
      }

      previous = current;
      current = current->next;
    } while (current != head);

    return false;
  }

  // Returns the first item matching a predicate or nullptr when not found.
  template <typename Predicate> const T *findIf(Predicate matches) const {
    if (head == nullptr) {
      return nullptr;
    }

    Node *current = head;
    do {
      if (matches(current->data)) {
        return &current->data;
      }

      current = current->next;
    } while (current != head);

    return nullptr;
  }

  // Runs an action once for each item, beginning at the head.
  void forEach(const std::function<void(const T &)> &action) const {
    if (head == nullptr) {
      return;
    }

    Node *current = head;
    do {
      action(current->data);
      current = current->next;
    } while (current != head);
  }

  // Returns the item at a zero-based position or nullptr for an invalid index.
  const T *at(std::size_t index) const {
    if (index >= itemCount) {
      return nullptr;
    }

    Node *current = head;
    for (std::size_t position = 0; position < index; ++position) {
      current = current->next;
    }

    return &current->data;
  }

  // Reports whether the list contains no items.
  bool empty() const { return itemCount == 0; }

  // Returns the number of items currently stored.
  std::size_t size() const { return itemCount; }

  // Deletes every node and restores the empty-list state.
  void clear() {
    if (head == nullptr) {
      return;
    }

    tail->next = nullptr;
    Node *current = head;

    while (current != nullptr) {
      Node *nodeToDelete = current;
      current = current->next;
      delete nodeToDelete;
    }

    head = nullptr;
    tail = nullptr;
    itemCount = 0;
  }
};

#endif
