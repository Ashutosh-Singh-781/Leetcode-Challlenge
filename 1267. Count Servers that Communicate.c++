/*
# 1267. Count Servers that Communicate

- **Difficulty:** Medium
- **Topic:** Array, Matrix, Counting
- **Language:** C++
- **LeetCode Link:** [Count Servers that Communicate](https://leetcode.com/problems/count-servers-that-communicate/)

## Problem Statement
You are given a map of a server center, represented as a `m x n` integer matrix `grid`, where 1 means that on that cell there is a server and 0 means that it is empty. Two servers are said to communicate if they are on the same row or on the same column. Return the number of servers that communicate with any other server.

## Intuition & Approach
1. **Row and Column Frequency Count:** First, iterate through the entire grid to count how many servers are present in each row and each column.
2. **Communication Check:** A server at `(i, j)` can communicate with at least one other server if and only if there is another server in its row (`rows[i] > 1`) or in its column (`cols[j] > 1`). 
3. Since `rows[i]` and `cols[j]` both include the server at `(i, j)`, the condition `rows[i] + cols[j] > 2` ensures that the server shares its row or column with at least one other server.

## Complexity Analysis
- **Time Complexity:** $O(M \times N)$ — We iterate through the grid twice: once to calculate row and column counts, and once to check each server.
- **Space Complexity:** $O(M + N)$ — To store the counts of servers in each of the $M$ rows and $N$ columns.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        const int m = grid.size(), n = grid[0].size();
        vector<int> rows(m), cols(n);  // servers on each row and column
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j) {
                rows[i] += grid[i][j];
                cols[j] += grid[i][j];
            }

        int ans = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (grid[i][j] && rows[i] + cols[j] > 2)  // it's counted in both, so more than 2 means company
                    ++ans;
        return ans;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid = {{1, 0}, {1, 1}};
    cout << sol.countServers(grid) << endl;
    return 0;
}