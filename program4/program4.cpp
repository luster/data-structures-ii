#include <iostream>
#include <fstream>
#include <string>

using namespace std;



int main() {
    string inFilename;
    cout << "Enter name of input file: ";
    cin >> inFilename;
    ifstream in(inFilename.c_str());

    string line, a, b, c;
    while (in.good()) {
        getline(in,a);
        getline(in,b);
        getline(in,c);

        cout << a << " " << b << " " << c << endl;
    }

    return 0;
}
