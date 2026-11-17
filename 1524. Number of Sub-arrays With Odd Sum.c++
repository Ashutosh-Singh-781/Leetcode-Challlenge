/*
# 1524. Number of Sub-arrays With Odd Sum

- **Difficulty:** Medium
- **Topic:** Array, Math, Prefix Sum
- **Language:** C++
- **LeetCode Link:** [Number of Sub-arrays With Odd Sum](https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/)

## Problem Statement
Given an array of integers `arr`, return *the number of subarrays with an odd sum*. 
Since the answer can be very large, return it modulo $10^9 + 7$.

## Intuition & Approach
1. **Prefix Sum Parity:** A subarray sum from index `i` to `j` is odd if and only if the prefix sum up to `j` and the prefix sum up to `i-1` have **different parities** (one is odd, the other is even).
2. **Counting Parities:** We use `ranges::count_if` to count how many prefix sums are odd. Since total prefix sums equal `arr.size() + 1` (including the initial empty prefix sum which is considered even), we can easily determine the number of even prefix sums.
3. **Combination:** The total number of valid subarrays with an odd sum is the product of the number of odd prefix sums and even prefix sums, taken modulo $10^9 + 7$.

## Complexity Analysis
- **Time Complexity:** $O(N)$ — We traverse the array once to compute the prefix sums and count their parities.
- **Space Complexity:** $O(1)$ — Only a few variables are used to store counts.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        long long odd = ranges::count_if(arr, [sum = 0](int x) mutable { return (sum += x) & 1; });  // odd prefix sums
        long long even = arr.size() + 1 - odd;  // the empty prefix is even
        return odd * even % 1'000'000'007;
    }
};

int main() {
    Solution sol;
    vector<int> arr = {1, 3, 5};
    cout << sol.numOfSubarrays(arr) << endl;
    return 0;
}