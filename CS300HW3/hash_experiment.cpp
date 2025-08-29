#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <string>
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

        // worst case - all hash to same location
        for (int i = 0; i < numElements; i++) {
            ht->insert(i * 100);
        }
        
        // search for non-existent elements
        for (int i = 0; i < numElements; i++) {
            ht->search(i * 100 + 1);
        }
        

        ht->displayStats();
    }
};

int maino() {
    HashExperiment exp;
    
    cout << "Hash Table Experiment Program" << endl;
    cout << "Commands:" << endl;
    cout << "  random <num> - Run random mode experiment" << endl;
    cout << "  adversarial <num> - Run adversarial mode experiment" << endl;
    cout << "  quit - Exit program" << endl;
    
    string command;
    while (true) {
        cout << "\n> ";
        cin >> command;
        
        if (command == "quit") {
            break;
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


        else {
            cout << "Unknown command!" << endl;
        }
    }
    
    return 0;
}
