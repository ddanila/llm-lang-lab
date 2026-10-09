#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("0\n");
        return 0;
    }

    long long *L = malloc(n * sizeof(long long));
    long long *R = malloc(n * sizeof(long long));
    if (!L || !R) {
        free(L);
        free(R);
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &L[i], &R[i]);
    }

    if (n == 0) {
        free(L);
        free(R);
        printf("0\n");
        return 0;
    }

    // Sort intervals by L, then by R
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            int swapped = 0;
            if (L[j] > L[j + 1]) {
                long long tmpL = L[j];
                long long tmpR = R[j];
                L[j] = L[j + 1];
                R[j] = R[j + 1];
                L[j + 1] = tmpL;
                R[j + 1] = tmpR;
                swapped = 1;
            } else if (L[j] == L[j + 1] && R[j] > R[j + 1]) {
                long long tmpL = L[j];
                long long tmpR = R[j];
                L[j] = L[j + 1];
                R[j] = R[j + 1];
                L[j + 1] = tmpL;
                R[j + 1] = tmpR;
                swapped = 1;
            }
            if (swapped) {
                // restart to ensure stability and correctness
                for (int k = 0; k < n - 1; k++) {
                    for (int m = 0; m < n - 1 - k; m++) {
                        int sw = 0;
                        if (L[m] > L[m + 1]) {
                            long long tL = L[m];
                            long long tR = R[m];
                            L[m] = L[m + 1];
                            R[m] = R[m + 1];
                            L[m + 1] = tL;
                            R[m + 1] = tR;
                            sw = 1;
                        } else if (L[m] == L[m + 1] && R[m] > R[m + 1]) {
                            long long tL = L[m];
                            long long tR = R[m];
                            L[m] = L[m + 1];
                            R[m] = R[m + 1];
                            L[m + 1] = tL;
                            R[m + 1] = tR;
                            sw = 1;
                        }
                        if (sw) break;
                    }
                    if (sw) break;
                }
            }
        }
    }

    int count = 1;
    for (int i = 1; i < n; i++) {
        // Merge if overlapping: L[i] <= current_R (closed intervals overlap at shared endpoint)
        if (L[i] <= R[count - 1]) {
            // Extend the current interval
            if (R[i] > R[count - 1]) {
                R[count - 1] = R[i];
            }
        } else {
            count++;
            L[count - 1] = L[i];
            R[count - 1] = R[i];
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%lld %lld\n", L[i], R[i]);
    }

    free(L);
    free(R);
    return 0;
}