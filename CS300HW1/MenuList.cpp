//
// Created by lorda on 7/31/2025.
//
#include "MenuList.h"
#include <iostream>
#include <iomanip>

using namespace std;

MenuList::MenuList() {
    head = nullptr;
    tail = nullptr;
    cnt = 0;
}

MenuList::~MenuList() {
    clear();
}

void MenuList::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    cnt = 0;
}

void MenuList::addDrink(const Drink& d) {
    Node* newNode = new Node(d);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    cnt++;
}

bool MenuList::removeDrink(int code) {
    if (head == nullptr) {
        return false;
    }

    if (head->data.code == code) {
        Node* temp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;
        cnt--;
        return true;
    }

    Node* current = head;
    while (current->next != nullptr) {
        if (current->next->data.code == code) {
            break;
        }
        current = current->next;
    }

    if (current->next == nullptr) {
        return false;
    }

    Node* nodeToDelete = current->next;
    current->next = nodeToDelete->next;

    if (nodeToDelete == tail) {
        tail = current;
    }

    delete nodeToDelete;
    cnt--;
    return true;
}

bool MenuList::swapDrinks(int code1, int code2) {


    Node* node1 = nullptr;
    Node* node2 = nullptr;

    for (Node* current = head; current != nullptr; current = current->next) {
        if (current->data.code == code1) {
            node1 = current;
        }
        if (current->data.code == code2) {
            node2 = current;
        }
    }

    if (node1 == nullptr || node2 == nullptr) {
        return false;
    }

    Drink temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;

    return true;
}

bool MenuList::featureDrink(int code) {
    if (head == nullptr)
        return false;
    if (head->data.code == code)
        return true;

    Node* prev = head;
      while (prev->next != nullptr && prev->next->data.code != code) {
                prev = prev->next;
            }
        if (prev->next == nullptr)
               return false;

      Node* nodeToMove = prev->next;
        prev->next     = nodeToMove->next;
        if (nodeToMove == tail)
            tail = prev;

        nodeToMove->next = head;
        head             = nodeToMove;
        return true;
    }


Drink* MenuList::findDrink(int code){
    for (Node* current = head; current != nullptr; current = current->next) {
        if (current->data.code == code) {
            return &(current->data);
        }
    }
    return nullptr;
}

void MenuList::printAll() const {
        if (head == nullptr) {
                cout << "Menu is empty." << endl;
                return;
            }

    for (Node* current = head; current != nullptr; current = current->next) {
        cout << "[" << current->data.code << "] " << current->data.name
             << " - $" << fixed << setprecision(2) << current->data.price << endl;
    }
}

int MenuList::size() const {
    return cnt;
}