/*
# 3360. Stone Removal Game

- **Difficulty:** Easy
- **Topic:** Math, Bit Manipulation, Game Theory
- **Language:** C++
- **LeetCode Link:** [Stone Removal Game](https://leetcode.com/problems/stone-removal-game/)

## Problem Statement
Alice and Bob are playing a game with a pile of `n` stones. Alice moves first.
- On her first turn, Alice must remove `10` stones.
- Each subsequent player must remove `1` fewer stone than the previous player's last move (so `9`, then `8`, then `7`, and so on, down to `1`).
- The player who cannot make a move (because fewer stones remain than required on their turn) loses.
Return `true` if Alice can win, and `false` otherwise.

## Intuition & Approach
1. **Deterministic Move Sequence:** Because each move's required stone count is strictly fixed (`10, 9, 8, ..., 1`, for at most `10` total turns and `55` stones), neither player has choices. We can simulate or precompute the winner for every `n` from `0` to `50` (`1 <= n <= 50`).
2. **Bitmask Lookup:** Pack the boolean outcomes (`1` if Alice wins, `0` if Bob wins) for `n = 0..50` into a 64-bit integer constant `0x61F03F807FC00ULL`, where bit `n` holds the answer for `n` stones. Shift right by `n` and mask with `& 1` to extract the result in $O(1)$ time.

## Complexity Analysis
- **Time Complexity:** $O(1)$ — A single bit shift and bitwise AND.
- **Space Complexity:** $O(1)$ — Constant space using a single integer literal.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canAliceWin(int n) {
        return 0x61F03F807FC00ULL >> n & 1;
    }
};

int main() {
    Solution sol;
    cout << boolalpha << sol.canAliceWin(12) << endl;
    cout << boolalpha << sol.canAliceWin(1) << endl;
    return 0;
}