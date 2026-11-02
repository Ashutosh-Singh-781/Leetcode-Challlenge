/*
# 462. Minimum Moves to Equal Array Elements II

- **Difficulty:** Medium
- **Topic:** Array, Sorting, Math
- **Language:** C++
- **LeetCode Link:** [Minimum Moves to Equal Array Elements II](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/)

## Problem Statement
Given an integer array `nums` of size `n`, return *the minimum number of moves required to make all array elements equal*.
In one move, you can increment or decrement an element by `1`.

## Intuition & Approach
To minimize the sum of absolute differences $\sum |x_i - m|$, the optimal choice for $m$ is the **median** of the array. 
1. We use `nth_element` to find the median in $O(N)$ average time without fully sorting the array.
2. We iterate through the array and sum up the absolute differences from the median.

## Complexity Analysis
- **Time Complexity:** $O(N)$ on average.
- **Space Complexity:** $O(1)$ auxiliary space.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves2(vector<int>& nums) {
        auto mid = nums.begin() + nums.size() / 2;
        std::nth_element(nums.begin(), mid, nums.end());
        int med = *mid;
        long long moves = 0;
        for (int x : nums) {
            moves += abs((long long)x - med);
        }
        return moves;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3};
    cout << sol.minMoves2(nums) << endl;
    return 0;
}