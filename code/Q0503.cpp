#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

#define H first
#define W second
#define VI vector<int>
#define VVI vector<vector<int>>
#define PII pair<int, int>
#define VPII vector<pair<int, int>>
#define ETERNAL 2000  // The time that the lava will never cover the map.
#define UNCOVER -1    // The block that is still not covered by lava will be marked as -1.
#define COVERED 0     // The block that is covered by lava will be marked as 0.

const VI allDir = {0, 1, 2, 3};
const VPII moveDir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

// Check if the coordinate is out of the map.
bool overFlow(PII &pos, int mapH, int mapW) {
    return pos.first < 0 || pos.first >= mapH || pos.second < 0 || pos.second >= mapW;
}

// Record the time of all Lava Spread
int sprLava(VVI &mapStat, queue<PII> &newLava) {
    int mapW = mapStat[0].size(), mapH = mapStat.size();
    int queSize;
    int time = 0;  // The time that the lava will cover the map.
    PII newPos;    // The coordinate of the new lava block.

    while (!newLava.empty()) {
        queSize = newLava.size(), ++time;
        for (int idx = 0; idx < queSize; ++idx) {
            PII curLava = newLava.front();
            newLava.pop();
            for (int dir : allDir) {
                newPos.H = curLava.H + moveDir[dir].H;
                newPos.W = curLava.W + moveDir[dir].W;
                if (overFlow(newPos, mapH, mapW)) continue;
                if (mapStat[newPos.H][newPos.W] == UNCOVER) {
                    mapStat[newPos.H][newPos.W] = time;
                    newLava.push(newPos);
                }
            }
        }
    }
    // Return the time that the lava will cover the map.
    return time;
}

bool DFS(VVI &mapStat, stack<PII> &route, PII &goal, int time) {
    int mapW = mapStat[0].size(), mapH = mapStat.size();
    PII curPos = route.top(), newPos;  // The current position and the new position.

    if (curPos == goal) return true;
    for (int dir : allDir) {
        newPos.H = curPos.H + moveDir[dir].H;
        newPos.W = curPos.W + moveDir[dir].W;
        if (overFlow(newPos, mapH, mapW)) continue;
        if (mapStat[newPos.H][newPos.W] > time) {
            route.push(newPos), mapStat[newPos.H][newPos.W] = COVERED;
            if (DFS(mapStat, route, goal, time)) return true;
            route.pop();
        }
    }
    return false;
}

// Check if the path is valid.
bool findPath(VVI mapStat, PII stPt, PII edPt, int time) {
    stack<PII> route;  // Use DFS to find the path.
    route.push(stPt), mapStat[stPt.H][stPt.W] = COVERED;
    return DFS(mapStat, route, edPt, time);  // Recursion version
}

int main(void) {
    int mapW, mapH;          // Width and Height of the map.
    int stTime = 0, edTime;  // The time that the lava will cover the map.
    char text;               // Temporary variable for input.
    VVI mapStat;             // number stand for the time when will covered by lava.
    queue<PII> newLava;      // Save all Lava that's unsprayed.
    PII stPt, edPt;          // Start Point and End Point.

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> mapH >> mapW;
    mapStat.resize(mapH);
    for (int hdx = 0; hdx < mapH; ++hdx) {
        mapStat[hdx].resize(mapW);
        for (int wdx = 0; wdx < mapW; ++wdx) {
            cin >> text;
            switch (text) {
                case 'L':  // Lava Blocks
                    mapStat[hdx][wdx] = COVERED;
                    newLava.push({hdx, wdx});
                    break;
                case 'O':  // Obsidian Blocks
                    mapStat[hdx][wdx] = COVERED;
                    break;
                case 'B':  // Start Point
                    mapStat[hdx][wdx] = ETERNAL;
                    stPt = {hdx, wdx};
                    break;
                case 'D':  // End Point
                    mapStat[hdx][wdx] = ETERNAL;
                    edPt = {hdx, wdx};
                    break;
                default:  // Normal Floor
                    mapStat[hdx][wdx] = UNCOVER;
                    break;
            }
        }
    }

    // Record the time of all Lava Spread
    edTime = sprLava(mapStat, newLava);

    // Find if there is a path from Start Point to End Point at the specific time
    while (stTime != edTime) {
        int time = (stTime + edTime) / 2;
        if (findPath(mapStat, stPt, edPt, time))
            stTime = time + 1;
        else
            edTime = time;
    }
    stTime -= 1;
    if (stTime == 0) stTime = -1;
    cout << stTime << endl;
    return 0;
}
