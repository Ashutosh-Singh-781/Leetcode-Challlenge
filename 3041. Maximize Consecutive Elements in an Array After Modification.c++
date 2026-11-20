/*
# 3041. Maximize Consecutive Elements in an Array After Modification

- **Difficulty:** Medium
- **Topic:** Array, Dynamic Programming, Greedy, Sorting
- **Language:** C++ (C++20)
- **LeetCode Link:** [Maximize Consecutive Elements in an Array After Modification](https://leetcode.com/problems/maximize-consecutive-elements-in-an-array-after-modification/)

## Problem Statement
You are given a 0-indexed array `nums` consisting of positive integers. Initially, you can increase the value of any element in the array by at most `1` any number of times. Return *the maximum possible length of a sequence of consecutive integers you can select from `nums` after performing the operations*.

## Intuition & Approach
1. **Sorting & State Tracking:** After sorting `nums`, each element `x` can either stay `x` (unmodified) or become `x + 1` (incremented by 1). We track two consecutive-streak lengths ending at the previous processed value:
   - `keep`: longest consecutive sequence ending at `last`.
   - `bump`: longest consecutive sequence ending at `last + 1` (achieved by incrementing a prior element).
2. **Gap Transitions (`x - last`):**
   - `x - last == 0`: `x` repeats `last`; keeping `x` doesn't extend `last`, while bumping `x` to `x + 1` extends a streak ending at `last` (`bump = keep + 1`).
   - `x - last == 1`: `x` is consecutive after `last` (`++keep`) and `x + 1` is consecutive after `last + 1` (`++bump`).
   - `x - last == 2`: `x` bridges into `last + 1` (`keep = bump + 1`), while `x + 1` has a gap so it resets (`bump = 1`).
   - Any larger gap: both `keep` and `bump` reset to `1`.

## Complexity Analysis
- **Time Complexity:** $O(N \log N)$ due to sorting `nums` of size $N$.
- **Space Complexity:** $O(1)$ auxiliary space (excluding sorting stack space).
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        ranges::sort(nums);
        int best = 1, keep = 1, bump = 1, last = -10;
        for (int x : nums) {
            switch (x - last) {
                case 0: bump = keep + 1; break;  // x repeat: bump it on top of keep
                case 1: ++keep, ++bump; break;  // x extends keep, x + 1 extends bump
                case 2: keep = bump + 1, bump = 1; break;  // x extends bump, x + 1 starts over
                default: keep = bump = 1;
            }
            best = max({best, keep, bump}), last = x;
        }
        return best;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2, 1, 5, 1, 1};
    cout << sol.maxSelectedElements(nums) << endl;
    return 0;
}