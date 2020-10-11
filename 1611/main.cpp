#include <iostream>

using namespace std;

// Note: Cormen 3ed. (english), page 31 (modified a little bit to sort in
// descending order).
void merge(int *A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1 + 1], R[n2 + 1];

    for (int i = 0; i < n1; i++) L[i] = A[p + i];
    for (int j = 0; j < n2; j++) R[j] = A[q + j + 1];

    L[n1] = R[n2] = -1;
    int i = 0, j = 0;

    for (int k = p; k <= r; k++) {
        if (L[i] > R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
}

// Sort array A in >> descending << order.
// Note: Cormen 3ed. (english), page 34.
void mergesort(int *A, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergesort(A, p, q);
        mergesort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

// We can reduce the problem of finding the minimum energy used by the
// elevator to something similar to sorting the floors that each person
// want to go.
//
// The base case (trivial case) of the problem happens when M <= C.  That is,
// the group of M people can use the elevador at the same time. In this case,
// the solution is the maximum floor times 2 (since the elevator must return to
// the floor 0).
//
// Assume that M > C. Then, there will be groups of people using the elevator
// together. Consider two groups A and B. Let min{A} be the minimum floor in A,
// and max{A} the maximum floor (similar to B). The cost of the two groups will
// be 2 * (max{A} + max{B}). Now, consider that max{A} > min{B}. If we move
// max{A} to B (name it B') and min{B} to A (name it A'), we end up with a cost
// 2 * {max{A'} + max{B'}}. Note that max{A'} < max{A} and max{B'} =
// max{max{A}, max{B}}. Clearly, we have reduced the cost of energy.
//
// In order words, we can reduce this to a sorting problem. We sort the floors
// in descending order, because it is better to let a smaller group of people
// using the elevator to go the minimum floor than to go to the maximum.
// Consider the situation where groups does not have the same number of people.
// For instance, assume that there K groups of C people and 1 people lefting.
// The cost will be minimized if we let this last people go to the minimum
// floor than to the maximum. To clarify, consider the following input:
//
// C = 2, M = 3 and floors = [1, 2, 3]. If we sort in ascending order (it is
// already sorted), we have two groups: {1, 2} and {3}. The cost of the first
// is 2 * 2 = 4. The cost of the second is 3 * 2 = 6. Hence, the total cost is
// 6 + 4 = 10. If instead, we sort in descending order (i.e. 3, 2, 1), the
// first group would be {3, 2} and the second {1}. The cost of the first is 3 *
// 2 = 6, while the cost of the second is 2 * 1 = 1. Thus, the total cost is 6
// + 2 = 8 < 10. The main observation is that >> we will have to move the
// elevator to the maximum floor at some point <<, so it is better to take
// together people that will go to floors as close as possible to the maximum.
int minEnergy(int C, int M, int *floors) {
    // Theta(M·log M)
    mergesort(floors, 0, M - 1);

    int sum = 0;
    // O(M) -- the worst case happens when C = 1.
    for (int i = 0; i < M; i += C) sum += 2 * floors[i];

    // Therefore, the final complexity is O(M·log M).
    return sum;
}

int main() {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        int N, C, M;
        cin >> N; // Not used :/
        cin >> C;
        cin >> M;

        int floors[M];
        for (int i = 0; i < M; i++) cin >> floors[i];

        cout << minEnergy(C, M, floors) << "\n";
    }

    return 0;
}
