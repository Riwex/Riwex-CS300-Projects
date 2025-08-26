// OrderQueue.h
#ifndef ORDERQUEUE_H
#define ORDERQUEUE_H

/*
 * OrderQueue: a FIFO queue of Order items, built on a linked list.
 *
 * Usage Example:
 *   OrderQueue q;
 *   q.enqueue({1,100,2});
 *   Order o;
 *   if (q.dequeue(o)) { got o }
 *   else { empty }
 */

struct Order {
    int orderId; // unique identifier (e.g. 1)
    int drinkCode; // code of the drink ordered (e.g. 100)
    int sugarPackets; // number of sugar packets (e.g. 2)

    Order() {}

    Order(int id, int code, int sugar) : orderId(id), drinkCode(code), sugarPackets(sugar) {}
};

class OrderQueue {
public:
    // Definition of Node
    struct Node {
        Order data;
        Node* next;
        Node(const Order& o): data(o), next(nullptr) {}
    };
    OrderQueue(); // Constructor: creates an empty queue
    ~OrderQueue(); // Destructor: frees all the allocated nodes

    /// Add new order to the back. 
    void enqueue(const Order& o);

    /// Remove front into out; return true if an element was dequeued.
    bool dequeue(Order& out);

    /// Move orderId to front; return true if found & moved.
    bool rushOrder(int orderId);

    /// Remove orderId somewhere in queue; return true if found & removed.
    bool cancelOrder(int orderId);

    /// True if empty.
    bool empty() const;

    /// Current count.
    int size() const;

    /// Traverse without removing.
    template<typename Func>
    void traverse(Func f) const {
        for (Node* cur = head; cur; cur = cur->next)
            f(cur->data);
    }

private:
    Node* head;
    Node* tail;
    int   cnt;
    void  clear();
};

#endif // ORDERQUEUE_H