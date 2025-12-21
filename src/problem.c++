#include <bits/stdc++.h>
using namespace std;

struct Cell {
    int r, c;
};

static const vector<Cell> DIRS = {
    {1, 0},  
    {-1, 0}, 
    {0, 1},  
    {0, -1} 
};

bool inside(int r, int c, int n, int m) {
    return r >= 0 && r < n && c >= 0 && c < m;
}

vector<Cell> buildPath(vector<vector<Cell>>& parent, Cell start, Cell goal) {
    vector<Cell> path;
    Cell cur = goal;

    while (!(cur.r == -1 && cur.c == -1)) {
        path.push_back(cur);
        if (cur.r == start.r && cur.c == start.c) break;
        cur = parent[cur.r][cur.c];
    }

    if (path.empty() || !(path.back().r == start.r && path.back().c == start.c)) {
        return {}; 
    }

    reverse(path.begin(), path.end());
    return path;
}

vector<Cell> bfsSolve(const vector<string>& grid, Cell start, Cell goal, int& visitedCount) {
    int n = (int)grid.size(), m = (int)grid[0].size();
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    vector<vector<Cell>> parent(n, vector<Cell>(m, {-1, -1}));
    queue<Cell> q;

    q.push(start);
    vis[start.r][start.c] = true;
    visitedCount = 1;

    while (!q.empty()) {
        Cell cur = q.front(); q.pop();

        if (cur.r == goal.r && cur.c == goal.c) break;

        for (auto d : DIRS) {
            int nr = cur.r + d.r;
            int nc = cur.c + d.c;

            if (!inside(nr, nc, n, m)) continue;
            if (vis[nr][nc]) continue;
            if (grid[nr][nc] == '#') continue;

            vis[nr][nc] = true;
            visitedCount++;
            parent[nr][nc] = cur;
            q.push({nr, nc});
        }
    }

    return buildPath(parent, start, goal);
}

vector<Cell> dfsSolve(const vector<string>& grid, Cell start, Cell goal, int& visitedCount) {
    int n = (int)grid.size(), m = (int)grid[0].size();
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    vector<vector<Cell>> parent(n, vector<Cell>(m, {-1, -1}));
    stack<Cell> st;

    st.push(start);
    vis[start.r][start.c] = true;
    visitedCount = 1;

    while (!st.empty()) {
        Cell cur = st.top(); st.pop();

        if (cur.r == goal.r && cur.c == goal.c) break;

        for (auto d : DIRS) {
            int nr = cur.r + d.r;
            int nc = cur.c + d.c;

            if (!inside(nr, nc, n, m)) continue;
            if (vis[nr][nc]) continue;
            if (grid[nr][nc] == '#') continue;

            vis[nr][nc] = true;
            visitedCount++;
            parent[nr][nc] = cur;
            st.push({nr, nc});
        }
    }

    return buildPath(parent, start, goal);
}

void printGrid(const vector<string>& grid) {
    for (auto& row : grid) cout << row << "\n";
}

vector<string> drawPath(vector<string> grid, const vector<Cell>& path, Cell start, Cell goal) {
    for (auto& p : path) {
        if ((p.r == start.r && p.c == start.c) || (p.r == goal.r && p.c == goal.c)) continue;
        if (grid[p.r][p.c] == '.') grid[p.r][p.c] = '*';
    }
    return grid;
}

bool findStartGoal(const vector<string>& grid, Cell& start, Cell& goal) {
    int n = (int)grid.size(), m = (int)grid[0].size();
    bool s = false, g = false;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (grid[r][c] == 'S') { start = {r, c}; s = true; }
            if (grid[r][c] == 'G') { goal  = {r, c}; g = true; }
        }
    }
    return s && g;
}

int main() {
    vector<string> grid = {
        "###########",
        "#S#...#...#",
        "#.#.#.#.#.#",
        "#...#...#G#",
        "###########"
    };

    Cell start{-1,-1}, goal{-1,-1};
    if (!findStartGoal(grid, start, goal)) {
        cout << "Error: Maze must contain 'S' (start) and 'G' (goal)\n";
        return 0;
    }

    cout << "Original Maze:\n";
    printGrid(grid);
    cout << "\n";

    int bfsVisited = 0, dfsVisited = 0;
auto bfsPath = bfsSolve(grid, start, goal, bfsVisited);
    auto dfsPath = dfsSolve(grid, start, goal, dfsVisited);

    // BFS Output
    cout << "===== BFS Result (Shortest in unweighted grid) =====\n";
    if (bfsPath.empty()) {
        cout << "No path found.\n";
    } else {
        cout << "Path length (steps): " << (int)bfsPath.size() - 1 << "\n";
        cout << "Visited nodes: " << bfsVisited << "\n\n";
        auto out = drawPath(grid, bfsPath, start, goal);
        printGrid(out);
        cout << "\n";
    }

    // DFS Output
    cout << "===== DFS Result (Not guaranteed shortest) =====\n";
    if (dfsPath.empty()) {
        cout << "No path found.\n";
    } else {
        cout << "Path length (steps): " << (int)dfsPath.size() - 1 << "\n";
        cout << "Visited nodes: " << dfsVisited << "\n\n";
        auto out = drawPath(grid, dfsPath, start, goal);
        printGrid(out);
        cout << "\n";
    }

    return 0;
}