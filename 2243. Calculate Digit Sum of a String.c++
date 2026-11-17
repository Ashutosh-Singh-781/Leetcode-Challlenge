/*
# 2243. Calculate Digit Sum of a String

- **Difficulty:** Easy
- **Topic:** String, Simulation
- **Language:** C++
- **LeetCode Link:** [Calculate Digit Sum of a String](https://leetcode.com/problems/calculate-digit-sum-of-a-string/)

## Problem Statement
You are given a string `s` consisting of digits and an integer `k`. A round can be completed if the length of `s` is greater than `k`. In one round, divide `s` into consecutive groups of size `k` such that the first group has length `k`, the second group has length `k`, and so on. The last group can have a length less than `k` if the length of `s` is not divisible by `k`. Replace each group with a string representing the sum of all its digits. Concatenate these groups to form a new string. Repeat this process until the length of `s` is less than or equal to `k`. Return `s` after completing all rounds.

## Intuition & Approach
1. **Simulation with While Loop:** Continue the transformation process as long as the length of string `s` is greater than `k`.
2. **Chunking via `string_view`:** Divide the string into groups of size `k` efficiently using `string_view::substr`.
3. **Summation & Concatenation:** For each group, accumulate the numeric value of each character (`d - '0'`), convert the sum to a string, and append it to the `next` round string. Update `s = next` and repeat.

## Complexity Analysis
- **Time Complexity:** $O(N \log_k N)$ where $N$ is the length of the string, as the string length decreases by a factor of $k$ in each round.
- **Space Complexity:** $O(N)$ for storing intermediate strings during transformation.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string digitSum(string s, int k) {
        while (ssize(s) > k) {
            string next;
            for (int i = 0; i < ssize(s); i += k) {
                string_view group = string_view(s).substr(i, k);  // the last group may be shorter
                next += to_string(accumulate(group.begin(), group.end(), 0, [](int sum, char d) { return sum + d - '0'; }));
            }
            s = next;
        }
        return s;
    }
};

int main() {
    Solution sol;
    string s = "11111222223";
    int k = 3;
    cout << sol.digitSum(s, k) << endl;
    return 0;
}