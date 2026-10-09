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
    if (!L || !R) {
        free(L);
        free(R);
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        scanf("%lld %lld", &L[i], &R[i]);
    }

    // Sort by L, then by R
    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < N - 1 - i; ++j) {
            int swap = 0;
            if (L[j] > L[j + 1]) {
                swap = 1;
            } else if (L[j] == L[j + 1] && R[j] > R[j + 1]) {
                swap = 1;
            }
            if (swap) {
                long long tL = L[j];
                long long tR = R[j];
                L[j] = L[j + 1];
                R[j] = R[j + 1];
                L[j + 1] = tL;
                R[j + 1] = tR;
            }
        }
    }

    int count = 0;
    long long start = L[0];
    long long end = R[0];

    for (int i = 1; i < N; ++i) {
        // Merge if overlapping or sharing endpoint: max(start, current.L) <= min(end, current.R)
        // For closed intervals [a,b] and [c,d], they overlap if max(a,c) <= min(b,d).
        // If they only touch at endpoints (e.g., [1,2] and [2,3]), max(1,2)=2, min(2,3)=2, so 2<=2 -> merge.
        // But the problem says "NOT merely adjacent integers", meaning [1,2] and [3,4] should not merge.
        // Overlap condition: end >= current.L (since we sorted by L)
        if (end >= L[i]) {
            if (R[i] > end) {
                end = R[i];
            }
        } else {
            count++;
            start = L[i];
            end = R[i];
        }
    }
    count++;

    printf("%d\n", count);
    for (int i = 0; i < count; ++i) {
        // We need to reconstruct the merged intervals. Instead of modifying, let's collect them.
        // Actually, we can just output as we go if we store them. But simpler: use a separate array.
    }

    // Re-do with storage for merged intervals
    free(L);
    free(R);
    L = malloc(N * sizeof(long long));
    R = malloc(N * sizeof(long long));
    if (!L || !R) {
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        scanf("%lld %lld", &L[i], &R[i]);
    }

    // Sort by L, then by R
    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < N - 1 - i; ++j) {
            int swap = 0;
            if (L[j] > L[j + 1]) {
                swap = 1;
            } else if (L[j] == L[j + 1] && R[j] > R[j + 1]) {
                swap = 1;
            }
            if (swap) {
                long long tL = L[j];
                long long tR = R[j];
                L[j] = L[j + 1];
                R[j] = R[j + 1];
                L[j + 1] = tL;
                R[j + 1] = tR;
            }
        }
    }

    // Now merge and count
    int merged_count = 0;
    long long *merged_L = malloc(N * sizeof(long long));
    long long *merged_R = malloc(N * sizeof(long long));
    if (!merged_L || !merged_R) {
        free(L);
        free(R);
        return 1;
    }

    merged_L[0] = L[0];
    merged_R[0] = R[0];
    merged_count = 1;

    for (int i = 1; i < N; ++i) {
        if (merged_R[merged_count - 1] >= L[i]) {
            // Overlap or touch at endpoint -> merge
            if (R[i] > merged_R[merged_count - 1]) {
                merged_R[merged_count - 1] = R[i];
            }
        } else {
            // No overlap -> new interval
            merged_L[merged_count] = L[i];
            merged_R[merged_count] = R[i];
            merged_count++;
        }
    }

    printf("%d\n", merged_count);
    for (int i = 0; i < merged_count; ++i) {
        printf("%lld %lld\n", merged_L[i], merged_R[i]);
    }

    free(L);
    free(R);
    free(merged_L);
    free(merged_R);
    return 0;
}