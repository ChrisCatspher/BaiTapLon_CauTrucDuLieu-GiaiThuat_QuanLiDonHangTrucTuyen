#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Node {
    string id;
    Node* next;

    Node(string id) {
        this->id = id;
        next = nullptr;
    }
};

class OrderQueue {
private:
    Node* head;
    Node* tail;
    int size;

public:
    OrderQueue();
    ~OrderQueue();

    void enqueue(string id);
    void dequeue();
    string front();
    bool isEmpty() const;
    int getSize() const;
    bool contains(string id) const;
    bool remove(string id);
};