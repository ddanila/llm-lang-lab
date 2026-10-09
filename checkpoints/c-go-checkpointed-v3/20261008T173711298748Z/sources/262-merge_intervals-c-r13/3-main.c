#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("0\n");
        return 0;
    }

    if (n == 0) {
        printf("0\n");
        return 0;
    }

    long long *L = malloc(n * sizeof(long long));
    long long *R = malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &L[i], &R[i]);
    }

    // Sort by L, then by R
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            int swap = 0;
            if (L[j] > L[j + 1]) {
                swap = 1;
            } else if (L[j] == L[j + 1] && R[j] > R[j + 1]) {
                swap = 1;
            }
            if (swap) {
                long long tmpL = L[j];
                long long tmpR = R[j];
                L[j] = L[j + 1];
                R[j] = R[j + 1];
                L[j + 1] = tmpL;
                R[j + 1] = tmpR;
            }
        }
    }

    // Merge intervals
    int merged_count = 0;
    long long *MergedL = malloc(n * sizeof(long long));
    long long *MergedR = malloc(n * sizeof(long long));
    
    MergedL[merged_count] = L[0];
    MergedR[merged_count] = R[0];
    merged_count++;

    for (int i = 1; i < n; i++) {
        // Check if intervals overlap or share endpoints
        // Closed intervals [L, R] and [nextL, nextR] overlap if nextL <= end
        if ((long long)L[i] <= MergedR[merged_count - 1]) {
            // Merge
            if (R[i] > MergedR[merged_count - 1]) {
                MergedR[merged_count - 1] = R[i];
            }
        } else {
            // No overlap, add new interval
            MergedL[merged_count] = L[i];
            MergedR[merged_count] = R[i];
            merged_count++;
        }
    }

    printf("%d\n", merged_count);
    for (int i = 0; i < merged_count; i++) {
        printf("%lld %lld\n", MergedL[i], MergedR[i]);
    }

    free(L);
    free(R);
    free(MergedL);
    free(MergedR);
    return 0;
}