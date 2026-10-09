#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    if (N == 0) {
        printf("0\n");
        return 0;
    }

    long long *L = malloc(N * sizeof(long long));
    long long *R = malloc(N * sizeof(long long));
    for (int i = 0; i < N; i++) {
        scanf("%lld %lld", &L[i], &R[i]);
    }

    // Sort by L ascending, then by R ascending
    int swaps[N];
    for (int i = 0; i < N; i++) swaps[i] = i;

    // Bubble sort (simple enough for N <= 200)
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            if (L[swaps[j]] > L[swaps[j + 1]] ||
                (L[swaps[j]] == L[swaps[j + 1]] && R[swaps[j]] > R[swaps[j + 1]])) {
                int tmp = swaps[j];
                swaps[j] = swaps[j + 1];
                swaps[j + 1] = tmp;
            }
        }
    }

    // Merge intervals
    long long merged_L, merged_R;
    merged_L = L[swaps[0]];
    merged_R = R[swaps[0]];
    int count = 1;

    for (int i = 1; i < N; i++) {
        int idx = swaps[i];
        if (L[idx] <= merged_R) { // Overlap including shared endpoints
            if (R[idx] > merged_R) {
                merged_R = R[idx];
            }
        } else {
            // Output current interval and start new one
            printf("%lld %lld\n", merged_L, merged_R);
            merged_L = L[idx];
            merged_R = R[idx];
            count++;
        }
    }
    // Output last interval
    printf("%lld %lld\n", merged_L, merged_R);

    free(L);
    free(R);
    return 0;
}