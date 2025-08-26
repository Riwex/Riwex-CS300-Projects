// PreparedStack.h
#ifndef PREPAREDSTACK_H
#define PREPAREDSTACK_H

#include <string>

/*
 * PreparedStack: LIFO stack of Prepared items.
 *
 * Usage:
 *   PreparedStack ps;
 *   ps.push({1,"Latte",2});
 *   Prepared p;
 *   if (ps.pop(p)) { got p }
 */

struct Prepared {
    int orderId; // unique identifier (e.g. 1)
    std::string drinkName; // e.g. "Latte"
    int sugarPackets; // number of sugar packets (e.g. 2)

    Prepared() {}

    Prepared(int id, const std::string& name, int sugar) : orderId(id), drinkName(name), sugarPackets(sugar) {}
};

class PreparedStack {
public:
    // Definition of Node
    struct Node {
        Prepared data;
        Node* next;
        Node(const Prepared& p, Node* n): data(p), next(n) {}
    };
    PreparedStack(); // Constructor: creates an empty stack
    ~PreparedStack(); // Destructor: frees all the allocated nodes

    /// Push onto stack.
    void push(const Prepared& p);

    /// Pop top into out; return true if popped.
    bool pop(Prepared& out);

    /// True if empty.
    bool empty() const;

    /// Current count.
    int size() const;

    /// Traverse without removing (top→bottom).
    template<typename Func>
    void traverse(Func f) const {
        for (Node* cur = head; cur; cur = cur->next)
            f(cur->data);
    }

private:
    Node* head;
    int   cnt;
    void  clear();
};

#endif // PREPAREDSTACK_H