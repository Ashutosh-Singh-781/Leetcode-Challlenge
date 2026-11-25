/*
# 3934. Smallest Unique Subarray

- **Difficulty:** Hard
- **Topic:** Array, Binary Search, Hash Table, String Matching / Sparse Table Equivalence Classes
- **Language:** C++ (C++20)
- **LeetCode Link:** [LeetCode Problem](https://leetcode.com/problems/)

## Problem Statement
Given an integer array `nums` of length `n`, find the smallest length `L` such that there exists at least one subarray of length `L` in `nums` that is unique (appears only once in `nums`). If no such subarray exists, return `n` (or appropriate fallback depending on constraints).

## Intuition & Approach
1. **Power-of-Two Equivalence Classes (`names`):** Similar to suffix-array / sparse-table doubling, `names[k][i]` assigns an integer ID representing the subarray of length $2^k$ starting at index `i`, such that two subarrays of length $2^k$ have the same ID if and only if they are identical. Each doubling step pairs two adjacent blocks of size `half` (`a` and `b`) into a single 64-bit key `(long long)a << 32 | b` and maps it to a dense ID.
2. **Covering Any Length `L` with Two Overlapping Blocks:** For any target subarray `length`, let `k = bit_width((unsigned)length) - 1` so that $2^k \le \text{length} < 2^{k+1}$. Any subarray of length `length` starting at `i` is uniquely determined by its prefix of length $2^k$ (ID `names[k][i]`) and its suffix of length $2^k$ (ID `names[k][i + length - (1 << k)]`), which overlap whenever $\text{length} > 2^k$ and touch when $\text{length} = 2^k$. Counting occurrences of these pairs in `found(length)` checks whether any window of size `length` is unique.
3. **Monotonicity & Binary Search (`partition_point`):** Since a unique subarray of length `L` implies every longer subarray containing it is also unique (and any shorter subarray has fewer distinct windows), `found(length)` is monotonic (`false` then `true`). `ranges::partition_point` over `views::iota(1, n)` finds the first length where `found` is true.

## Complexity Analysis
- **Time Complexity:** $O(N \log^2 N)$ — Building `names` takes $O(N \log N)$ across $\lfloor \log_2 N \rfloor$ levels, and `ranges::partition_point` runs $O(\log N)$ calls to `found`, each scanning up to $N$ pairs in $O(N)$ expected time.
- **Space Complexity:** $O(N \log N)$ to store the equivalence IDs across all $O(\log N)$ power-of-two levels.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> names{nums};  // names[k][i] is equal for equal windows of length 2^k starting at i
        for (int half = 1; 2 * half <= n; half *= 2) {  // blocks of 2, 4, 8, ... while they fit
            unordered_map<long long, int> ids;  // pair of halves -> number of the whole window
            vector<int> whole;
            for (auto [a, b] : views::zip(names.back(), names.back() | views::drop(half)))
                whole.push_back(ids.try_emplace((long long)a << 32 | b, ids.size()).first->second);
            names.push_back(std::move(whole));
        }

        auto found = [&](int length) {  // is some window of this length unique?
            int k = bit_width((unsigned)length) - 1;  // its first 2^k elements and its last 2^k cover it
            unordered_map<long long, int> count;
            for (auto [a, b] : views::zip(names[k], names[k] | views::drop(length - (1 << k))))
                count[(long long)a << 32 | b]++;
            return ranges::any_of(count, [](auto& entry) { return entry.second == 1; });
        };

        return *ranges::partition_point(views::iota(1, n), not_fn(found));
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 1, 2, 3};
    cout << sol.smallestUniqueSubarray(nums) << endl;
    return 0;
}