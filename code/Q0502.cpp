#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

#define VI vector<int>
#define VB vector<bool>
#define VVI vector<VI>
#define PI pair<int, int>
#define VPI vector<PI>

#define START 0
#define END 1
#define COST 2
#define MAXCOST 1000000000

int cityNum, cabNum;  // Amount of city and cable
VI cityList;          // Record all cost of cities
VVI cabList;          // Cable list: Record all cable
VVI adjMap;           // Adjacent map: Record all cable that connect to specific city

// Compare Less Cost
bool cmpCost(VI &cableA, VI &cableB) {
    return cableA[COST] < cableB[COST];
}

bool isBridge(VI cable) {
    int curCity = cable[START];
    VB visCity(cityNum, false);
    VI stack;

    visCity[cable[START]] = true, visCity[cable[END]] = true;
    stack.push_back(cable[START]);
    for (auto cab : adjMap[cable[START]]) {
        if (cab == cable[END]) continue;
        if (visCity[cab]) continue;
        stack.push_back(cab);
        while (stack.size() > 1) {
            curCity = stack.back();
            visCity[curCity] = true;
            for (auto nextCab : adjMap[curCity]) {
                if (nextCab == cable[END]) return false;
                if (visCity[nextCab]) continue;
                stack.push_back(nextCab);
                break;
            }
            if (stack.back() == curCity) stack.pop_back();
        }
    }
    return true;
}

int findCost(int cityA, int cityB) {
    int cost = MAXCOST;
    for (auto cab : cabList) {
        if ((cab[START] == cityA && cab[END] == cityB) || (cab[START] == cityB && cab[END] == cityA)) {
            cost = cab[COST];
            break;
        }
    }
    return cost;
}

int shortPath() {
    int sum = 0, cost;
    int curCity = START;
    VI visCity(cityNum, false);
    VI stack;

    // Setup cost of all nodes
    visCity[START] = true, cityList[START] = 0;
    stack.push_back(START);
    while (!stack.empty()) {
        curCity = stack.back();
        for (auto childCity : adjMap[curCity]) {
            cost = cityList[curCity];
            cost += findCost(curCity, childCity);
            if (cost < cityList[childCity])
                cityList[childCity] = cost;
        }
        for (auto nextCity : adjMap[curCity]) {
            if (visCity[nextCity]) continue;
            stack.push_back(nextCity);
            visCity[nextCity] = true;
            break;
        }
        if (stack.back() == curCity) stack.pop_back();
    }

    // Count shortest path cost by DFS
    visCity = VI(cityNum, false), visCity[START] = true;
    stack.push_back(START);
    while (!stack.empty()) {
        curCity = stack.back();
        for (auto nextCity : adjMap[curCity]) {
            if (visCity[nextCity]) continue;
            cost = cityList[curCity];
            cost += findCost(curCity, nextCity);
            if (cityList[nextCity] == cost) {
                cost -= cityList[curCity];
                std::cout << curCity + 1 << " -> " << nextCity + 1 << " :: " << cost << endl;
                stack.push_back(nextCity);
                visCity[nextCity] = true;
                sum += cost;
                break;
            }
        }
        if (stack.back() == curCity) stack.pop_back();
    }

    return sum;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int cityA, cityB, cost, sum = 0;

    cin >> cityNum >> cabNum;
    cabList.resize(cabNum), adjMap.resize(cityNum);
    cityList.resize(cityNum, MAXCOST);
    for (int idx = 0; idx < cabNum; idx++) {
        cin >> cityA >> cityB >> cost;
        cityA -= 1, cityB -= 1;
        cabList[idx] = {cityA, cityB, cost};
        adjMap[cityA].push_back(cityB), adjMap[cityB].push_back(cityA);
    }
    // Sort cabList by cost (Ascending)
    sort(cabList.begin(), cabList.end(), cmpCost);
    while (cabList.size() > 0) {
        VI cable = cabList.front();
        if (isBridge(cable)) break;
        remove(adjMap[cable[START]].begin(), adjMap[cable[START]].end(), cable[END]);
        remove(adjMap[cable[END]].begin(), adjMap[cable[END]].end(), cable[START]);
        adjMap[cable[START]].pop_back(), adjMap[cable[END]].pop_back();
        cabList.erase(cabList.begin());
    }

    sum = shortPath();
    std::cout << sum << endl;

    // for (auto cable : cabList) sum += cable[COST];
    // cout << sum << endl;
    return 0;
}
