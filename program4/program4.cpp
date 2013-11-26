#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    string inFilename, outFilename;
    cout << "Enter name of input file: ";
    cin >> inFilename;
    cout << "Enter name of output file: ";
    cin >> outFilename;
    ifstream in(inFilename.c_str());
    ofstream out(outFilename.c_str());

    string line, a, b, c;
    while (getline(in,a) && getline(in,b) && getline(in,c)) {

        cout << a << " " << b << " " << c << endl;

        // check if valid merge. write to output filestream properly.

    }

    in.close();
    out.close();
    return 0;
}
