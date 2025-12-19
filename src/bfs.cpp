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

Result BFS(const vector<string> &grid, pair<int,int> start, pair<int,int> goal) {
    int R = grid.size(), C = grid[0].size();
    vector<vector<int>> visited(R, vector<int>(C, 0));
    vector<vector<pair<int,int>>> parent(R, vector<pair<int,int>>(C, {-1,-1}));
    queue<pair<int,int>> q;

    int dr[4] = {-1,1,0,0};
    int dc[4] = {0,0,-1,1};

    Result res;
    res.found = false;
    res.nodesExpanded = 0;

    auto t1 = chrono::high_resolution_clock::now();

    q.push(start);
    visited[start.first][start.second] = 1;

    while (!q.empty()) {
        auto cur = q.front(); 
        q.pop();
        res.nodesExpanded++;

        if (cur == goal) {
            res.found = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nr = cur.first + dr[i];
            int nc = cur.second + dc[i];


            if (inBounds(nr, nc, R, C) && !visited[nr][nc] && grid[nr][nc] != '#') {
                visited[nr][nc] = 1;
                parent[nr][nc] = cur;
                q.push({nr, nc});
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