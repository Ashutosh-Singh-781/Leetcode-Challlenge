/*
# 3946. Maximum Sale Items

- **Difficulty:** Hard
- **Topic:** Array, Dynamic Programming, Number Theory
- **Language:** C++ (C++20)
- **LeetCode Link:** [LeetCode Problem](https://leetcode.com/problems/)

## Problem Statement
You are given a list of `items`, where each item is represented as `[factor, price]`, along with an integer `budget`. Buying or unlocking a copy of an item with `factor` provides additional sale items / copies according to multiples of `factor`, subject to the available `budget`. Return the maximum number of items obtainable within `budget`.

## Intuition & Approach
1. **Multiple / Factor Gain Precomputation:** Count how many items have each factor in `have[f]`. For every candidate `factor` from `1` to `top = max(factors)`, step through multiples of `factor` (`have | views::drop(factor) | views::stride(factor)`) and sum them into `gains[factor]` to find how many items match a multiple of `factor`.
2. **Baseline with Cheapest Item (`0/1` vs. Unbounded Comparison):** Initialize `best[money] = money / cheapest`, representing buying as many copies as possible of the item with minimum price `cheapest` without paying extra item costs.
3. **0/1 Knapsack Over Beneficial Items:** For each `[factor, price]`, let `gain = gains[factor]`. Only consider adopting this item when `gain > price / cheapest` (otherwise buying copies of the cheapest item gives at least as much value). Iterate `money` backward from `budget` down to `price` so each item is applied at most once (`best[money] = max(best[money], best[money - price] + gain)`).

## Complexity Analysis
- **Time Complexity:** $O(F \log F + N \cdot B)$ where $F$ is the maximum factor, $N$ is the number of items, and $B$ is `budget`.
- **Space Complexity:** $O(F + B)$ for the factor frequency/gain arrays and the DP table of size `budget + 1`.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        auto factors = items | views::transform([](auto& item) { return item[0]; });
        auto prices = items | views::transform([](auto& item) { return item[1]; });
        int top = ranges::max(factors);
        vector<int> have(top + 1), gains(top + 1);  // have[f]: items with factor f
        for (int factor : factors) have[factor]++;
        for (int factor = 1; factor <= top; factor++)  // every factor-th cell is a multiple
            gains[factor] = ranges::fold_left(have | views::drop(factor) | views::stride(factor), 0, plus{});

        int cheapest = ranges::min(prices);
        vector<int> best(budget + 1);  // no first copies yet: everything goes to the cheapest item
        for (int money = 0; money <= budget; money++) best[money] = money / cheapest;
        for (auto& item : items) {
            int factor = item[0], price = item[1];
            if (int gain = gains[factor]; gain > price / cheapest)  // else the same money buys as many copies of the cheapest item
                for (int money = budget; money >= price; money--)  // backwards: one first copy per item
                    best[money] = max(best[money], best[money - price] + gain);
        }
        return best[budget];
    }
};

int main() {
    Solution sol;
    vector<vector<int>> items = {{2, 5}, {4, 3}, {1, 2}};
    int budget = 10;
    cout << sol.maximumSaleItems(items, budget) << endl;
    return 0;
}