// Ethan Lusterman
// ECE165, Fall 2013

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include "hash.h"

using namespace std;

hashTable dict(100000);

void loadDictionary(ifstream &dict_file);
int spellCheck(ifstream &input, ofstream &output);

int main() {

    // prompt user for dict file
    string filename, outfilename;
    cout << "Enter name of dictionary: ";
    cin >> filename;

    // create input filestream 
    ifstream input(filename.c_str());
    if (!input) {
        cerr << "Error: could not open " << filename << endl;
        exit(1);
    }

    // time dictionary load
    clock_t t1 = clock();
    loadDictionary(input);
    clock_t t2 = clock();

    double timeDict = ((double) (t2-t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to load dictionary: ";
    cout << timeDict << endl;

    input.close();

    // prompt user for document to spellcheck
    cout << "Enter name of input file: ";
    cin >> filename;
    cout << "Enter name of output file: ";
    cin >> outfilename;

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

void loadDictionary(ifstream &dict_stream) {
    string word;
    while (getline(dict_stream, word)) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        dict.insert(word);
    }
    return;
}

int spellCheck(ifstream &input, ofstream &output) {
    string valid_char="abcdefghijklmnopqrstuvwxyz0123456789\'-";
    string digits="0123456789";
    string line, word;
    int lineNo = 1, start, end;

    while (getline(input, line)) {
        // make lowercase
        transform(line.begin(), line.end(), line.begin(), ::tolower);

        // skip blank lines
        if (line=="") {
            lineNo++;
            continue;
        }

        // spaces and other invalid characters are word separators, check all
        start = line.find_first_of(valid_char);
        while (start != string::npos) {
            end = line.find_first_not_of(valid_char, start);
            word = line.substr(start,end-start);
            start = line.find_first_of(valid_char, end);

            // word with numbers are skipped
            if (word.find_first_of(digits) != string::npos)
                continue;

            // word longer than 20 characters
            else if (word.length() > 20) {
                output << "Long word at line ";
                output << lineNo;
                output << ", starts: ";
                output << word.substr(0,20) << endl;
            }

            // word not in dictionary
            else if (!dict.contains(word)) {
                output << "Unknown word at line ";
                output << lineNo;
                output << ": " << word << endl;
            }

            // break if end of the line
            if (end == string::npos)
                break;
        }

        lineNo++;
    }
    return 0;
}
