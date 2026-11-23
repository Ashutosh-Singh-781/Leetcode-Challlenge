/*
# 1352. Product of the Last K Numbers

- **Difficulty:** Medium
- **Topic:** Array, Math, Design, Data Stream, Prefix Sum
- **Language:** C++
- **LeetCode Link:** [Product of the Last K Numbers](https://leetcode.com/problems/product-of-the-last-k-numbers/)

## Problem Statement
Design an algorithm that accepts a stream of integers and retrieves the product of the last `k` integers of the stream.
Implement the `ProductOfNumbers` class:
- `ProductOfNumbers()` initializes the object with an empty stream.
- `void add(int num)` appends the integer `num` to the stream.
- `int getProduct(int k)` returns the product of the last `k` numbers in the current list. You can assume that always the current list has at least `k` numbers.

At any time, the product of any contiguous sequence of numbers will fit into a single 32-bit integer without overflowing.

## Intuition & Approach
1. **Prefix Products & Resetting on Zero:** Maintain a `prefix` array where `prefix[i]` stores the running product of non-zero elements seen since the most recent `0` (initialized with `{1}`). When `num == 0`, reset `prefix` to `{1}` because any suffix product covering that `0` becomes `0`, and prior products cannot be divided out cleanly.
2. **Querying in $O(1)$:** Let `n = prefix.size()`. There are `n - 1` elements since the last zero. If `k >= n`, the last `k` elements include a `0`, so return `0`; otherwise, return `prefix[n - 1] / prefix[n - 1 - k]`.

## Complexity Analysis
- **Time Complexity:** $O(1)$ amortized per `add` and $O(1)$ per `getProduct`.
- **Space Complexity:** $O(N)$ where $N$ is the number of elements added since the last zero.
*/

#include <bits/stdc++.h>
using namespace std;

class ProductOfNumbers {
    vector<int> prefix{1};  // prefix[i]: the product of the first i numbers after the last zero

public:
    void add(int num) {
        if (num == 0)
            prefix = {1};  // a window that reaches this zero is 0, so forget everything before it
        else
            prefix.push_back(prefix.back() * num);
    }

    int getProduct(int k) {
        int n = prefix.size();
        if (k >= n)  // the window reaches back to a zero
            return 0;
        return prefix[n - 1] / prefix[n - 1 - k];
    }
};

int main() {
    ProductOfNumbers productOfNumbers;
    productOfNumbers.add(3);
    productOfNumbers.add(0);
    productOfNumbers.add(2);
    productOfNumbers.add(5);
    productOfNumbers.add(4);
    cout << productOfNumbers.getProduct(2) << endl;
    cout << productOfNumbers.getProduct(3) << endl;
    cout << productOfNumbers.getProduct(4) << endl;
    productOfNumbers.add(8);
    cout << productOfNumbers.getProduct(2) << endl;
    return 0;
}