#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct Frog {
    // List of possible locations that the frog can be/jump to.
    std::vector<int> L;
    // The maximum size of a short jump.
    int X;
    // The maximum size of a long jump.
    int Y;
};

const long Inf = std::numeric_limits<int>::max();
long minJumps(Frog &F) {
    int n = F.L.size();
    // S[j][0] is the best solution for the subproblem 0..j, considering that j
    // was reached by taken a short jump. Similarly, S[j][0] is the best
    // solution considering a long jump to j. That is, the design of the
    // solution is by induction, and the inductive hypothesis is that we know
    // the best solution for a subproblem 0..j considering that r will be
    // reached by taken a short jump, and also considering a long jump.
    int S[n][2];
    for (int j = 1; j < n; j++) S[j][0] = S[j][1] = Inf;
    S[0][0] = S[0][1] = 0;
    // We proceed as follows: a short jump has a max size X, while a long jump
    // has a max size Y. For each position j, we want the farthest position i <
    // j such that can be a jump from i to j. We keep the same position until
    // it cannot reach position j. Since there are two types of jumps, we let x
    // be the position for a short jump and y for a long.
    int x = 0, y = 0;
    for (int j = 1; j < n; j++) {
        // Find the farthest position < j for a short jump. We test if either
        // S[x][0] or S[x][1] is less than Inf because we want at least one
        // possible jump (if there's no such position, there is no solution
        // considering a short jump to j).
        while (x < j - 1 && F.L[x] + F.X < F.L[j]) x++;
        while (x < j - 1 && S[x][0] == Inf && S[x][1] == Inf) x++;
        // Similarly for a long jump, but this time we only look for S[x][0]
        // because there cannot be two long jumps in a row.
        while (y < j - 1 && F.L[y] + F.Y < F.L[j]) y++;
        while (y < j - 1 && S[y][0] == Inf) y++;
        // When considering a short jump to j, the previous jump does not
        // matter. Thus, we consider the minimum between the solutions.
        int min = std::min(S[x][0], S[x][1]);
        if (min < Inf && F.L[x] + F.X >= F.L[j]) S[j][0] = min + 1;
        // For a long jump, the previous cannot have been a long. In this case,
        // we only consider the solution for reaching y with a short jump.
        if (S[y][0] < Inf && F.L[y] + F.Y >= F.L[j]) S[j][1] = S[y][0] + 1;
    }
    // The best solution for the problem 0..n - 1 is the minimum between the
    // two solutions (reaching n - 1 with a short or a long jump).
    return std::min(S[n - 1][0], S[n - 1][1]);
}

int main() {
    int N, M;
    cin >> N;
    cin >> M;

    // The initial margin is at the first position (0), while the other margin
    // is at Mth position (M-1). Also, there are N rocks. Thus, there are N + 2
    // positions that the frog can be.
    Frog F;
    F.L.resize(N + 2);

    F.L[0] = 1;
    F.L[N + 1] = M;

    for (int i = 1; i <= N; i++) cin >> F.L[i];

    cin >> F.X;
    cin >> F.Y;

    int numJ = minJumps(F);
    if (numJ == Inf)
        cout << -1 << "\n";
    else
        cout << numJ << "\n";

    return 0;
}
