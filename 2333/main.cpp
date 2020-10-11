#include <algorithm>
#include <iostream>

using namespace std;

// Note that this problem is quite similar to finding the maximum subarray sum,
// but in a circular list since the last element is adjacent to the first.
//
// For instance, given the circular property, we can have a solution as
// follows:
// - A = [a1, a2, ..., an] is the input of size n.
// - S = [ai, ..., an, a1, ..., ai-1] is the solution.
//
// The most ingenuous solution would be to run he maximum subarray sum
// algorithm for each possible starting point. This approach would run in
// Theta(n²). We can try to do better, though. We need to run the maximum
// subarray algorithm for different intial elements, but for how many? Note
// that there exists an inverse problem A' = {a * -1 | a in A}. We can search
// for the maximum subarray in A' (this time considering A as a simple list,
// not circular). Let s' be the solution for A'. If you consider A as an array
// (without the circular property), then s' A' is the worse solution for A. If
// s' is 0, there is no such worst solution; thus, we can just run the maximum
// subarray for A a single time. Otherwise, we run the maximum subarray for A,
// starting at the first element, and also run for A but starting at the first
// element right after s'. The best solution will be the max between the two.
int maxSum(int *A, int n) {
    // Find the inverse of A:
    int Ainv[n];
    for (int i = 0; i < n; i++) Ainv[i] = A[i] * -1;
    // Now we find the best solution for Ainv. We keep track of the first
    // element "j" right after the best solution.
    int maxInv = 0, suffix = 0, j = -1;
    for (int i = 0; i < n; i++) {
        int newSuffix = suffix + Ainv[i];
        // If the new suffix is better than the previous maximum subarray, it
        // is the best solution thus far.
        if (newSuffix > maxInv) maxInv = newSuffix, j = i + 1;
        // If the newSuffix is positive, than it is okay. Else, it is better to
        // consider an empty suffix.
        if (newSuffix > 0)
            suffix = newSuffix;
        else
            suffix = 0;
    }
    // We now run the first time for A, starting at the first element.
    int max1 = 0;
    suffix = 0;
    for (int i = 0; i < n; i++) {
        int newSuffix = suffix + A[i];
        if (newSuffix > max1) max1 = newSuffix;
        if (newSuffix > 0)
            suffix = newSuffix;
        else
            suffix = 0;
    }
    // If j == -1, then the best solution for the inverse problem is the empty
    // subarray, which means that there is no worse solution in the original
    // problem. Moreover, if n == n, then the best solution for the inverse
    // problem is the entire subarray. In this case, we can get the best
    // solution for A with a single run as well.
    if (j == -1 || j == n) return max1;
    // Now, we run again for A, but this time starting at j.
    int max2 = 0;
    suffix = 0;
    for (int i = j; i < j + n; i++) {
        int newSuffix = suffix + A[i % n];
        if (newSuffix > max2) max2 = newSuffix;
        if (newSuffix > 0)
            suffix = newSuffix;
        else
            suffix = 0;
    }
    return std::max(max1, max2);
}

int main() {
    int n;
    cin >> n;

    int A[n];
    for (int i = 0; i < n; i++) cin >> A[i];

    cout << maxSum(A, n) << "\n";
    return 0;
}
