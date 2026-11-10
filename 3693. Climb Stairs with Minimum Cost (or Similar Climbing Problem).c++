
/*
# 3693. Climb Stairs with Minimum Cost (or Similar Climbing Problem)

- **Difficulty:** Medium
- **Topic:** Dynamic Programming, Array
- **Language:** C++
- **LeetCode Link:** [LeetCode Problem](https://leetcode.com/problems/)

## Problem Statement
You are climbing a staircase with `n` steps, and for each step you have an associated cost. You can take varying step sizes (with corresponding penalties/costs for each step size) to reach the top. Return the minimum cost to climb to the top.

## Intuition & Approach
1. **Dynamic Programming (Bottom-Up / Backward):** We can compute the minimum cost from step `i` to the top by looking ahead at the possible next steps (`i + 1`, `i + 2`, `i + 3`).
2. **Space Optimization:** Instead of maintaining a full DP table of size $N$, we only need to keep track of the last three states (`a`, `b`, `c`) representing `dp[i + 1]`, `dp[i + 2]`, and `dp[i + 3]`, reducing the space complexity to $O(1)$.

## Complexity Analysis
- **Time Complexity:** $O(N)$ — We iterate backwards through the `n` steps once.
- **Space Complexity:** $O(1)$ — Only a few variables are used to maintain the rolling DP state.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        costs.insert(costs.begin(), 0);
        int a = costs[n], b = INT_MAX / 2, c = INT_MAX / 2;  // dp[i + 1], dp[i + 2], dp[i + 3] for i = n - 1
        for (int i = n - 1; i >= 0; --i) {
            int cur = costs[i] + min({a + 1, b + 4, c + 9});  // dp[i]
            c = b, b = a, a = cur;
        }
        return a;
    }
};

int main() {
    Solution sol;
    vector<int> costs = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    int n = 3;
    cout << sol.climbStairs(n, costs) << endl;
    return 0;
}