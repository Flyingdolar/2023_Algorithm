#include <algorithm>
#include <iostream>
#include <vector>

#define VI vector<int>
#define MAXNUM 1000005

using namespace std;

int LIS(VI& arr) {
    int len = arr.size();
    int ldx = 1, pos;
    VI tmp(len, 0);

    if (len == 0) return 0;
    tmp[0] = arr[0];
    for (int ndx = 1; ndx < len; ndx++) {
        if (arr[ndx] > tmp[ldx - 1])
            tmp[ldx] = arr[ndx], ldx++;
        else {
            pos = lower_bound(tmp.begin(), tmp.begin() + ldx, arr[ndx]) - tmp.begin();
            tmp[pos] = arr[ndx];
        }
    }
    return ldx;
}

int main(void) {
    int airport, lines;
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

    for (int idx = 0; idx < arrList.size(); ++idx)
        cout << arrList[idx] << " ";
    cout << endl;
    arrList.erase(remove(arrList.begin(), arrList.end(), 0), arrList.end());
    for (int idx = 0; idx < arrList.size(); ++idx)
        cout << arrList[idx] << " ";
    cout << endl;
    lines = LIS(arrList);
    cout << lines << endl;
    return 0;
}
