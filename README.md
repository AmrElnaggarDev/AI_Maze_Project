# AI Maze Pathfinding Project

## Overview
This project solves a classic Maze Pathfinding Problem using two uninformed search algorithms:
- Breadth-First Search (BFS)
- Depth-First Search (DFS)

The project is implemented in C++ as part of the Artificial Intelligence course requirements.

---

## Problem Description
The maze is represented as a 2D grid where:
- **S** represents the Start cell
- **G** represents the Goal cell
- **.** represents a Free cell
- **#** represents a Wall

The agent can move only in four directions:
- Up
- Down
- Left
- Right

The objective is to find a valid path from the start cell to the goal cell.

---

## Implemented Algorithms

### 1. Breadth-First Search (BFS)
- Explores the maze level by level
- Guarantees finding the shortest path in an unweighted grid
- Uses a **queue (FIFO)** data structure

### 2. Depth-First Search (DFS)
- Explores the maze by going as deep as possible
- Does not guarantee the shortest path
- Uses a **stack (LIFO)** data structure

---

## Project Structure

AI_Maze_Project/
├── src/
│   ├── maze.cpp
│   ├── bfs.cpp
│   ├── dfs.cpp
│   └── main.cpp
├── AiReport.pdf
├── TeamContribuation.txt
└── README.md

---

## How to Compile
Use the following command to compile the project:

```bash
g++ -std=c++17 -O2 -o maze src/main.cpp src/maze.cpp src/bfs.cpp src/dfs.cpp
