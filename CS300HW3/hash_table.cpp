#include "hash_table.h"

HashTable::HashTable(int size) {
    tableSize = size;
    elementCount = 0;
    
    a = 1;
    b = 0;
    m = size;
    p = 1000000007;  // big prime
    A = 0.6180339887;  // golden ratio
    
    currentCollisionMethod = "quadratic";
    currentHashMethod = "modulus";
    
    totalProbes = 0;
    maxProbes = 0;
    totalResizes = 0;
    totalCollisions = 0;
    
    chainingTable.resize(size);
    linearTable.resize(size, -1);
    quadraticTable.resize(size, -1);
}

int HashTable::modulusHash(int key) {
    return ((a * key + b) % p) % m;
}

int HashTable::multiplicativeHash(int key) {
    double k = key * A;
    k = k - (int)k;
    return (int)(k * m);
}

int HashTable::getHash(int key) {
    if (currentHashMethod == "modulus") {
        return modulusHash(key);
    } else {
        return multiplicativeHash(key);
    }
}

void HashTable::insertChaining(int key) {
    int hash = getHash(key);
    int probes = 0;
    
    for (int val : chainingTable[hash]) {
        probes++;
        if (val == key) {
            cout << "Element " << key << " already exists!" << endl;
            return;
        }
    }
    
    chainingTable[hash].push_back(key);
    elementCount++;
    totalProbes += probes;
    maxProbes = max(maxProbes, probes);
    
    // resize
    if (getLoadFactor() > 0.75) {
        resize();
    }
}

void HashTable::insertLinear(int key) {
    int hash = getHash(key);
    int probes = 0;
    
    while (linearTable[hash] != -1) {
        if (linearTable[hash] == key) {
            cout << "Element " << key << " already exists!" << endl;
            return;
        }
        hash = (hash + 1) % tableSize;
        probes++;
        totalCollisions++;
    }
    
    linearTable[hash] = key;
    elementCount++;
    totalProbes += probes;
    maxProbes = max(maxProbes, probes);
    
    if (getLoadFactor() > 0.7) {
        resize();
    }
}

void HashTable::insertQuadratic(int key) {
    int hash = getHash(key);
    int probes = 0;
    int i = 0;
    
    while (quadraticTable[hash] != -1) {
        if (quadraticTable[hash] == key) {
            cout << "Element " << key << " already exists!" << endl;
            return;
        }
        i++;
        hash = (getHash(key) + i * i) % tableSize;
        probes++;
        totalCollisions++;
    }
    
    quadraticTable[hash] = key;
    elementCount++;
    totalProbes += probes;
    maxProbes = max(maxProbes, probes);
    
    if (getLoadFactor() > 0.7) {
        resize();
    }
}

void HashTable::insert(int key) {
    if (currentCollisionMethod == "chaining") {
        insertChaining(key);
    } else if (currentCollisionMethod == "linear") {
        insertLinear(key);
    } else if (currentCollisionMethod == "quadratic") {
        insertQuadratic(key);
    }
}

bool HashTable::searchChaining(int key) {
    int hash = getHash(key);
    int probes = 0;
    
    for (int val : chainingTable[hash]) {
        probes++;
        if (val == key) {
            totalProbes += probes;
            maxProbes = max(maxProbes, probes);
            return true;
        }
    }
    
    totalProbes += probes;
    maxProbes = max(maxProbes, probes);
    return false;
}

bool HashTable::searchLinear(int key) {
    int hash = getHash(key);
    int probes = 0;
    int startHash = hash;
    
    do {
        if (linearTable[hash] == key) {
            totalProbes += probes;
            maxProbes = max(maxProbes, probes);
            return true;
        }
        if (linearTable[hash] == -1) break;
        hash = (hash + 1) % tableSize;
        probes++;
    } while (hash != startHash);
    
    totalProbes += probes;
    maxProbes = max(maxProbes, probes);
    return false;
}

bool HashTable::searchQuadratic(int key) {
    int hash = getHash(key);
    int probes = 0;
    int i = 0;
    
    while (quadraticTable[hash] != -1) {
        if (quadraticTable[hash] == key) {
            totalProbes += probes;
            maxProbes = max(maxProbes, probes);
            return true;
        }
        i++;
        hash = (getHash(key) + i * i) % tableSize;
        probes++;
    }
    
    totalProbes += probes;
    maxProbes = max(maxProbes, probes);
    return false;
}

