#include <iostream>
#include "hash.h"
#include <vector>
#include <string>

using namespace std;

int main() {
    hashTable testTable(10);
    return 0;
}

hashTable::hashTable(int size) {
    capacity = getPrime(size);
    data.resize(capacity);
}

bool hashTable::contains(const std::string &key) {
    int hashLoc = hash(key);
    while (true) {
        if (!data[hashLoc].isOccupied) return false;
        else if (data[hashLoc].key == key) return true;
        else ++hashLoc %= capacity;
    }
    return false;
}

int hashTable::insert(const std::string &key, void *pv) {

    bool success;

    int hashLoc = hash(key);
    if (contains(key))
        return 1;

    if (filled >= capacity/2)
        success = rehash();
        if (!success)
            return 2;

    while (data[hashLoc].isOccupied)
        hashLoc++;

    if (!data[hashLoc].isOccupied) {
        data[hashLoc].key = key;
        data[hashLoc].isOccupied = true;
        data[hashLoc].isDeleted = false;
        return 0;
    }

}

bool hashTable::rehash() {
    return true;

}

int hashTable::hash(const std::string &key) {

    int hashValue = 0;

    for (int i=0; i < key.length(); i++)
        hashValue = 37*hashValue + key[i];

    hashValue %= capacity;

    return hashValue;
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
