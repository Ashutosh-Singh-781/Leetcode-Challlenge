/*
# 3331. Find Subtree Sizes After Changes

- **Difficulty:** Medium
- **Topic:** Array, Tree, Depth-First Search, String
- **Language:** C++
- **LeetCode Link:** [Find Subtree Sizes After Changes](https://leetcode.com/problems/find-subtree-sizes-after-changes/)

## Problem Statement
You are given a tree rooted at node `0` with `n` nodes labeled from `0` to `n - 1`, represented by a parent array `p` where `p[i]` is the parent of node `i` (`p[0] = -1`). You are also given a string `s` of length `n`, where `s[i]` is the character assigned to node `i`.
For each node `u` (other than `0`), if there exists an ancestor `v` of `u` in the original tree such that `s[v] == s[u]`, we move node `u` so that its new parent becomes the closest such ancestor `v`. All such moves happen simultaneously.
Return an array `ans` of length `n` where `ans[i]` is the size of the subtree rooted at node `i` in the modified tree.

## Intuition & Approach
1. **Ancestor Character Tracking (`dfs`):** Traverse the original tree from root `0` using DFS while maintaining `last[26]`, which records the most recent ancestor seen on the current root-to-node path for each character `'a'`–`'z'`. For a node `u` (`u > 0`), if `last[s[u] - 'a'] != -1`, update `p[u]` to that closest matching ancestor. Set `last[s[u] - 'a'] = u` before recursing into children, and restore `old` on backtrack.
2. **Subtree Size Calculation (`calc`):** Build the new adjacency list `tree` using the updated parent array `p`, then run a post-order DFS from node `0` to compute and store each node's subtree size in `ans[u]`.

## Complexity Analysis
- **Time Complexity:** $O(N)$ — Each node is visited a constant number of times across both DFS traversals.
- **Space Complexity:** $O(N)$ — For adjacency lists, recursion stack, and the `ans` array.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> ans;

    void dfs(int u, vector<vector<int>>& adj, string& s,
             vector<int>& p, vector<int>& last) {
        int c = s[u] - 'a', old = last[c];

        if (u && old != -1) p[u] = old;
        last[c] = u;

        for (int v : adj[u])
            dfs(v, adj, s, p, last);

        last[c] = old;
    }

    int calc(int u, vector<vector<int>>& tree) {
        ans[u] = 1;
        for (int v : tree[u])
            ans[u] += calc(v, tree);
        return ans[u];
    }

    vector<int> findSubtreeSizes(vector<int>& p, string s) {
        int n = p.size();
        vector<vector<int>> adj(n), tree(n);

        for (int i = 1; i < n; i++)
            adj[p[i]].push_back(i);

        vector<int> last(26, -1);
        dfs(0, adj, s, p, last);

        for (int i = 1; i < n; i++)
            tree[p[i]].push_back(i);

        ans.resize(n);
        calc(0, tree);
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> parent = {-1, 0, 0, 1, 1, 1};
    string s = "abaabc";
    vector<int> res = sol.findSubtreeSizes(parent, s);
    for (int x : res) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}