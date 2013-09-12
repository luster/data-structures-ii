#include <iostream>
#include <vector>
#include <string>

using namespace std;

int capacity = 100003;

int hash(const std::string &key) {
	
	int hashValue = 0;

	for (int i=0; i < key.length(); i++)
		hashValue = 37*hashValue + key[i];

	hashValue %= capacity;

	return hashValue;
}

int main() {

	string x = "test";

	int hashTest = hash(x);
	cout << hashTest << endl;

	return 0;
}
