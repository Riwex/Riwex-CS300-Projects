//
// Created by lorda on 7/31/2025.
//
#include "PreparedStack.h"

PreparedStack::PreparedStack() {
    head = nullptr;
    cnt = 0;


}

PreparedStack::~PreparedStack() { clear();}

void PreparedStack::clear() {
    while (head != nullptr) {
         Node* temp = head;
        head = head->next;

        delete temp;

    }
    cnt = 0;
}

void PreparedStack::push(const Prepared& p) {

    Node* newNode = new Node(p, head);
    head = newNode;
      cnt++;
}

bool PreparedStack::pop(Prepared& out) {
       if (head == nullptr) {
        return false;}

    out = head->data;
    Node* temp = head;
    head = head->next;

    delete temp;
    cnt--;

    return true;
}

bool PreparedStack::empty() const {return head == nullptr;}

int PreparedStack::size() const {return cnt;}

