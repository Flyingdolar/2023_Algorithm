#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

#define UNVISIT -1
#define SET first
#define LOW second

#define VI vector<int>
#define VB vector<bool>
#define VVI vector<VI>
#define PI pair<int, int>
#define VPI vector<PI>

using namespace std;

int posNum, roadNum;  // Amount of position and road
VVI roadMap;          // Road map: Record all road
VPI bridge;           // Bridge: Record all bridge

void findBridge() {
    VPI visTime(posNum, {UNVISIT, UNVISIT});  // Record visited time: {set, low}
    VI visNode;                               // Track visited node
    int time = 0;                             // Time

    for (int idx = 0; idx < posNum; idx++) {
        if (visTime[idx].SET != UNVISIT) continue;
        visNode.push_back(idx);
        while (!visNode.empty()) {
            int curNode = visNode.back(), prevNode = -1;
            if (visNode.size() > 1) prevNode = visNode.at(visNode.size() - 2);
            if (visTime[curNode].SET == UNVISIT)
                visTime[curNode].SET = visTime[curNode].LOW = time++;
            for (auto road : roadMap[curNode]) {
                if (visTime[road].SET != UNVISIT) {
                    if (road != prevNode)
                        visTime[curNode].LOW = min(visTime[curNode].LOW, visTime[road].SET);
                    continue;
                }
                visNode.push_back(road);
                break;
            }
            if (visNode.back() == curNode) {
                visNode.pop_back();
                if (prevNode != -1) {
                    visTime[prevNode].LOW = min(visTime[prevNode].LOW, visTime[curNode].LOW);
                    if (visTime[curNode].LOW > visTime[prevNode].SET) {
                        if (curNode > prevNode) swap(curNode, prevNode);
                        bridge.push_back({curNode, prevNode});
                    }
                }
            }
        }
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> posNum >> roadNum;

    roadMap.resize(posNum);
    int start, end;
    while (roadNum--) {
        cin >> start >> end;
        roadMap[start].push_back(end);
        roadMap[end].push_back(start);
    }

    findBridge();
    if (bridge.empty()) {
        cout << "No Critical Road" << endl;
        return 0;
    }
    sort(bridge.begin(), bridge.end(), [](PI roadA, PI roadB) {
        if (roadA.first == roadB.first) return roadA.second < roadB.second;
        return roadA.first < roadB.first;
    });
    for (auto road : bridge)
        cout << road.first << " " << road.second << endl;
    return 0;
}
