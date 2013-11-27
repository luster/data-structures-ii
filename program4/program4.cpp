#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#define LEN 1001

int d[LEN][LEN] = {0};

int main() {
    string inFilename, outFilename;
    cout << "Enter name of input file: ";
    cin >> inFilename;
//    cout << "Enter name of output file: ";
//    cin >> outFilename;
    ifstream in(inFilename.c_str());
//    ofstream out(outFilename.c_str());

    bool isMerge = true;

    string line, a, b, c;
    while (getline(in,a) && getline(in,b) && getline(in,c)) {
//        cout << a << endl; cout << b << endl; cout << c << endl;

        // initialize
        for (int i=0; i<LEN; i++) {
            for (int j=0; j<LEN; j++) {
                d[i][j] = 0;
            }
        }
        d[0][0] = 1;

        int i=0;
        int j=0;
        int k=0;

        int la = a.length();
        int lb = b.length();
        int lc = c.length();

        isMerge = true;

        for (int x=0; x<=la; x++) {
            for (int y=0; y<=lb; y++) {
                if (d[x][y] == 1) {
                    if (c[x+y] == a[x])
                        d[x+1][y] = 1;
                    if (c[x+y] == b[y])
                        d[x][y+1] = 1;
                } else {
                    //break;
                }

            // print matrix
//            for (int p=0; p<la+1; p++) {
//                for (int q=0; q<lb+1; q++) {
//                    cout << d[p][q] << " ";
//                } cout << endl;
//            }
//            cout << endl;

            }
        }
        if (d[la][lb] == 1) {
            cout << "MERGE" << endl;
        } else {
            cout << "NOT A MERGE" << endl;
        }
    }



//        while (isMerge) {
//            // print matrix to test
//            for (int x=0; x<la+1; x++) {
//                for (int y=0; y<lb+1; y++) {
//                    cout << d[x][y] << " ";
//                } cout << endl;
//            }
//            cout << endl;
//
//            if (lc != la + lb) {
//                cout << "*** NOT A MERGE ***" << endl;
//                isMerge = false;
//            }
//            if (c[k] == a[i] && c[k] == b[j]) {
//                d[i+1][j] = 1;
//                d[i][j+1] = 1;
//                i++;
//                j++;
//                k++;
//            } else if (c[k] == a[i]) {
//                d[++i][j] = 1;
//                k++;
//            } else if (c[k] == b[j]) {
//                d[i][++j] = 1;
//                k++;
//            } else {
//                cout << "*** NOT A MERGE ***" << endl;
//                isMerge = false;
//            }
//            cout << i << j << k << endl;
//
//            if (d[la][lb] == 1) {
//                for (int x=0; x<la+1; x++) {
//                    for (int y=0; y<lb+1; y++) {
//                        cout << d[x][y] << " ";
//                    } cout << endl;
//                }
//                cout << "*** MERGE!! ***" << endl;
//                break;
//            }


      //  }
    //}

    in.close();
//    out.close();
    return 0;
}
