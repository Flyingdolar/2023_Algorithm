#include <algorithm>
#include <iostream>
#include <vector>

#define ORIGIN 0
#define DISCOVER 1
#define FINISH 2

#define VI vector<int>
#define VB vector<bool>
#define VVI vector<VI>
#define PI pair<int, int>
#define VPI vector<PI>

using namespace std;

void DFS(VVI roadMap, int pos, VI &visited, VVI &stack, VPI &reqRoute) {
    visited[pos] = DISCOVER;

    for (auto road : roadMap[pos]) {
        if (visited[road] == FINISH) continue;
        if (visited[road] == DISCOVER && !stack.empty()) {
            if (stack.back().at(0) == road) continue;
            for (int idx = stack.size() - 1; idx >= 0; idx--) {
                stack[idx].at(2) = -1;
                if (stack[idx].at(0) == road) break;
            }
            continue;
        }
        stack.push_back({pos, road, 0});
        DFS(roadMap, road, visited, stack, reqRoute);
    }
    if (!stack.empty()) {
        if (stack.back().at(2) >= 0) {
            if (stack.back().at(0) > stack.back().at(1))
                swap(stack.back().at(0), stack.back().at(1));
            reqRoute.push_back({stack.back().at(0), stack.back().at(1)});
        }
        stack.pop_back();
        visited[pos] = FINISH;
    }
    return;
}

void findBridge(VVI roadMap, int posNum, VPI &reqRoute) {
    VI visited(posNum, ORIGIN);
    VVI stack;

    for (int idx = 0; idx < posNum; idx++) {
        if (visited[idx] == false)
            DFS(roadMap, idx, visited, stack, reqRoute);
    }

    return;
}

int main() {
    int posNum, roadNum;  // Amount of position and road
    int start, end;       // Start and end of road, List of position
    VVI roadMap;          // Road map: Record all road
    VPI reqRoute;         // Required route: Record route that is necessary.

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> posNum >> roadNum;

    roadMap.resize(posNum);
    while (roadNum--) {
        cin >> start >> end;
        roadMap[start].push_back(end);
        roadMap[end].push_back(start);
    }

    findBridge(roadMap, posNum, reqRoute);
    if (reqRoute.empty()) {
        cout << "No Critical Road" << endl;
        return 0;
    }
    sort(reqRoute.begin(), reqRoute.end(), [](PI roadA, PI roadB) {
        if (roadA.first == roadB.first) return roadA.second < roadB.second;
        return roadA.first < roadB.first;
    });
    for (auto road : reqRoute)
        cout << road.first << " " << road.second << endl;
    return 0;
}
