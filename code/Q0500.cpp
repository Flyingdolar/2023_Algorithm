#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef enum _visit_ {
    ORIGIN = 0,
    DISCOVER = 1,
    FINISH = 2
} visit;

void toZero(int *arr, int size) {
    for (int idx = 0; idx < size; idx++)
        arr[idx] = 0;
    return;
}

int greatPair(pair<int, int> a, pair<int, int> b) {
    return a.second - b.second;
}

int main() {
    int placeNum, routeNum, start, end;
    pair<int, int> *road;
    vector<pair<int, int>> road, seq;

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> placeNum >> routeNum;

    return 0;
}
