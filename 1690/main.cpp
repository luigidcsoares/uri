#include <algorithm>
#include <iostream>

using namespace std;

// The problem of finding the smallest positive integer not in a sequence can
// be solved in linear time. However, in this case we would need to find every
// possible subarray in A, which is expensive. Thus, we will try a different
// solution. First, we will sort the element in the array A, for the elements
// of a subarray do not need to be adjacent. Then, we will proceed by
// induction:
//
// Assume that we know how to solve for the subproblem of size n - 1. The
// solution will be a number that is at most A[0] + ... + A[n - 2] + 1 (this
// comes from the solution for the problem of finding the smallest positive
// integer not in a sequence). But, we do not want to produce every possible
// sum in A[0 ... n - 2]. So, what we do?
//
// Well, the solution when n == 1 is trivial. If A[0] > 1, then the smallest
// positive integer is 1. Else, it is 2 (because A[0] == 1, since A[0] is
// positive, and thus it cannot be < 1).
//
// Now, we consider the subproblem of size n == 2. We know the solution for n
// == 1. Let's call it s. The possible cases are:
// 1) If s == 1, then s is the solution for the entire problem, due to the fact
// that we have sorted the elements in A. In other words, s = 1 < A[0] < A[1] <
// A[2], and so on.
// 2) If A[1] > subsetSum(A, n - 1), i.e. A[1] > subsetSum(A, 1), then the
// solution for n - 1 is also valid for n, and since A[1] < A[2] < A[3] ...,
// the solution is valid for the entire problem as well.
// 3) If not, i.e. A[1] <= subsetSum(A, n - 1), then:
//  a) The answer cannot be neither A[0], A[1], nor A[0] + A[1].
//  b) The answer must be greater than A[1], so it has to be A[1] + something.
//  c) The answer must be greater than A[0], and we know that s > A[0] is the
//  smallest positive integer > A[0].
// From (a), (b), and (c) we can see that the answer for the subproblem of size
// 2 will be A[1] + s. The same reasoning can be applied for a subproblem of
// size n = k.
long long subsetSum(long long *A, int n) {
    // First, we sort the array A.
    sort(A, A + n);

    // Let's check the base case, i.e. n = 1.
    if (A[0] > 1) return 1;

    // At this point, we know A[0] == 1, so the solution for the subproblem of
    // size 1 is s = 2.
    long long s = 2;

    // Now, we compute the solution for the next subproblems.
    for (int i = 1; i < n; i++) {
        if (A[i] > s) break;
        s += A[i];
    }

    return s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;

        long long A[n];
        for (int i = 0; i < n; i++) cin >> A[i];

        cout << subsetSum(A, n) << "\n";
    }

    return 0;
}
