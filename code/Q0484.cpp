#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Audio {
    int start, end;
    Audio(int s, int e) : start(s), end(e) {}
};

bool early(const Audio& a, const Audio& b) {
    if (a.start == b.start) {
        return a.end > b.end;
    }
    return a.start < b.start;
}

void necTrack(vector<Audio>& aList, int& trackNum, int& time) {
    int allTrack = trackNum;
    int allTime = time;
    int idx = 0, jdx, pEnd = 0;

    time = 0, trackNum = 0;
    while (idx < allTrack) {
        if (aList[idx].end == aList[idx].start) {
            idx++;
            continue;
        }
        if (aList[idx].start > pEnd) {
            trackNum++;
            time += aList[idx].start - pEnd;
            pEnd = aList[idx].end, idx++;
        } else {
            for (jdx = idx; jdx < allTrack; jdx++) {
                if (aList[jdx].start > pEnd) break;
                if (aList[jdx].end <= aList[idx].end) continue;
                idx = jdx;
            }
            if (aList[idx].end > pEnd) {
                pEnd = aList[idx].end;
                trackNum++;
            }
            idx = jdx;
        }
    }
    time += allTime - pEnd;
}

int main() {
    int audioNum, timeLen;
    vector<Audio> aList;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    cin >> audioNum >> timeLen;
    for (int i = 0; i < audioNum; i++) {
        int s, e;
        cin >> s >> e;
        aList.emplace_back(s, e);
    }

    sort(aList.begin(), aList.end(), early);
    necTrack(aList, audioNum, timeLen);
    cout << audioNum << " " << timeLen << "\n";

    return 0;
}
