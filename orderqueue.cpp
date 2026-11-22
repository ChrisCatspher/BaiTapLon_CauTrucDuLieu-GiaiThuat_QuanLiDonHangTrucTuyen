
#include "orderqueue.h"

OrderQueue::OrderQueue() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

OrderQueue::~OrderQueue() {
    while (!isEmpty()) {
        dequeue();
    }
}

void OrderQueue::enqueue(string id) {
    Node* newNode = new Node(id);

    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }

    size++;
}

void OrderQueue::dequeue() {
    if (isEmpty()) {
        return;
    }

    Node* temp = head;
    head = head->next;

    delete temp;
    size--;

    if (head == nullptr) {
        tail = nullptr;
    }
}

string OrderQueue::front() {
    if (isEmpty()) {
        return "";
    }

    return head->id;
}

bool OrderQueue::isEmpty() const{
    return head == nullptr;
}

int OrderQueue::getSize() const{
    return size;
}

bool OrderQueue::contains(string id) const {
    Node* current = head;

    while (current != nullptr) {
        if (current->id == id)
            return true;

        current = current->next;
    }

    return false;
}

bool OrderQueue::remove(string id) {
    if (isEmpty()) return false;

    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->id == id) {
            if (previous == nullptr) {
                head = current->next;
            }
            else {
                previous->next = current->next;
            }

            if (current == tail) {
                tail = previous;
            }

            delete current;
            size--;

            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}