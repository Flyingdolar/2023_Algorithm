#include <algorithm>
#include <iostream>
#include <vector>

#define VI vector<int>
#define MAXNUM 1000005

using namespace std;

int main(void) {
    int airport;
    int depNum, arrNum;    // Amount of the Departure & Arrival Airport
    VI depPos(MAXNUM, 0);  // The list of the Department Airport (In Airport Location)
    VI arrList;            // The list of the Arrival Airport (In Airport ID num)

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> depNum >> arrNum;
    for (int idx = 0; idx < depNum; ++idx)
        cin >> airport, depPos[airport] = idx;
    for (int idx = 0; idx < arrNum; ++idx)
        cin >> airport, arrList.push_back(depPos[airport]);

    return 0;
}
