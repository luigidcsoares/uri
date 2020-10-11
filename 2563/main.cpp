#include <iostream>

using namespace std;

// This problem is basically the knapsack problem. Thus, we can solve it with
// dynamic programming.
int maxAmount(int *W, int *C, int n, int k) {
    int M[n + 1][k + 1];
    for (int i = 0; i < n + 1; i++) M[i][0] = 0;
    for (int j = 0; j < k + 1; j++) M[0][j] = 0;
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < k + 1; j++) {
            int wi = W[i - 1], ci = C[i - 1];
            if (wi > j)
                M[i][j] = M[i - 1][j];
            else
                M[i][j] = std::max(M[i - 1][j], M[i - 1][j - wi] + ci);
        }
    }
    return M[n][k];
}

int main() {
    int n;
    while (cin >> n) {
        // The maximum capacity of the professor's lab.
        int k;
        cin >> k;

        // How many candies can be obtained.
        int C[n];
        for (int i = 0; i < n; i++) cin >> C[i];

        // Weight of each "analógimôn".
        int W[n];
        for (int i = 0; i < n; i++) cin >> W[i];

        cout << maxAmount(W, C, n, k) << "\n";
    }

    return 0;
}
