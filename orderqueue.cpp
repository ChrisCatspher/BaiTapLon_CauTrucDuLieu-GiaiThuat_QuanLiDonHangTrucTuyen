
#include "OrderQueue.h"

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

bool OrderQueue::isEmpty() {
    return head == nullptr;
}

int OrderQueue::getSize() {
    return size;
}
