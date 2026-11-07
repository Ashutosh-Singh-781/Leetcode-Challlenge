/*
# 1882. Process Tasks Using Servers

- **Difficulty:** Medium
- **Topic:** Array, Heap (Priority Queue), Simulation
- **Language:** C++
- **LeetCode Link:** [Process Tasks Using Servers](https://leetcode.com/problems/process-tasks-using-servers/)

## Problem Statement
You are given two integer arrays `servers` and `tasks` of lengths `n` and `m` respectively. `servers[i]` is the weight of the $i$-th server, and `tasks[j]` is the time needed to process the $j$-th task.
Tasks are assigned to servers in sequential order using a greedy strategy: assign the task to the free server with the smallest weight, and break ties by the smallest index. If all servers are busy, wait for the earliest server to free up. Return an array of the indices of the servers used to process each task.

## Intuition & Approach
1. **Priority Queues (Min-Heaps):** Maintain two priority queues:
   - `free`: Stores available servers, sorted primarily by weight, and secondarily by server index.
   - `busy`: Stores currently occupied servers, sorted by their free-up time.
2. **Simulation:** For each second `s` (each task arrival):
   - Free up any servers in `busy` whose processing finish time is less than or equal to `s`, and move them back to `free`.
   - If no servers are free, advance time to the earliest finish time in `busy` by picking from the busy heap.
   - Assign the task to the top server, update its availability time, and push it into the `busy` heap.

## Complexity Analysis
- **Time Complexity:** $O((N + M) \log N)$ where $N$ is the number of servers and $M$ is the number of tasks, due to heap operations.
- **Space Complexity:** $O(N + M)$ for storing heaps and the answer vector.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
    struct Server {
        long long at;  // the second it frees up; 0 while free, so free servers sort by weight, then index
        int weight, index;
        auto operator<=>(const Server&) const = default;
    };
    using MinHeap = priority_queue<Server, vector<Server>, greater<>>;

public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        vector<Server> all;
        for (int i = 0; i < ssize(servers); ++i) all.push_back({0, servers[i], i});
        MinHeap free(greater<>{}, std::move(all));

        MinHeap busy;
        vector<int> ans;
        for (int s = 0; s < ssize(tasks); ++s) {
            while (!busy.empty() && busy.top().at <= s) {  // done by second s
                auto [at, weight, index] = busy.top();
                busy.pop();
                free.push({0, weight, index});
            }
            MinHeap& from = free.empty() ? busy : free;  // none free: the first to finish takes it
            auto [at, weight, index] = from.top();
            from.pop();
            busy.push({max<long long>(at, s) + tasks[s], weight, index});
            ans.push_back(index);
        }

        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> servers = {3, 1, 1};
    vector<int> tasks = {1, 2, 3, 2, 1, 2};
    vector<int> result = sol.assignTasks(servers, tasks);
    for (int res : result) {
        cout << res << " ";
    }
    cout << endl;
    return 0;
}