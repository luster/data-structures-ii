#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> data;
    data.resize(40);
    data[1] = 1;

    cout << data.size() << endl;
    return 0;
}
