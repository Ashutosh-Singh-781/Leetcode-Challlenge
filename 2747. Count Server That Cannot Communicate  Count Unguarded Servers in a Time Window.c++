/*
# 2747. Count Server That Cannot Communicate / Count Unguarded Servers in a Time Window

- **Difficulty:** Medium / Hard
- **Topic:** Array, Sorting, Two Pointers, Sliding Window
- **Language:** C++
- **LeetCode Link:** [LeetCode Problem](https://leetcode.com/problems/)

## Problem Statement
You are given an integer `n` representing servers, a 2D integer array `logs` where `logs[i] = [server_id, time]`, an integer `x`, and an array of integers `queries`. For each query time `q`, find the number of servers that did not receive any requests within the time window `[q - x, q]`.

## Intuition & Approach
1. **Sorting by Time:** Sort the `logs` by their timestamp so we can process them efficiently. Also, sort the `queries` while keeping track of their original indices using an `order` array so we can process queries in chronological order.
2. **Two-Pointer Window Technique:** Maintain a sliding window `[q - x, q]` over the logs. As query times increase, bring in new log entries (`hi` pointer) and expire old ones (`lo` pointer) that fall outside the window.
3. **Tracking Busy Servers:** Maintain a frequency array `cnt` for each server and a `busy` counter representing servers with at least one request in the active window. The number of servers without requests is simply `n - busy`.

## Complexity Analysis
- **Time Complexity:** $O(M \log M + Q \log Q)$ where $M$ is the number of logs and $Q$ is the number of queries, due to sorting.
- **Space Complexity:** $O(M + Q)$ for storing order vectors, counts, and answers.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        ranges::sort(logs, {}, [](auto& log) { return log[1]; });  // by time
        logs.push_back({0, INT_MAX});  // sentinel: no window ever reaches it
        vector<int> order(queries.size());
        iota(order.begin(), order.end(), 0);
        ranges::sort(order, {}, [&](int i) { return queries[i]; });  // query positions in time order

        vector<int> cnt(n + 1), ans(queries.size());  // cnt: requests per server inside the window [q - x, q]
        int busy = 0, lo = 0, hi = 0;  // busy: servers with at least one request in it
        for (int i : order) {
            int q = queries[i];
            for (; logs[hi][1] <= q; ++hi)  // requests up to q come in
                busy += cnt[logs[hi][0]]++ == 0;
            for (; logs[lo][1] < q - x; ++lo)  // requests before q - x go out
                busy -= --cnt[logs[lo][0]] == 0;
            ans[i] = n - busy;
        }
        return ans;
    }
};

int main() {
    Solution sol;
    int n = 3;
    vector<vector<int>> logs = {{1, 3}, {2, 6}, {1, 5}};
    int x = 5;
    vector<int> queries = {10, 11};
    vector<int> result = sol.countServers(n, logs, x, queries);
    for (int res : result) {
        cout << res << " ";
    }
    cout << endl;
    return 0;
}