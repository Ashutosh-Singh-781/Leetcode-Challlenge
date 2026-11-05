/*
# 1385. Find the Distance Value Between Two Arrays

- **Difficulty:** Easy
- **Topic:** Array, Two Pointers, Binary Search, Sorting
- **Language:** C++
- **LeetCode Link:** [Find the Distance Value Between Two Arrays](https://leetcode.com/problems/find-the-distance-value-between-two-arrays/)

## Problem Statement
Given two integer arrays `arr1` and `arr2` and an integer `d`, return the distance value between the two arrays.
The distance value is defined as the number of elements `arr1[i]` such that there is not any element `arr2[j]` where `|arr1[i] - arr2[j]| <= d`.

## Intuition & Approach
1. We define a lambda function `far` to check if a given element `a` from `arr1` maintains a distance greater than `d` from every element `b` in `arr2`.
2. Using C++20 `ranges::all_of`, we verify that all elements in `arr2` satisfy the condition `abs(a - b) > d`.
3. Finally, `ranges::count_if` counts how many elements in `arr1` satisfy this condition.

## Complexity Analysis
- **Time Complexity:** $O(N \times M)$ where $N$ is the size of `arr1` and $M$ is the size of `arr2`.
- **Space Complexity:** $O(1)$ auxiliary space.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        auto far = [&](int a) {  // no b in [a - d, a + d]
            return ranges::all_of(arr2, [&](int b) { return abs(a - b) > d; });
        };
        return ranges::count_if(arr1, far);
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {4, 5, 8};
    vector<int> arr2 = {10, 9, 1, 8};
    int d = 2;
    cout << sol.findTheDistanceValue(arr1, arr2, d) << endl;
    return 0;
}