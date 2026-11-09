/*
# 1606. Find Servers That Handled Most Number of Requests

- **Difficulty:** Hard
- **Topic:** Array, Greedy, Heap (Priority Queue), Ordered Set
- **Language:** C++
- **LeetCode Link:** [Find Servers That Handled Most Number of Requests](https://leetcode.com/problems/find-servers-that-handled-most-number-of-requests/)

## Problem Statement
You have `k` servers numbered from `0` to `k-1` that are being used to handle multiple requests roughly arriving sequentially. Each request arrives at `arrival[i]` and takes `load[i]` time to process. 
Requests are assigned using a specific rule:
1. The `i`-th request is given to the server `i % k` if it is free.
2. If that server is busy, it is assigned to the next available server with an index greater than or equal to `i % k` (wrapping around to `0` if necessary).
3. If all servers are busy, the request is dropped.
Return a sorted list containing the indices of the busiest servers.

## Intuition & Approach
1. **Min-Heaps for Management:** We maintain two priority queues:
   - `free`: A min-heap storing the next available timestamp/turn index for each server, initialized such that server `x` is ready at turn `x`.
   - `busy`: A min-heap storing active jobs (`{free_up_time, server_id}`).
2. **Simulation & Turn Calculation:** For each request `i` arriving at `arrival[i]`:
   - Free up any servers in `busy` whose finish time is less than or equal to `arrival[i]` and push their next valid turn index into `free`.
   - If `free` is empty, the request is dropped. Otherwise, query the first valid server from `free` whose turn index is `>= i`.
   - Assign the task, update its completion time in `busy`, and increment the request count for that server.
3. **Finding the Busiest:** Finally, find the maximum handle count and collect all servers matching that maximum count.

## Complexity Analysis
- **Time Complexity:** $O(N \log K)$ where $N$ is the number of requests and $K$ is the number of servers, due to priority queue operations.
- **Space Complexity:** $O(K + N)$ for storing the heaps, handled counts, and answer vector.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct Job {
        int at;  // the time its server frees up
        int server;
        auto operator<=>(const Job&) const = default;
    };
    template <class T> using MinHeap = priority_queue<T, vector<T>, greater<>>;

public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> turns(k);
        iota(turns.begin(), turns.end(), 0);  // at request 0, server x's next turn is x
        MinHeap<int> free(greater<>{}, std::move(turns));  // each free server, keyed by its next turn

        MinHeap<Job> busy;
        vector<int> handled(k);
        for (int i = 0; i < ssize(arrival); ++i) {
            while (!busy.empty() && busy.top().at <= arrival[i]) {  // done by the arrival
                int x = busy.top().server;
                busy.pop();
                free.push(i + (x - i % k + k) % k);  // its first turn from i on
            }
            if (free.empty()) continue;  // none free: the request is dropped
            int x = free.top() % k;
            free.pop();
            busy.push({arrival[i] + load[i], x});
            ++handled[x];
        }

        int most = ranges::max(handled);
        vector<int> ans;
        for (int x = 0; x < k; ++x)
            if (handled[x] == most) ans.push_back(x);
        return ans;
    }
};

int main() {
    Solution sol;
    int k = 3;
    vector<int> arrival = {1, 2, 3, 4, 8, 9, 10};
    vector<int> load = {5, 2, 10, 3, 1, 2, 2};
    vector<int> result = sol.busiestServers(k, arrival, load);
    for (int res : result) {
        cout << res << " ";
    }
    cout << endl;
    return 0;
}