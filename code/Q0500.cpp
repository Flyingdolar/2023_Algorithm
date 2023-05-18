#include <iostream>
#include <vector>

#define VPII vector<pair<int, int>>

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

void DFS(VPII roadList, VPII stack, int *visit, int &time, VPII &finish) {
    int curPos = stack.back().first;

    visit[curPos] = DISCOVER, time++;
    for (auto road : roadList) {
        if (road.first == curPos && visit[road.second] == ORIGIN) {
            stack.push_back(make_pair(road.second, time));
            DFS(roadList, stack, visit, time, finish);
        }
    }
    visit[curPos] = FINISH, time++;
    finish.push_back(stack.back());
    finish.back().second = time;
    stack.pop_back();
    return;
}

// Do DFS and setup the value of pos by the order of finish time
void setDFS(VPII &roadList, VPII &posList) {
    int time = 0;
    int *visit = new int[posList.size()];
    VPII stack, finish;

    toZero(visit, posList.size());
    for (auto pos : posList) {
        if (visit[pos.first] == ORIGIN) {
            stack.push_back(make_pair(pos.first, time));
            DFS(roadList, stack, visit, time, finish);
        }
    }

    sort(finish.begin(), finish.end(), greatPair);
    for (size_t idx = 0; idx < posList.size(); idx++) {
        posList[idx].first = finish[idx].first;
        posList[idx].second = finish[idx].second;
    }
    delete[] visit;
    return;
}

int main() {
    int posNum, roadNum, start, end;
    // Data format: Road(Start, End), Pos(Number, Value)
    VPII road, pos;

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> posNum >> roadNum;

    for (int idx = 0; idx < roadNum; idx++) {
        cin >> start >> end;
        road.push_back(make_pair(start, end));
    }
    for (int idx = 0; idx < posNum; idx++) {
        pos.push_back(make_pair(idx, 0));
    }

    setDFS(road, pos);
    for (auto p : pos) {
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}
