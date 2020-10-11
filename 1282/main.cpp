#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

using int64 = long long;

int64 arrangeHeaps(vector<pair<int64, int64>> &A, int64 n, int64 k) {
    // We will first compute the accumulated weights from i to j.
    vector<vector<int64>> W(n);
    for (int64 i = 0; i < n; i++) {
        W[i] = vector<int64>(n);
        W[i][i] = A[i].second;
        for (int64 j = i + 1; j < n; j++) W[i][j] = W[i][j - 1] + A[j].second;
    }

    // Now, we will compute the cost for moving i, i+1, i+2, ..., j-1 to j.
    vector<vector<int64>> C(n);
    for (int64 i = 0; i < n; i++) {
        C[i] = vector<int64>(n);
        C[i][i] = 0;
        for (int64 j = i + 1; j < n; j++) {
            int64 d = A[j].first - A[j - 1].first;
            C[i][j] = C[i][j - 1] + W[i][j - 1] * d;
        }
    }

    // If k = 1, we already have the answer: it is the cost of moving
    // everything from 2 ... n - 2 to n - 1.
    if (k == 1) return C[0][n - 1];

    // For k > 1, we will use dynamic programming to compute the solutions for
    // 1, 2, ..., k - 1, k. Here, index 0 is equivalent to k = 1 and so on.
    vector<vector<int64>> H(k);
    for (int64 i = 0; i < k; i++) H[i] = vector<int64>(n);

    // The solution for k = 1 is simply C[0][0 ... n-1].
    for (int64 j = 0; j < n; j++) H[0][j] = C[0][j];

    for (int64 i = 1; i < k; i++) {
        // When the size of the problem is equal to k, the cost is zero.
        H[i][i] = 0;
        for (int64 j = i + 1; j < n; j++) {
            int64 minCost = H[i - 1][i - 1] + C[i][j];
            for (int64 l = i; l < j; l++) {
                int64 cost = H[i - 1][l] + C[l + 1][j];
                minCost = min(minCost, cost);
            }
            H[i][j] = minCost;
        }
    }

    return H[k - 1][n - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 n, k;
    while (cin >> n) {
        cin >> k;
        vector<pair<int64, int64>> A(n);

        for (int64 i = 0; i < n; i++) {
            int64 x, w;
            cin >> x;
            cin >> w;
            A[i] = {x, w};
        }

        cout << arrangeHeaps(A, n, k) << "\n";
    }

    return 0;
}
