#include <iostream>
#include "hash.h"
#include <vector>
#include <string>

using namespace std;

int main() {
    return 0;
}

hashTable::hashTable(int size) {
    capacity = getPrime(size);
    data.resize(capacity);
}


int hashTable::insert(const std::string &key, void *pv) {
    return 1;

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
