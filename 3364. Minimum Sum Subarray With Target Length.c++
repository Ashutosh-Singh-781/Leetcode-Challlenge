/*
# 3364. Minimum Sum Subarray With Target Length

- **Difficulty:** Easy
- **Topic:** Array, Sliding Window, Prefix Sum
- **Language:** C++
- **LeetCode Link:** [Minimum Sum Subarray With Target Length](https://leetcode.com/problems/minimum-sum-subarray-with-target-length/)

## Problem Statement
You are given an array of integers `nums` and two integers `l` and `r`. Find the minimum sum of a subarray whose size is between `l` and `r` (inclusive) and whose sum is greater than `0`. Return the minimum sum, or `-1` if no such subarray exists.

## Intuition & Approach
1. **Brute Force Subarray Search:** We use a nested loop to check all possible subarrays starting at index `i` and ending at index `j`.
2. **Length and Sum Validation:** For each subarray, we compute its length (`len = j - i + 1`) and sum. If the length is within the range `[l, r]` and the sum is strictly positive (`sum > 0`), we update our minimum sum (`ans`).

## Complexity Analysis
- **Time Complexity:** $O(N^2)$ — We iterate through all possible starting and ending points for subarrays of size up to $N$.
- **Space Complexity:** $O(1)$ — Only a constant amount of extra space is used.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int n = nums.size();
        int ans = INT_MAX;
        for (int i = 0; i < n; i++) {
            int sum = 0;
            for (int j = i; j < n; j++) {
                sum += nums[j];
                int len = j - i + 1;
                if (len >= l && len <= r && sum > 0) {
                    ans = min(ans, sum);
                }
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {3, -2, 1, 4};
    int l = 2, r = 3;
    cout << sol.minimumSumSubarray(nums, l, r) << endl;
    return 0;
}