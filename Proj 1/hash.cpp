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

    if (!data[hashLoc].isOccupied) {
        data[hashLoc].key = key;
        data[hashLoc].isOccupied = true;
        data[hashLoc].isDeleted = false;
        filled++;
        return 0;
    }


}

bool hashTable::contains(const std::string &key) {
    int pos = findPos(key);

    if (pos == -1)
        return false;
    else
        return true;
}


// void *hashTable::getPointer(const std::string &key, bool *b) {
//     b = false;
//
//     int hashLoc = hash(key);
//
// }


// int setPointer(const std::string &key, void *pv){
// }

// bool remove(const std::string &key) {
// }


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

    while (data[hashValue].key != key) {
        if (!data[hashValue].isOccupied)
            return -1;
        else {
            hashValue++;
            hashValue %= capacity;
        }
    }

    return hashValue;
}

bool hashTable::rehash() {
    vector<hashItem> old = data;
    filled = 0;

    int nextSize = getPrime(capacity);
    data.resize(nextSize);
    capacity = nextSize;

    for (int i=0; i<capacity; i++) {
        data[i].isOccupied = false;
    }

    for (int i=0; i<old.size(); i++) {
        if (old[i].isOccupied) {
            insert(old[i].key);
            filled++;
        }
    }

    return true;
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


// int main() {
//     hashTable t(100);
//     int i1 = t.insert("abc");
//     int i2 = t.insert("xyz");
//     int i3 = t.insert("123");
// 
//     bool c1 = t.contains("abc");
//     bool c2 = t.contains("xyz");
//     bool c3 = t.contains("123");
//     bool c4 = t.contains("asdfgawefa");
//     int x = t.dhash("asdfgawefa");
//     cout << x << endl;
// 
//     int h1 = t.dhash("abc");
//     int h2 = t.dhash("xyz");
//     int h3 = t.dhash("123");
//     int h4 = t.dhash("asdfgawefa");
// 
//     cout << h1 << endl;
//     cout << h2 << endl;
//     cout << h3 << endl;
//     cout << h4 << endl;
// 
//    int a = t.length();
//    cout << a << endl;
// 
//    bool y = t.datHash();
//    int z = t.length();
//    cout << y << endl;
//    cout << z << endl;
//     c1 = t.contains("abc");
//     c2 = t.contains("xyz");
//     c3 = t.contains("123");
//     c4 = t.contains("asdfgawefa");
//    cout << c1 << c2 << c3 << c4 << endl;
// 
// 
//     return 0;
// }
