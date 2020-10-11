#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// First, let's try to visualize a solution. Consider the following instance of
// the problem: [100, 120, 130] and C = 10. In order to guide us to the design
// of the algorithm, let's move backwards. That is, we will first try to sell
// by 130. Either we sell it or not. If we sell, the next node is of type
// "buy", and the same question arises: should I buy it now? For both node
// types, consider the left-hand choice as "yes" and the right-hand as "no":
//
//                                    130 (sell)
//                   120 (buy)                          120 (sell)
//        100 (sell)          100 (buy)        100 (buy)            100 (sell)
//
// We will check the bank balance to find the best current solution. We need
// distinct balances for both types sell and buy. Let S be the balance for sell
// and B for buy. When the node is a leaf, we cannot sell it so the balance is
// zero. However, we can buy it so the balance is its price minus the the cost
// C. Furthermore, we have different interpretations for nodes of type sell and
// buy.
//
// To illustrate:
//
// 1. Consider the node 120 (buy). From the left, the balance would be 0, while
// from the right it would be -100. In this case, we want to know if its better
// to buy by 120 or not. If we buy it, we consider the left balance (0, sell):
// 0 - (120 + 10) = -130. If we don't buy it, then we keep the balance from the
// right (100, buy): -110. Clearly, the best choice is to not buy.
//
// 2. Now, let's see how to handle a node of type sell. Consider the node 120
// (sell) at the right-hand side. We want to know if it is better to sell by
// 120 or not. If we choose to sell, then we need to buy at some day prior to
// this one, i.e. the left-hand side. Otherwise, we keep the solution from the
// right-hand side. From the left, we have a balance of -110, which give us a
// balance of -110 + 120 = 10 if we sell it now. From the right we have a
// balance of 0. Thus, it is better to sell.
//
// We can compute the elements of both types as follows:
//
// B[i] = { - (P[i] + C), if i == 0
//        { max{B[i-1], S[i-1] - (P[i] + C) otherwise
//
// S[i] = { 0, if i == 0
//        { max{S[i-1], B[i-1] + P[i]} otherwise
//
// The final solution is the balance at S[n-1], since we will never want to buy
// in the last day.
int maxProfit(std::vector<int> P, int C) {
    int n = P.size();
    std::vector<int> B(n);
    std::vector<int> S(n);

    B[0] = -P[0] - C;
    S[0] = 0;

    for (int i = 1; i < n; i++) {
        B[i] = std::max(B[i - 1], S[i - 1] - P[i] - C);
        S[i] = std::max(S[i - 1], B[i - 1] + P[i]);
    }

    return S[n - 1];
}

int main() {
    int N, C;
    cin >> N;
    cin >> C;

    std::vector<int> P(N);
    for (int i = 0; i < N; i++) cin >> P[i];

    cout << maxProfit(P, C) << "\n";
    return 0;
}
