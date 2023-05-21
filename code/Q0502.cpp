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
#define VVPI vector<VPI>

#define START 0
#define END 1
#define COST 2
#define MAXCOST 1000000000

typedef enum _method_ {
    MIN = 0,
    MAX = 1
} meth;

int cityNum, cabNum;  // Amount of city and cable
VVI cabList;          // Cable list: Record all cable

// Minimum or Maximum Spanning Tree
VI MST(meth M = MIN, int limit = -1) {
    int visNum = 0;
    int curCity = 0, edgeCost;
    VI visCity(cityNum, false);
    VI cityCost(cityNum, MAXCOST);
    VVPI adjMap(cityNum);

    if (M) fill(cityCost.begin(), cityCost.end(), -1);
    if (limit == -1 && M) limit = MAXCOST;
    for (auto cab : cabList) {
        adjMap[cab[START]].push_back({cab[END], cab[COST]});
        adjMap[cab[END]].push_back({cab[START], cab[COST]});
    }

    cityCost[0] = 0;
    while (visNum < cityNum) {
        visCity[curCity] = true, ++visNum;
        edgeCost = M ? -1 : MAXCOST;
        for (auto cable : adjMap[curCity]) {
            if (visCity[cable.first]) continue;
            if (M && cable.second > limit) continue;
            if (!M && cable.second < limit) continue;
            cityCost[cable.first] = M ? max(cityCost[cable.first], cable.second)
                                      : min(cityCost[cable.first], cable.second);
        }
        for (int idx = 0; idx < cityNum; idx++) {
            if (visCity[idx]) continue;
            if (M && cityCost[idx] < edgeCost) continue;
            if (!M && cityCost[idx] > edgeCost) continue;
            edgeCost = cityCost[idx];
            curCity = idx;
        }
    }
    return cityCost;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int cityA, cityB;
    int cost, limit, sum = 0;
    VI costList;

    cin >> cityNum >> cabNum;
    cabList.resize(cabNum);
    for (int idx = 0; idx < cabNum; idx++) {
        cin >> cityA >> cityB >> cost;
        cityA -= 1, cityB -= 1;
        cabList[idx] = {cityA, cityB, cost};
    }

    // Calculate the maximum cost
    costList = MST(MAX);
    limit = min_element(costList.begin() + 1, costList.end())[0];
    // Calculate the minimum cost
    costList = MST(MIN, limit);
    for (auto cost : costList) sum += cost;
    std::cout << sum << endl;
    return 0;
}
