#include <iostream>
#include "hash.h"
#include <vector>
#include <string>

using namespace std;

int main() {
    hashTable testTable(10);
    // int ins = testTable.datdatHash("abcdefgh");
    // int ins2 = testTable.datdatHash("abcd");
    // int ins3 = testTable.datdatHash("dcba");
    // int ins4 = testTable.datdatHash("edcba");

    int ins = testTable.insert("abcdefgh");
    int ins2 = testTable.insert("abcd");
    int ins3 = testTable.insert("dcba");
    int ins4 = testTable.insert("edcba");

    bool i1 = testTable.contains("abcdefgh");
    bool i2 = testTable.contains("abcd");
    bool i3 = testTable.contains("dcba");
    bool i4 = testTable.contains("edcba");
    bool i5 = testTable.contains("stupidbitch");
    bool x = testTable.datHash();

    cout << i1 << endl;
    cout << i2 << endl;
    cout << i3 << endl;
    cout << i4 << endl;
    cout << i5 << endl;
    cout << x << endl;

    return 0;
}

hashTable::hashTable(int size) {
    capacity = getPrime(size);
    data.resize(capacity);
    filled = 0;
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

    while (data[hashLoc].isOccupied)
        hashLoc++;
        hashLoc %= capacity;

    if (!data[hashLoc].isOccupied) {
        data[hashLoc].key = key;
        data[hashLoc].isOccupied = true;
        data[hashLoc].isDeleted = false;
        filled++;
        return 0;
    }

}

bool hashTable::contains(const std::string &key) {
    int hashLoc = hash(key);
    int fixedHash = hash(key);

    if (!data[hashLoc].isOccupied) return false;
    else {
        while (data[hashLoc].key != key) {
            hashLoc++;
            hashLoc %= capacity;
            if (data[hashLoc].key == key) return true;
            if (hashLoc == fixedHash-1) return false;
        }
    }
    return false;
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

    // error seems to be over here
    return hashValue;
}

int hashTable::findPos(const std::string &key) {

    int hashValue = hash(key);
    if (!data[hashValue].isOccupied)
        return -1;

    while (data[hashValue].key != key)
        hashValue++;

    return hashValue;
}

bool hashTable::rehash() {
    // new hash table, declare and resize
    vector<hashItem> tmpData;
    int newSize = getPrime(data.size());
    tmpData.resize(newSize);
    capacity = newSize;

    int t = tmpData.size();
    int d = data.size();
    // swap data and tmpData since class def changes data vector
    data.swap(tmpData);
    int ts = tmpData.size();
    int ds = data.size();
    cout << t << endl;
    cout << d << endl;
    cout << ts << endl;
    cout << ds << endl;

    for (int i=0; i < tmpData.size(); i++) {
        if (tmpData[i].isOccupied) {
            int ins = insert(tmpData[i].key);
        }
    }
 
    // free memory
    vector<hashItem>().swap(tmpData);

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
