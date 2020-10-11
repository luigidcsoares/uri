#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Building {
    int l, h, r;
};

vector<int> &merge(vector<int> &L, vector<int> &R) {
    int n = L.size();
    int m = R.size();
    auto S = new vector<int>();

    int hl = 0, hr = 0;
    int l = 0, r = 0, s = 0;

    while (l < n && r < m) {
        int x = 0;

        // If the two coordinates are the same, we move the pointers for both L
        // and R. Otherwise, we move only the pointer of the one with the
        // smaller coordinate.
        if (L[l] == R[r]) {
            x = L[l];
            hl = L[l + 1];
            hr = R[r + 1];
            l += 2;
            r += 2;
        } else if (L[l] < R[r]) {
            x = L[l];
            hl = L[l + 1];
            l += 2;
        } else {
            x = R[r];
            hr = R[r + 1];
            r += 2;
        }

        int h = max(hl, hr);
        if (s == 0 || (*S)[s - 1] != h) {
            S->push_back(x);
            S->push_back(h);
            s += 2;
        }
    }

    while (l < n) {
        S->push_back(L[l]);
        l++;
    }

    while (r < m) {
        S->push_back(R[r]);
        r++;
    }

    return *S;
}

// The straightfoward solution is to assume that we know how to solve for a
// subproblem of size n - 1, and, given the solution to the subproblem, we
// insert the nth building. The complexity of this solution is O(n²). We can
// achieve a better complexity by using a divide and conquer approach. We can
// merge two skylines in a way similar to the one we use to insert the nth
// building into a skyline. Thus, we can assume we know how to solve
// subproblems of size n/2, and then we merge the two skylines. The
// implementation is quite similar to the one for mergesort.
vector<int> &skyline(const vector<Building> &V, int p, int r) {
    if (p == r) {
        auto [l, h, r] = V[p];
        auto S = new vector<int>{l, h, r, 0};
        return *S;
    }

    int q = (p + r + 1) / 2;
    auto L = skyline(V, p, q - 1);
    auto R = skyline(V, q, r);

    return merge(L, R);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Building> V;
    int l, h, r;

    while (cin >> l) {
        cin >> h;
        cin >> r;
        V.push_back(Building{l, h, r});
    }

    auto S = skyline(V, 0, V.size() - 1);
    cout << S[0];
    for (int i = 1; i < S.size(); i++) cout << " " << S[i];
    cout << "\n";

    return 0;
}
