/*
# 3411. Maximum Length Subarray With Positive Product

- **Difficulty:** Medium
- **Topic:** Array, Math, Sliding Window, Number Theory
- **Language:** C++ (C++20)
- **LeetCode Link:** [Maximum Length Subarray With Positive Product](https://leetcode.com/problems/maximum-length-subarray-with-positive-product/)

## Problem Statement
Given an array of positive integers `nums`, a subarray `arr` of `nums` is called **product equivalent** if `prod(arr) == gcd(arr) * lcm(arr)`, where `prod(arr)` is the product of elements in `arr`, `gcd(arr)` is their greatest common divisor, and `lcm(arr)` is their least common multiple. Return *the length of the longest product-equivalent subarray of `nums`*.

## Intuition & Approach
1. **Product vs. `gcd * lcm`:** For any two positive integers $a$ and $b$, $a \cdot b = \gcd(a, b) \cdot \operatorname{lcm}(a, b)$. Across a subarray of size $m$, $\operatorname{lcm}$ grows by incorporating prime factors, while $\gcd$ shrinks as more elements are included. A subarray satisfies $\prod = \gcd \cdot \operatorname{lcm}$ when its elements are **pairwise coprime** (so no prime factor is shared across multiple elements in the window, keeping $\gcd = 1$ and $\operatorname{lcm} = \prod$ when pairwise coprime).
2. **Sliding Window with Coprimality:** Maintain a window `[left, right]` whose elements are pairwise coprime, tracking the current window product in `product`. Before adding `x = nums[right]`, while `gcd(product, x) > 1`, shrink the window from `left` and divide `product` by `nums[left++]`. Multiply `product *= x` and update `best` with the current window length `right - left + 1`.

## Complexity Analysis
- **Time Complexity:** $O(N \log(\max(\text{nums})))$ — Each element enters and leaves the sliding window at most once, and each `gcd` / division step takes logarithmic time in the element values.
- **Space Complexity:** $O(1)$ auxiliary space.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxLength(vector<int>& nums) {
        int best = 2, left = 0, product = 1;
        for (int right = 0; right < ssize(nums); ++right) {
            int x = nums[right];
            while (gcd(product, x) > 1)
                product /= nums[left++];
            product *= x;
            best = max(best, right - left + 1);
        }
        return best;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 1, 2, 1, 1, 1};
    cout << sol.maxLength(nums) << endl;
    return 0;
}