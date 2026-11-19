/*
# 2567. Minimum Score by Changing Two Elements

- **Difficulty:** Medium
- **Topic:** Array, Greedy, Sorting
- **Language:** C++ (C++20)
- **LeetCode Link:** [Minimum Score by Changing Two Elements](https://leetcode.com/problems/minimum-score-by-changing-two-elements/)

## Problem Statement
You are given a 0-indexed integer array `nums`. The score of `nums` is the sum of the maximum and minimum values of `nums` after changing at most two elements to any value. Return the minimum possible score.

## Intuition & Approach
1. **Extreme Values & Two Edits:** Changing an element to match an existing value effectively removes its influence on the min or max. Since we can modify up to two elements, we can eliminate any combination of two extremes among the three smallest and three largest elements.
2. **Three Candidate Scores:**
   - Change the two largest elements to match the third largest: `large[2] - small[0]`.
   - Change the two smallest elements to match the third smallest: `large[0] - small[2]`.
   - Change one largest and one smallest element: `large[1] - small[1]`.
3. **Partial Sort Copy:** We copy the three smallest elements into `small` (ascending) and the three largest into `large` (descending) using `ranges::partial_sort_copy`, then return the minimum of the three candidate scores.

## Complexity Analysis
- **Time Complexity:** $O(N \log K)$ where $K = 3$ (effectively $O(N)$ for partial sorting of the top/bottom 3 elements).
- **Space Complexity:** $O(1)$ auxiliary space using fixed-size arrays of length 3.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        array<int, 3> small, large;
        ranges::partial_sort_copy(nums, small);  // the 3 smallest, ascending
        ranges::partial_sort_copy(nums, large, greater{});  // the 3 largest, descending
        return min({large[0] - small[2], large[1] - small[1], large[2] - small[0]});
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 4, 3};
    cout << sol.minimizeSum(nums) << endl;
    return 0;
}