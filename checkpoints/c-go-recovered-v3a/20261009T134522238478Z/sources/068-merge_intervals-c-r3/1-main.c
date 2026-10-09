#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("0\n");
        return 0;
    }

    int *L = malloc(n * sizeof(int));
    int *R = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &L[i], &R[i]);
    }

    if (n == 0) {
        printf("0\n");
        free(L);
        free(R);
        return 0;
    }

    // Sort by L ascending, then R ascending for ties
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (L[j] > L[j + 1] || (L[j] == L[j + 1] && R[j] > R[j + 1])) {
                int tmpL = L[j];
                int tmpR = R[j];
                L[j] = L[j + 1];
                R[j] = R[j + 1];
                L[j + 1] = tmpL;
                R[j + 1] = tmpR;
            }
        }
    }

    int count = 0;
    int curL, curR;
    
    // Initialize with first interval
    curL = L[0];
    curR = R[0];
    
    for (int i = 1; i < n; i++) {
        // Merge if overlapping: L[i] <= curR (since intervals are closed)
        if ((long long)L[i] <= curR) {
            if ((long long)L[i] > curL) {
                curL = L[i];
            }
            if ((long long)R[i] > curR) {
                curR = R[i];
            }
        } else {
            count++;
            curL = L[i];
            curR = R[i];
        }
    }
    count++; // Add the last interval

    printf("%d\n", count);
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", L[i], R[i]);
    }

    free(L);
    free(R);
    return 0;
}