/*
# 3105. Longest Strictly Increasing or Strictly Decreasing Subarray

- **Difficulty:** Easy
- **Topic:** Array
- **Language:** C++
- **LeetCode Link:** [Longest Strictly Increasing or Strictly Decreasing Subarray](https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/)

## Problem Statement
You are given an array of integers `nums`. Return *the length of the longest subarray of `nums` that is either strictly increasing or strictly decreasing*.

## Intuition & Approach
1. We can track the lengths of the current strictly increasing (`up`) and strictly decreasing (`down`) subarrays ending at the current index `i`.
2. As we iterate through the array from left to right:
   - If `nums[i - 1] < nums[i]`, we extend the increasing streak (`up + 1`); otherwise, it resets to `1`.
   - If `nums[i - 1] > nums[i]`, we extend the decreasing streak (`down + 1`); otherwise, it resets to `1`.
3. We keep track of the maximum length encountered across all positions in `best`.

## Complexity Analysis
- **Time Complexity:** $O(N)$ — We traverse the array of size $N$ in a single pass.
- **Space Complexity:** $O(1)$ — Only a few integer variables are used for tracking streaks.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int best = 1, up = 1, down = 1;
        for (size_t i = 1; i < nums.size(); ++i) {
            up = nums[i - 1] < nums[i] ? up + 1 : 1;  // increasing streak ending at nums[i]
            down = nums[i - 1] > nums[i] ? down + 1 : 1;  // decreasing streak ending at nums[i]
            best = max({best, up, down});
        }
        return best;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 4, 3, 3, 2};
    cout << sol.longestMonotonicSubarray(nums) << endl;
    return 0;
}