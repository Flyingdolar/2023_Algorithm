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

// Find Minimum Spanning Tree
int MST() {
    int sum = 0, visNum = 0;
    int curCity = 0, minCost = MAXCOST;
    VI visCity(cityNum, false);
    VI cityCost(cityNum, MAXCOST);

    cityCost[0] = 0;
    while (visNum < cityNum) {
        visCity[curCity] = true, ++visNum;
        minCost = MAXCOST;
        for (auto cab : cabList) {
            if (cab[START] == curCity) {
                if (visCity[cab[END]]) continue;
                cityCost[cab[END]] = min(cityCost[cab[END]], cab[COST]);
            }
            if (cab[END] == curCity) {
                if (visCity[cab[START]]) continue;
                cityCost[cab[START]] = min(cityCost[cab[START]], cab[COST]);
            }
        }
        for (int idx = 0; idx < cityNum; idx++) {
            if (visCity[idx]) continue;
            if (cityCost[idx] < minCost) {
                minCost = cityCost[idx];
                curCity = idx;
            }
        }
    }
    for (auto cost : cityCost) sum += cost;
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
    // Calculate the mininum cost
    sum = MST();
    std::cout << sum << endl;
    return 0;
}
