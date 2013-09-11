#include <iostream>
#include "hash.h"

using namespace std;


void hashTable::hashTable(int size = 0) {
	capacity = getPrime(size);

}


void hashTable::insert(const std::string &key, void *pv = NULL) {
	// what
}


int hashTable::hash(const std::string &key) {
	
	int hash = 0;

	for (int i=0; i < key.length(); i++)
		hash = 37*hash + key[i];

	hash %= capacity;

	return hash;
}


static unsigned int hashTable::getPrime(int size) {

	int primes [7];

	primes[0] = 100003;
	primes[1] = 505919;
	primes[2] = 1054007;
	primes[3] = 2380481;
	primes[4] = 4114741;
	primes[5] = 6699197;
	primes[6] = 8487821;

	for (i=0; i < primes.length(); i++)
		if primes[i] < size
			return primes[i];
}
