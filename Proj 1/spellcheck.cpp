#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include "hash.h"

using namespace std;

hashTable dict(100000);

bool loadDictionary(ifstream &dict_file);
int spellCheck(ifstream &input, ofstream &output);

int main() {

    // prompt user for dict file
    string filename, outfilename;
    cout << "Enter name of dictionary: ";
    cin >> filename;
    clock_t t1 = clock();

    // load dictionary
    ifstream input(filename.c_str());
    if (!input) {
        cerr << "Error: could not open " << filename << endl;
        exit(1);
    }

    bool loaded = loadDictionary(input);

    clock_t t2 = clock();
    double timeDict = ((double) (t2-t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to load dictionary: ";
    cout << timeDict << endl;


    // prompt user for document to spellcheck
    cout << "Enter name of input file: ";
    cin >> filename;
    cout << "Enter name of output file: ";
    cin >> outfilename;

    input.close();
    ifstream spellInput(filename.c_str());

    ofstream output(outfilename.c_str());
    t1 = clock();
    int spellCheckSuccess = spellCheck(spellInput, output);
    t2 = clock();
    double timeSpellcheck = ((double) (t2-t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to check document: ";
    cout << timeSpellcheck << endl;

    return 0;
}

// returns true on success, false if error
bool loadDictionary(ifstream &dict_stream) {
    string word;
    while (getline(dict_stream, word)) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        dict.insert(word);
    }
    // for word in dictionary
    //      convert to lowercase
    //      insert into hash table
    return true;
}

int spellCheck(ifstream &input, ofstream &output) {
    // for word in document
    //      keep track of line number
    //      look up to see if word in dictionary
    //          if valid word, output
    //          if not valid word, output
    return 0;
}

// valid word
//      20 characters max length
//      no special characters
//      if special character, check word before and after
