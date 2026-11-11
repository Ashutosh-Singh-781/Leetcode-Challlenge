/*
# 3789. Minimum Cost to Satisfy Requests / Minimum Cost to Acquire Items with Bundles

- **Difficulty:** Medium / Hard
- **Topic:** Math, Greedy, Combinatorics
- **Language:** C++
- **LeetCode Link:** [LeetCode Problem](https://leetcode.com/problems/)

## Problem Statement
You need to satisfy two types of requirements: `need1` of item 1 and `need2` of item 2. You can buy item 1 individually at `cost1`, item 2 individually at `cost2`, or both items together using a bundle at `costBoth`. Return the minimum cost to satisfy both requirements.

## Intuition & Approach
1. **Greedy Resource Allocation:** We want to decide how many units to fulfill using individual purchases versus combined bundles. 
2. **Bounding Function:** A helper lambda `bound` calculates the cost by greedily assigning the cheaper individual price or utilizing the bundle price effectively.
3. **Maximization/Minimization Logic:** By evaluating the symmetric bounds (`bound(need1, cost1, need2, cost2)` vs `bound(need2, cost2, need1, cost1)`), we capture the optimal combination of individual and bundled purchases.

## Complexity Analysis
- **Time Complexity:** $O(1)$ — Only a few arithmetic operations and comparisons are performed.
- **Space Complexity:** $O(1)$ — Auxiliary space is constant.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        auto bound = [&](long long needA, int costA, long long needB, int costB) {
            int pA = min(costA, costBoth);  // a takes its full price
            int pB = min(costB, costBoth - pA);  // b gets what's left of the bundle
            return needA * pA + needB * pB;
        };
        return max(bound(need1, cost1, need2, cost2), bound(need2, cost2, need1, cost1));
    }
};

int main() {
    Solution sol;
    cout << sol.minimumCost(2, 3, 4, 2, 3) << endl;
    return 0;
}