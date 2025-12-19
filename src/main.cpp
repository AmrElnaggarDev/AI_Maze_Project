#include <bits/stdc++.h>
using namespace std;


struct Result {
bool found;
int nodesExpanded;
int pathLength;
double timeMs;
vector<pair<int,int>> path;
};


Result BFS(const vector<string>&, pair<int,int>, pair<int,int>);
Result DFS(const vector<string>&, pair<int,int>, pair<int,int>);


int main() {


vector<string> maze = {
"###########",
"#S...#....#",
"#.#.#.##..#",
"#.#...#...#",
"#.###.#.#G#",
"#.....#...#",
"###########"
};


pair<int,int> start, goal;
for (int i = 0; i < maze.size(); i++)
for (int j = 0; j < maze[0].size(); j++) {
if (maze[i][j] == 'S') start = {i,j};
if (maze[i][j] == 'G') goal = {i,j};
}


cout << "Maze Pathfinding using BFS and DFS\n\n";


Result bfs = BFS(maze, start, goal);
Result dfs = DFS(maze, start, goal);


cout << "[BFS]\n";
cout << "Found: " << bfs.found << "\n";
cout << "Nodes Expanded: " << bfs.nodesExpanded << "\n";
cout << "Path Length: " << bfs.pathLength << "\n";
cout << "Time (ms): " << bfs.timeMs << "\n\n";


cout << "[DFS]\n";
cout << "Found: " << dfs.found << "\n";
cout << "Nodes Expanded: " << dfs.nodesExpanded << "\n";
cout << "Path Length: " << dfs.pathLength << "\n";
cout << "Time (ms): " << dfs.timeMs << "\n";


return 0;
}