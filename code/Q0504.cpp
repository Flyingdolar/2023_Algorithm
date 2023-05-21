#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define VI vector<int>
#define VB vector<bool>
#define VVI vector<VI>
#define PI pair<int, int>
#define VPI vector<PI>
#define VVPI vector<VPI>

int ballNum, hitNum;
VI hitList;
VVI adjMap;

void setHitMap() {
    for (int idx = 1; idx < hitNum; idx++) {
        if (hitList[idx] > hitList[idx - 1])
            adjMap[hitList[idx]].push_back(hitList[idx - 1]);
    }
    return;
}

int findSplit() {
    int splitNum = 0, stPos = 0;

    for (int curPos = 1; curPos < ballNum; curPos++) {
        for (auto backPos : adjMap[curPos]) {
            if (backPos < stPos) continue;
            stPos = curPos, splitNum++;
            break;
        }
    }
    return splitNum;
}

int main(void) {
    cin >> ballNum >> hitNum;
    hitList.resize(hitNum), adjMap.resize(ballNum);
    for (int idx = 0; idx < hitNum; idx++) cin >> hitList[idx], --hitList[idx];
    setHitMap();

    int groupNum = findSplit() + 1;
    cout << groupNum << endl;
    return 0;
}
