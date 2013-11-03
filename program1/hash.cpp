// Ethan Lusterman
// ECE165, Fall 2013

#include <iostream>
#include "hash.h"

using namespace std;


hashTable::hashTable(int size) {
    capacity = getPrime(size);
    data.resize(capacity);
    filled = 0;

    for (int i=0; i<data.size(); i++)
        data[i].isOccupied = false;
}

int hashTable::insert(const std::string &key, void *pv) {

    bool success;

    int hashLoc = hash(key);

    if (contains(key))
        return 1;

    if (filled >= capacity/2) {
        success = rehash();
        if (!success)
            return 2;
    }

    while (data[hashLoc].isOccupied) {
        hashLoc++;
        hashLoc %= capacity;
    }

    if (!data[hashLoc].isOccupied || data[hashLoc].isDeleted) {
        data[hashLoc].key = key;
        data[hashLoc].isOccupied = true;
        data[hashLoc].isDeleted = false;
        data[hashLoc].pv = pv;
        filled++;
        return 0;
    }

    return -1;


}

bool hashTable::contains(const std::string &key) {

    int pos = findPos(key);

    if (pos == -1)
        return false;
    else
        return true;
}


void* hashTable::getPointer(const std::string &key, bool *b) {

    int pos = findPos(key);

    if (pos == -1 || data[pos].isDeleted) {
        *b = false;
        return NULL;
    }
    else {
        *b = true;
        return data[pos].pv;
    }

}


int hashTable::setPointer(const std::string &key, void *pv) {

    int pos = findPos(key);

    if (pos == -1)
        return 1;
    else {
        data[pos].pv = pv;
        return 0;
    }

}

bool hashTable::remove(const std::string &key) {

    int pos = findPos(key);

    if (pos == -1)
        return false;
    else {
        data[pos].isDeleted = true;
        return true;
    }

}


int hashTable::hash(const std::string &key) {

    int hashValue = 0;

    for (int i=0; i < key.length(); i++)
        hashValue = 37*hashValue + key[i];

    hashValue %= capacity;
    if (hashValue < 0)
        hashValue += capacity;

    return hashValue;
}

int hashTable::findPos(const std::string &key) {

    int hashValue = hash(key);
    if (!data[hashValue].isOccupied)
        return -1;

    while (data[hashValue].isOccupied) {
        if (data[hashValue].key == key && !data[hashValue].isDeleted)
            return hashValue;

        hashValue++;
        hashValue %= capacity;
    }

    return -1;
}

bool hashTable::rehash() {
    try {
        vector<hashItem> old = data;
        filled = 0;

        int nextSize = getPrime(capacity);
        data.clear();
        data.resize(nextSize);
        capacity = nextSize;

        for (int i=0; i<capacity; i++) {
            data[i].isOccupied = false;
        }

        for (int i=0; i<old.size(); i++) {
            if (old[i].isOccupied && !old[i].isDeleted) {
                insert(old[i].key, old[i].pv);
            }
        }
        old.clear();
        return true;
    }
    catch (const bad_alloc &b) {
        cerr << "Memory Allocation Failed." << endl;
        return false;
    }
}


unsigned int hashTable::getPrime(int size) {

    vector<int> primes;

    primes.push_back(100003);
    primes.push_back(505919);
    primes.push_back(1054007);
    primes.push_back(2380481);
    primes.push_back(4114741);
    primes.push_back(6699197);
    primes.push_back(8487821);

    for (int i=0; i < primes.size(); i++) {
        if (primes[i] > size) {
            return primes[i];
        }
    }
    return 0;
}