bool HashTable::search(int key) {
    if (currentCollisionMethod == "chaining") {
        return searchChaining(key);
    } else if (currentCollisionMethod == "linear") {
        return searchLinear(key);
    } else if (currentCollisionMethod == "quadratic") {
        return searchQuadratic(key);
    }
    return false;
}

void HashTable::deleteChaining(int key) {
    int hash = getHash(key);
    
    for (auto it = chainingTable[hash].begin(); it != chainingTable[hash].end(); ++it) {
        if (*it == key) {
            chainingTable[hash].erase(it);
            elementCount--;
            cout << "Element " << key << " deleted successfully!" << endl;
            return;
        }
    }
    
    cout << "Element " << key << " not found for deletion!" << endl;
}

void HashTable::deleteLinear(int key) {
    int hash = getHash(key);
    int startHash = hash;
    
    do {
        if (linearTable[hash] == key) {
            linearTable[hash] = -1;
            elementCount--;
            cout << "Element " << key << " deleted successfully!" << endl;
            return;
        }
        if (linearTable[hash] == -1) break;
        hash = (hash + 1) % tableSize;
    } while (hash != startHash);
    
    cout << "Element " << key << " not found for deletion!" << endl;
}

void HashTable::deleteQuadratic(int key) {
    int hash = getHash(key);
    int i = 0;
    
    while (quadraticTable[hash] != -1) {
        if (quadraticTable[hash] == key) {
            quadraticTable[hash] = -1;
            elementCount--;
            cout << "Element " << key << " deleted successfully!" << endl;
            return;
        }
        i++;
        hash = (getHash(key) + i * i) % tableSize;
    }
    
    cout << "Element " << key << " not found for deletion!" << endl;
}

void HashTable::deleteElement(int key) {
    if (currentCollisionMethod == "chaining") {
        deleteChaining(key);
    } else if (currentCollisionMethod == "linear") {
        deleteLinear(key);
    } else if (currentCollisionMethod == "quadratic") {
        deleteQuadratic(key);
    }
}

double HashTable::getLoadFactor() {
    return (double)elementCount / tableSize;
}

void HashTable::resize() {
    totalResizes++;
    int oldSize = tableSize;
    tableSize *= 2;
    
    vector<list<int>> oldChaining = chainingTable;
    chainingTable.clear();
    chainingTable.resize(tableSize);
    
    vector<int> oldLinear = linearTable;
    linearTable.clear();
    linearTable.resize(tableSize, -1);
    
    vector<int> oldQuadratic = quadraticTable;
    quadraticTable.clear();
    quadraticTable.resize(tableSize, -1);
    
    elementCount = 0;
    for (int i = 0; i < oldSize; i++) {
        for (int val : oldChaining[i]) {
            insertChaining(val);
        }
        if (oldLinear[i] != -1) {
            insertLinear(oldLinear[i]);
        }
        if (oldQuadratic[i] != -1) {
            insertQuadratic(oldQuadratic[i]);
        }
    }
}

void HashTable::displayStats() {
    cout << "\n=== HASH TABLE STATS ===" << endl;
    cout << "Size: " << tableSize << endl;
    cout << "Elements: " << elementCount << endl;
    cout << "Load Factor: " << getLoadFactor() << endl;
    cout << "Total Probes: " << totalProbes << endl;
    cout << "Max Probes: " << maxProbes << endl;
    cout << "Total Collisions: " << totalCollisions << endl;
    cout << "Total Resizes: " << totalResizes << endl;
    cout << "Hash Method: " << currentHashMethod << endl;
    cout << "Collision Method: " << currentCollisionMethod << endl;
    cout << "========================\n" << endl;
}

void HashTable::resetStats() {
    totalProbes = 0;
    maxProbes = 0;
    totalCollisions = 0;
}

void HashTable::setHashParams(int newA, int newB, int newM, int newP) {
    a = newA;
    b = newB;
    m = newM;
    p = newP;
}

void HashTable::setMultiplicativeParam(double newA) {
    A = newA;
}

void HashTable::setCollisionMethod(string method) {
    currentCollisionMethod = method;
}

void HashTable::setHashMethod(string method) {
    currentHashMethod = method;
}
