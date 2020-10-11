#include <functional>
#include <iostream>
#include <utility>

using namespace std;

const int maxN = 40;
int fib[maxN];
int calls[maxN];

pair<int, int> fibonacci(int n) {
    // If we have already computed fib(n), just use the precomputed
    // solution.
    if (fib[n] != -1) return make_pair(fib[n], calls[n]);

    // The base case happens when n = 0 or n = 1. We have that fib(0) = 0
    // and fib(1) = 1;
    if (n == 0 || n == 1) {
        fib[n] = n;
        calls[n] = 0;
    }

    // The recursive step requires 2 calls, so we get the number of calls
    // for the two subproblems and increase it by 2.
    else {
        auto [i, ci] = fibonacci(n - 2);
        auto [j, cj] = fibonacci(n - 1);
        fib[n] = i + j;
        calls[n] = ci + cj + 2;
    }

    return make_pair(fib[n], calls[n]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Initialize every position with -1 to indicate that it wasn't computed
    // yet.
    for (int i = 0; i < maxN; i++) fib[i] = calls[i] = -1;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        auto [fib, calls] = fibonacci(x);
        cout << "fib(" << x << ")"
             << " = " << calls << " calls = " << fib << "\n";
    }

    return 0;
}
