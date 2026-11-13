/*
# 3420. Count Non-Decreasing Subarrays With a Certain K

- **Difficulty:** Hard
- **Topic:** Array, Two Pointers, Monotonic Stack / Queue
- **Language:** C++
- **LeetCode Link:** [Count Non-Decreasing Subarrays With a Certain K](https://leetcode.com/problems/count-non-decreasing-subarrays-with-a-certain-k/)

## Problem Statement
Given an integer array `nums` and an integer `k`, return *the number of non-decreasing subarrays where the total operations (increments) required to make the subarray non-decreasing is at most `k`*.

## Intuition & Approach
1. **Sliding Window & Monotonic Plateau Structure:** We iterate backwards from right to left while maintaining valid starting indices of plateaus using a deque-like array (`starts`).
2. **Water Trapping / Cost Tracking:** As we expand the window to the left, elements that are smaller than current peaks require "water" (increments) to flatten out.
3. **Window Shrinking:** If the accumulated `water` cost exceeds `k`, we shrink the window from the right (`r`) and adjust our cost metrics until the condition holds true.

## Complexity Analysis
- **Time Complexity:** $O(N)$ — Each element enters and leaves the plateau stack and window boundaries at most once.
- **Space Complexity:** $O(N)$ — For storing the plateau tracking arrays.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size(), head = n, tail = n, r = n - 1;
        vector<int> starts(n);  // where each plateau starts, left to right: starts[head..tail)
        long long ans = 0, water = 0;
        for (int l = n - 1; l >= 0; --l) {
            int x = nums[l];
            while (head < tail && nums[starts[head]] <= x) {  // x floods the plateau that starts at starts[head]
                int s = starts[head++];
                int end = head < tail ? starts[head] : r + 1;
                water += 1LL * (x - nums[s]) * (end - s);
            }
            starts[--head] = l;
            while (water > k) {  // the right end leaves with its water
                water -= nums[starts[tail - 1]] - nums[r];
                if (starts[tail - 1] == r)
                    --tail;
                --r;
            }
            ans += r - l + 1;
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {6, 3, 1, 2, 4};
    int k = 2;
    cout << sol.countNonDecreasingSubarrays(nums, k) << endl;
    return 0;
}