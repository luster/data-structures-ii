#include <iostream>
#include "hash.h"
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main() {
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
    int hashLoc = hash(key);

    if (data[hashLoc].key == key)
        return true;

    if (!data[hashLoc].isOccupied)
        return false;

    while (data[hashLoc].isOccupied) {
       hashLoc++;
       hashLoc %= capacity;
       if (data[hashLoc].key == key)
           return true;
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
    int oldCapacity = capacity;
    int newSize = getPrime(data.size());
    capacity = newSize;

    // new hash table vector, declare and resize
    vector<hashItem> tmpData;
    tmpData.resize(newSize);

    for (int i=0; i<tmpData.size(); i++) {
        tmpData[i].isOccupied = false;
    }

    tmpData.swap(data);
    for (int i=0; i<tmpData.size(); i++) {
        if (tmpData[i].isOccupied) {
            insert(tmpData[i].key);
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


void gen_random(char *s, const int len) {
        static const char alphanum[] =
                    "0123456789"
                            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                    "abcdefghijklmnopqrstuvwxyz";

            for (int i = 0; i < len; ++i) {
                        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
                            }

                s[len] = 0;
}
