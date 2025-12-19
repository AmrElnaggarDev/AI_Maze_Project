#include <bits/stdc++.h>
using namespace std;

bool inBounds(int r, int c, int R, int C) {
    return r >= 0 && r < R && c >= 0 && c < C;
}

vector<pair<int,int>> reconstructPath(
    pair<int,int> start,
    pair<int,int> goal,
    vector<vector<pair<int,int>>> &parent
) {
    vector<pair<int,int>> path;
    pair<int,int> cur = goal;

    if (cur != start && parent[cur.first][cur.second] == make_pair(-1, -1))
        return {};

    while (cur != start) {
        path.push_back(cur);
        cur = parent[cur.first][cur.second];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}