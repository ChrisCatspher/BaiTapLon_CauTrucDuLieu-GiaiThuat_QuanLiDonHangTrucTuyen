#include <iostream>
#pragma once
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
    bool isEmpty();
    int getSize();
};