#include <bits/stdc++.h>

using namespace std;

extern bool inBounds(int r, int c, int R, int C);

extern vector<pair<int,int>> reconstructPath(
    pair<int,int> start,
    pair<int,int> goal,
    vector<vector<pair<int,int>>> &parent
);

struct Result {
    bool found;
    int nodesExpanded;
    int pathLength;
    double timeMs;
    vector<pair<int,int>> path;
};

Result DFS(const vector<string> &grid, pair<int,int> start, pair<int,int> goal) {

    int R = grid.size(), C = grid[0].size();
    vector<vector<int>> visited(R, vector<int>(C, 0));
    vector<vector<pair<int,int>>> parent(R, vector<pair<int,int>>(C, {-1,-1}));
    stack<pair<int,int>> st;

    int dr[4] = {-1,1,0,0};
    int dc[4] = {0,0,-1,1};

    Result res;
    res.found = false;
    res.nodesExpanded = 0;

    auto t1 = chrono::high_resolution_clock::now();

    st.push(start);

    while (!st.empty()) {
        auto cur = st.top(); 
        st.pop();

        if (visited[cur.first][cur.second]) continue;
        visited[cur.first][cur.second] = 1;
        res.nodesExpanded++;

        if (cur == goal) {
            res.found = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nr = cur.first + dr[i];
            int nc = cur.second + dc[i];

            if (inBounds(nr, nc, R, C) && !visited[nr][nc] && grid[nr][nc] != '#') {
                parent[nr][nc] = cur;
                st.push({nr, nc});
            }
        }
    }

    auto t2 = chrono::high_resolution_clock::now();
    res.timeMs = chrono::duration<double, milli>(t2 - t1).count();

    if (res.found) {
        res.path = reconstructPath(start, goal, parent);
        res.pathLength = res.path.size() - 1;
    } else {
        res.pathLength = -1;
    }

    return res;
}