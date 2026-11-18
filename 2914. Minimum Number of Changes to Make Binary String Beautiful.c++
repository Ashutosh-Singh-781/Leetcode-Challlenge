/*
# 2914. Minimum Number of Changes to Make Binary String Beautiful

- **Difficulty:** Medium
- **Topic:** String, Bit Manipulation, Greedy
- **Language:** C++
- **LeetCode Link:** [Minimum Number of Changes to Make Binary String Beautiful](https://leetcode.com/problems/minimum-number-of-changes-to-make-binary-string-beautiful/)

## Problem Statement
You are given a 0-indexed binary string `s` of an even length. A string is beautiful if it can be partitioned into one or more substrings such that each substring is of even length and contains only 1's or only 0's. Return the minimum number of changes needed to make the string beautiful.

## Intuition & Approach
1. **Even-Length Partitioning:** Since the string must be partitioned into even-length segments consisting of identical characters (all '0's or all '1's), the simplest and most optimal greedy approach is to partition the string into non-overlapping pairs of adjacent characters (size 2).
2. **Chunking & Counting:** We use C++20 views (`views::chunk(2)`) to split the string into pairs `[pair[0], pair[1]]`. If the characters in a pair do not match (`pair[0] != pair[1]`), exactly 1 change is required to make them equal.
3. `ranges::count_if` efficiently counts how many pairs have unequal elements.

## Complexity Analysis
- **Time Complexity:** $O(N)$ — We traverse the string of length $N$ once using views and count operations.
- **Space Complexity:** $O(1)$ — Only constant extra space is used.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minChanges(string s) {
        return ranges::count_if(s | views::chunk(2), [](auto pair) { return pair[0] != pair[1]; });
    }
};

int main() {
    Solution sol;
    string s = "1001";
    cout << sol.minChanges(s) << endl;
    return 0;
}