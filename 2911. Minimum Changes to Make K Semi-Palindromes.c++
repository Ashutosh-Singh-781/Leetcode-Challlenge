/*
# 2911. Minimum Changes to Make K Semi-Palindromes

- **Difficulty:** Hard
- **Topic:** String, Dynamic Programming, Memoization
- **Language:** C++
- **LeetCode Link:** [Minimum Changes to Make K Semi-Palindromes](https://leetcode.com/problems/minimum-changes-to-make-k-semi-palindromes/)

## Problem Statement
Given a string `s` and an integer `k`, partition the string `s` into `k` disjoint palindromic-like substrings (specifically, semi-palindromes) such that the total number of character changes required across all substrings is minimized. Return the minimum number of changes needed.

## Intuition & Approach
1. **Precomputing Substring Costs (`cost[i][j]`):** First, we precompute the minimum changes required to turn any substring `s[i...j]` into a semi-palindrome. A semi-palindrome of length $L$ can be divided into parts of length $d$ (where $d$ is a proper divisor of $L$), and each part forms a palindrome. We check all valid divisors $d$ and count the character mismatches.
2. **Dynamic Programming:** We define `dp[i][p]` as the minimum changes required to partition the prefix of length `i` into `p` semi-palindromes. Using the precomputed `cost` matrix, we transition from previous partition points to find the optimal global configuration.

## Complexity Analysis
- **Time Complexity:** $O(N^2 \cdot \sqrt{N} + N^2 K)$ where $N$ is the length of the string and $K$ is the number of parts, accounting for divisor checks and DP transitions.
- **Space Complexity:** $O(N^2 + N K)$ to store the precomputed substring cost table and the DP table.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;
        vector<vector<int>> cost(n, vector<int>(n, INF));
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int L = j - i + 1;
                int best = INF;
                for (int d = 1; d < L; ++d) {
                    if (L % d != 0) continue;
                    int cur = 0;
                    int m = L / d;
                    for (int r = 0; r < d; ++r) {
                        for (int t = 0; t < m / 2; ++t) {
                            if (s[i + r + t * d] != s[i + r + (m - 1 - t) * d])
                                ++cur;
                        }
                    }
                    best = min(best, cur);
                }
                cost[i][j] = best;
            }
        }
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INF));
        dp[0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int p = 1; p <= k; ++p) {
                for (int prev = 0; prev <= i - 2; ++prev) {
                    if (dp[prev][p - 1] != INF && cost[prev][i - 1] != INF)
                        dp[i][p] = min(dp[i][p], dp[prev][p - 1] + cost[prev][i - 1]);
                }
            }
        }
        return dp[n][k];
    }
};

int main() {
    Solution sol;
    string s = "abcac";
    int k = 2;
    cout << sol.minimumChanges(s, k) << endl;
    return 0;
}