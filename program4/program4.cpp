#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

#define LEN 1001

int d[LEN][LEN] = {0};

/*
 *
 * Given an input file of the form
 *
 *      word_a1
 *      word_b1
 *      word_c1
 *      word_a2
 *      word_b2
 *      word_c2
 *      ...
 *
 * determine if the third word C is a valid merge
 * of the previous two words. C is a valid merge of
 * A and B if the order of letters is preserved in C.
 * Think of it like shuffling a deck of cards split into
 * A and B piles, where you want the shuffled deck C
 * to preserve the orders of A and B.
 *
 * Example of merge:    A: cat
 *                      B: dog
 *                      C: cadtog
 *
 * Example of !merge:   A: cat
 *                      B: dog
 *                      C: cagotd
 *
 * For a valid merge, the program outputs the merged word
 * with the letters of word A capitalized to the specified
 * output filestream. Letters in A are kept as left as possible
 * in the case that multiple valid merges are possible.
 *
 * Example:             A: aa
 *                      B: ba
 *                      C: abaa -> AbAa, not AbaA
 *
 * In the case of an invalid merge, the line
 *
 *      *** NOT A MERGE ***
 *
 * is written to the output filestream.
 *
 */
 int main() {
    string inFilename, outFilename;
    cout << "Enter name of input file: ";
    cin >> inFilename;
    cout << "Enter name of output file: ";
    cin >> outFilename;
    ifstream in(inFilename.c_str());
    ofstream out(outFilename.c_str());

    string a, b, c;
    while (getline(in,a) && getline(in,b) && getline(in,c)) {

        // initialize matrix
        for (int i=0; i<LEN; i++) {
            for (int j=0; j<LEN; j++) {
                d[i][j] = 0;
            }
        }
        d[0][0] = 1;

        int la = a.length();
        int lb = b.length();
        int lc = c.length();

        if (lc != la + lb) {
            out << "*** NOT A MERGE ***" << endl;
            continue;
        }

        // fill matrix to get merge paths
        for (int x=0; x<=la; x++) {
            for (int y=0; y<=lb; y++) {

                if (d[x][y] == 1) {

                    if (c[x+y] == a[x])
                        d[x+1][y] = 1;
                    if (c[x+y] == b[y])
                        d[x][y+1] = 1;

                }
            }
        }

        // merge condition, print string to output
        if (d[la][lb] == 1) {
            int i=la;
            int j=lb;
            while (i>0 && j>=0) {
                if (d[i][j] and (j == 0 or !d[i][j-1])) {
                    c[i+j-1] = toupper(c[i+j-1]);
                    i--;
                } else {
                    j--;
                }
            }
            out << c << endl;
        } else {
            out << "*** NOT A MERGE ***" << endl;
        }
    }

    in.close();
    out.close();
    return 0;
}
