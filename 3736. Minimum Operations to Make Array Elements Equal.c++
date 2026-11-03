/*
# 3736. Minimum Operations to Make Array Elements Equal

- **Difficulty:** Easy / Medium
- **Topic:** Array, Math, Greedy
- **Language:** C++
- **LeetCode Link:** [LeetCode Problem](https://leetcode.com/problems/)

## Problem Statement
Given an integer array `nums`, return the minimum number of operations required to make all array elements equal, where in each operation you can increase an element.

## Intuition & Approach
To make all elements equal with the minimum number of increases, the target value must be the maximum element in the array (`mx`). 
1. We find the maximum element in the array using `max_element`.
2. We iterate through each element and add the difference `mx - x` to our total result.

## Complexity Analysis
- **Time Complexity:** $O(N)$ — We iterate through the array twice: once to find the maximum element and once to calculate the total operations.
- **Space Complexity:** $O(1)$ — Only a constant amount of extra space is used.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minMoves(vector<int>& nums) {
        int mx = *max_element(nums.begin(), nums.end());
        long long res = 0;
        for (int x : nums) {
            res += (mx - x);
        }
        return res;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3};
    cout << sol.minMoves(nums) << endl;
    return 0;
}