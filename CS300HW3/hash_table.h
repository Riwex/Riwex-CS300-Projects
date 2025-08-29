#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <list>
using namespace std;

class HashTable {
private:
    vector<list<int>> chainingTable;
    vector<int> linearTable;
    vector<int> quadraticTable;

    int tableSize;
    int elementCount;

    // hash function parameters
    int a, b, m, p;        // for modulus
    double A;              // for multiplicative

    string currentCollisionMethod;
    string currentHashMethod;

    // stats
    int totalProbes;
    int maxProbes;
    int totalResizes;
    int totalCollisions;

public:
    HashTable(int size = 100);

    int modulusHash(int key);
    int multiplicativeHash(int key);
    int getHash(int key);

    void insert(int key);
    void deleteElement(int key);
    bool search(int key);

    void insertChaining(int key);
    void insertLinear(int key);
    void insertQuadratic(int key);

    bool searchChaining(int key);
    bool searchLinear(int key);
    bool searchQuadratic(int key);

    void deleteChaining(int key);
    void deleteLinear(int key);
    void deleteQuadratic(int key);

    double getLoadFactor();
    void resize();
    void displayStats();
    void resetStats();

    void setHashParams(int newA, int newB, int newM, int newP);
    void setMultiplicativeParam(double newA);
    void setCollisionMethod(string method);
    void setHashMethod(string method);
};

#endif
