/*
# 453. Minimum Moves to Equal Array Elements

- **Difficulty:** Medium
- **Topic:** Array, Math
- **Language:** C++ (C++20)
- **LeetCode Link:** [Minimum Moves to Equal Array Elements](https://leetcode.com/problems/minimum-moves-to-equal-array-elements/)

## Problem Statement
Given an integer array `nums` of size `n`, return *the minimum number of moves required to make all array elements equal*.
In one move, you can increment `n - 1` elements of the array by `1`.

## Intuition & Approach
Incrementing $n-1$ elements by $1$ is mathematically equivalent to decrementing $1$ element by $1$. Instead of trying to raise every element up to reach a maximum value, we can bring all elements down to the minimum element in the array. 
Total Moves = Sum of Array - (Minimum Element * Length of Array)

## Complexity Analysis
- **Time Complexity:** $O(N)$
- **Space Complexity:** $O(1)$
*/

#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums) {
        return accumulate(nums.begin(), nums.end(), 0ll) - ((long long)nums.size() * ranges::min(nums));
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3};
    cout << sol.minMoves(nums) << endl;
    return 0;
}
