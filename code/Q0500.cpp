#include <iostream>
#include <vector>

#define VI vector<int>
#define VB vector<bool>
#define VVI vector<VI>
#define PII pair<int, int>
#define VPII vector<PII>

using namespace std;

void crtDFS(VVI roadMap, int pos, VB &visited, VB &critical, VI &stack) {
    stack.push_back(pos);
    visited[pos] = true;

    for (auto road : roadMap[pos]) {
        if (!visited[road]) {
            crtDFS(roadMap, road, visited, critical, stack);
            continue;
        }
        if (road != stack[stack.size() - 2]) {
            for (int idx = stack.size() - 1; idx >= 0; idx--) {
                critical[stack[idx]] = true;
                if (stack[idx] == road) break;
            }
        }
    }

    stack.pop_back();
    return;
}

VB strongConnect(VVI roadMap, int posNum) {
    VB critical(posNum, false), visited(posNum, false);
    VI stack;

    for (int idx = 0; idx < posNum; idx++) {
        if (visited[idx]) continue;
        crtDFS(roadMap, idx, visited, critical, stack);
    }

    return critical;
}

int main() {
    int posNum, roadNum;  // Amount of position and road
    int start, end;       // Start and end of road, List of position
    VVI roadMap;          // Road map: Record all road
    VB posList;           // Position list: Record all position(is critical or not)
    bool print = false;   // Print flag: Print the first line or not

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> posNum >> roadNum;

    roadMap.resize(posNum);
    while (roadNum--) {
        cin >> start >> end;
        roadMap[start].push_back(end);
        roadMap[end].push_back(start);
    }

    posList = strongConnect(roadMap, posNum);
    for (int idx = 0; idx < posNum; idx++) {
        if (posList[idx]) continue;
        print = true;
        for (auto road : roadMap[idx]) {
            if (road < idx && !posList[road]) continue;
            if (road < idx) cout << road << " " << idx << endl;
            if (road > idx) cout << idx << " " << road << endl;
        }
    }
    if (!print) cout << "No Critical Road" << endl;
    return 0;
}
