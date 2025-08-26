//
// Created by lorda on 7/31/2025.
//
#include "OrderQueue.h"

OrderQueue::OrderQueue() {
    head = nullptr;
    tail = nullptr;
    cnt = 0;

}

OrderQueue::~OrderQueue() {

    clear();
}

void OrderQueue::clear() {

    while (head != nullptr) {
        Node* temp = head;
        head = head->next;


        delete temp;
    }
    tail = nullptr;
    cnt = 0;
}

void OrderQueue::enqueue(const Order& o) {
    Node* newNode = new Node(o);

    if (tail == nullptr) {
        head = tail = newNode;

    } else {
        tail->next = newNode;
        tail = newNode;

    }
    cnt++;
}

bool OrderQueue::dequeue(Order& out) {
    if (head == nullptr) {
        return false;
    }

    out = head->data;
    Node* temp = head;
    head = head->next;

    if (head == nullptr) {
        tail = nullptr;
    }

    delete temp;
    cnt--;
    return true;
}

bool OrderQueue::rushOrder(int orderId) {
    if (head == nullptr || head->data.orderId == orderId) {
        return false;
    }

    if (head->next != nullptr && head->next->data.orderId == orderId) {
        Node* nodeToRush = head->next;
        head->next = nodeToRush->next;

        if (nodeToRush == tail) {
            tail = head;
        }

        nodeToRush->next = head;
        head = nodeToRush;
        return true;
    }


    Node* prev = head;
    while (prev->next != nullptr && prev->next->data.orderId != orderId) {
        prev = prev->next;

    }

    if (prev->next == nullptr) {
        return false;
    }

    Node* nodeToRush = prev->next;
    prev->next = nodeToRush->next;

    if (nodeToRush == tail) {
        tail = prev;}



    nodeToRush->next = head;
    head = nodeToRush;
    return true;
}

bool OrderQueue::cancelOrder(int orderId) {
    if (head == nullptr) {
        return false;
    }

    // If first node needs to be removed
    if (head->data.orderId == orderId) {
        Node* temp = head;
        head = head->next;

        if (head == nullptr) {
            tail = nullptr;
        }

        delete temp;
        cnt--;
        return true;
    }



    Node* prev = head;

    while (prev->next != nullptr && prev->next->data.orderId != orderId) {
        prev = prev->next;
    }

    if (prev->next == nullptr) {
        return false; }

    Node* nodeToDelete = prev->next;
    prev->next = nodeToDelete->next;


    if (nodeToDelete == tail) {
        tail = prev;
    }

    delete nodeToDelete;
    cnt--;
    return true;
}

bool OrderQueue::empty() const {
    return head == nullptr;
}

int OrderQueue::size() const {
    return cnt;
}

