    // MenuList.h
#ifndef MENULIST_H
#define MENULIST_H

#include <string>
#include <iostream>

/*
 * MenuList: a singly‑linked list of Drink items.

 *
 * Usage Example:
 *   MenuList menu;
 *   menu.addDrink({100, "Espresso", 2.50});
 *   menu.addDrink({101, "Latte",    3.75});
 *   menu.printAll();
 */

/// One menu item
struct Drink {
    int code;           // unique identifier (e.g. 100)
    std::string name;   // e.g. "Latte"
    double price;       // e.g. 3.75

     // Default constructor
     Drink() {}

     // Parameterized constructor
     Drink(int c, const std::string& n, double p) : code(c), name(n), price(p) {}
};

class MenuList {
public:
    /// Internal node type for linked list
    struct Node {
        Drink data;     // the drink stored
        Node* next;     // pointer to next node (nullptr if last)
        Node(const Drink& d)
          : data(d)
          , next(nullptr)
        {}
    };

    /// Constructor: creates an empty list
    MenuList();

    /// Destructor: frees all the allocated nodes
    ~MenuList();

    /// Append a new drink to the end of the list.
    void addDrink(const Drink& d);

    /// Remove the first node whose data.code == code.
    /// Returns true if found & removed, false otherwise.
    bool removeDrink(int code);

    /// Swap the positions of the two nodes identified by code1 and code2.
    /// Returns true if both found and swapped, false otherwise.
    bool swapDrinks(int code1, int code2);

    /// Move the node with data.code == code to the front (head).
    /// Returns true if found and moved, false if not found or already head.
    bool featureDrink(int code);

    /// Find a drink by code, returning a pointer to its data, or nullptr.
    Drink* findDrink(int code);

    /// Print all drinks in order to stdout.
    /// Example format: [100] Espresso - $2.50
    void printAll() const;

    /// Return the number of drinks in the list.
    int size() const;

private:
    Node* head;    // first node (nullptr if empty)
    Node* tail;    // last node (nullptr if empty)
    int   cnt;     // cached count of nodes

    /// Helper to delete all nodes on destruction.
    void clear();
};

#endif // MENULIST_H
