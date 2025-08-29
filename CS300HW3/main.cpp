#include <iostream>
#include <string>

#include <vector>
#include <random>
using namespace std;


using namespace std;

#include "hash_table.h"

class HashExperiment {
private:
    HashTable* ht;

public:
    HashExperiment() {
        ht = new HashTable(100);
    }

    ~HashExperiment() {
        delete ht;
    }

    // random
    void randomMode(int numOperations) {
        cout << "Running random mode with " << numOperations << " operations..." << endl;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 10000);
        uniform_int_distribution<> opDis(0, 2);  // 0=insert, 1=search, 2=delete

        ht->resetStats();

        for (int i = 0; i < numOperations; i++) {
            int op = opDis(gen);
            int num = dis(gen);

            if (op == 1) {
                ht->insert(num);
            } else if (op == 0) {
                ht->search(num);
            } else {
                ht->deleteElement(num);
            }
        }

        ht->displayStats();
    }

    // adversarial
    void adversarialMode(int numElements) {
        cout << "Running adversarial mode with " << numElements << " elements..." << endl;

        ht->resetStats();

        // worst case - all hash same location
        for (int i = 0; i < numElements; i++) {
            ht->insert(i * numElements);
        }

        // search for not existent elements
        for (int i = 0; i < numElements; i++) {
            ht->search(i * numElements + 1);
        }


        ht->displayStats();
    }
};

int main() {



    cout << "CS 300 Homework 3 - Hash Table Demo" << endl;
    cout << "===================================" << endl;
    cout << endl;
    cout << "Commands:" << endl;
    cout << "  insert <number> - Insert a number" << endl;
    cout << "  search <number> - Search for a number" << endl;
    cout << "  delete <number> - Delete a number" << endl;
    cout << "  stats - Show statistics" << endl;
    cout << "  setHash <a> <b> <m> <p> - Set modulus hash parameters" << endl;
    cout << "  setMulti <A> - Set multiplicative hash parameter" << endl;
    cout << "  setCollision <method> - Set collision method (chaining/linear/quadratic)" << endl;
    cout << "  setHashMethod <method> - Set hash method (modulus/multiplicative)" << endl;
    cout << "  reset - Reset statistics" << endl;
    cout << "  quit - Exit program" << endl;
    cout << "  random <num> - Run random mode experiment" << endl;
    cout << "  adversarial <num> - Run adversarial mode experiment" << endl;

    cout << endl;

    int sze = 97;
    //cin >> size;

    HashTable ht(sze);
    HashExperiment exp;

    string command;
    while (true) {
        cout << "> ";
        cin >> command;
        
        if (command == "quit") {
            cout << "Goodbye!" << endl;
            break;
        }
        else if (command == "insert") {
            int num;
            cin >> num;
            ht.insert(num);
        }
        else if (command == "random") {
            int num;
            cin >> num;
            exp.randomMode(num);
        }
        else if (command == "adversarial") {
            int num;
            cin >> num;
            exp.adversarialMode(num);
        }
        else if (command == "search") {
            int num;
            cin >> num;
            if (ht.search(num)) {
                cout << "Found " << num << endl;
            } else {
                cout << "Not found " << num << endl;
            }
        }
        else if (command == "delete") {
            int num;
            cin >> num;
            ht.deleteElement(num);
        }
        else if (command == "stats") {
            ht.displayStats();
        }
        else if (command == "setHash") {
            int a, b, m, p;
            cin >> a >> b >> m >> p;
            ht.setHashParams(a, b, m, p);
            ht.setHashMethod("modulus");
            cout << "Hash parameters updated!" << endl;
        }
        else if (command == "setMulti") {
            double A;
            cin >> A;
            ht.setMultiplicativeParam(A); // golden ratio-1 = 0.161803398875
            ht.setHashMethod("multiplicative");
            cout << "Multiplicative parameter updated!" << endl;
        }
        else if (command == "setCollision") {
            string method;
            cin >> method;
            ht.setCollisionMethod(method);
            cout << "Collision method set to: " << method << endl;
        }
        else if (command == "setHashMethod") {
            string method;
            cin >> method;
            ht.setHashMethod(method);
            cout << "Hash method set to: " << method << endl;
        }
        else if (command == "reset") {
            ht.resetStats();
            cout << "Statistics reset!" << endl;
        }
        else {
            cout << "Unknown command: " << command << endl;
        }
    }
    
    return 0;
}
