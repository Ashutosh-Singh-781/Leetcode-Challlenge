/*
# 2124. Check if All A's Appears Before All B's

- **Difficulty:** Easy
- **Topic:** String
- **Language:** C++ (C++23)
- **LeetCode Link:** [Check if All A's Appears Before All B's](https://leetcode.com/problems/check-if-all-as-appears-before-all-bs/)

## Problem Statement
Given a string `s` consisting of only the characters `'a'` and `'b'`, return `true` if **every** `'a'` appears before **every** `'b'` in the string, or `false` otherwise.

## Intuition & Approach
1. **Forbidden Substring Observation:** All `'a'`s appear before all `'b'`s if and only if there is never a `'b'` followed later by an `'a'`—that is, the substring `"ba"` never appears in `s`.
2. **Substring Check:** Using C++23 `string::contains("ba")`, we return `true` when `"ba"` is absent (`!s.contains("ba")`) and `false` otherwise.

## Complexity Analysis
- **Time Complexity:** $O(N)$ where $N$ is the length of `s`.
- **Space Complexity:** $O(1)$ auxiliary space.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool checkString(string s) {
        return !s.contains("ba");
    }
};

int main() {
    Solution sol;
    cout << boolalpha << sol.checkString("aaabbb") << endl;
    return 0;
}

