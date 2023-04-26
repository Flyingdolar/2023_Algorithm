#include <algorithm>
#include <iostream>
using namespace std;

struct Line {
    int x, y;
};

bool seq(Line a, Line b) {
    if (a.x < b.x) return true;
    if (a.x == b.x && a.y > b.y) return true;
    return false;
}

int bSearch(int* tmp, int len, int val) {
    int left = 0, right = len - 1, mid;

    while (left <= right) {
        mid = (left + right) / 2;
        if (tmp[mid] < val)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return left;
}

int lis(Line* list, int len) {
    int tmp[len];
    int ldx = 1, pos;

    for (int ndx = 0; ndx < len; ndx++) tmp[ndx] = 0;
    tmp[0] = list[0].y;
    for (int ndx = 1; ndx < len; ndx++) {
        if (list[ndx].y > tmp[ldx - 1])
            tmp[ldx] = list[ndx].y, ldx++;
        else {
            pos = bSearch(tmp, ldx, list[ndx].y);
            tmp[pos] = list[ndx].y;
        }
    }
    return ldx;
}

int main() {
    int numX, numY, lineNum;
    Line* arrLine;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    cin >> numX >> numY >> lineNum;
    arrLine = new Line[lineNum];
    for (int idx = 0; idx < lineNum; idx++)
        cin >> arrLine[idx].x >> arrLine[idx].y;

    sort(arrLine, arrLine + lineNum, seq);
    lineNum = lis(arrLine, lineNum);
    cout << lineNum << endl;

    delete[] arrLine;
    return 0;
}
