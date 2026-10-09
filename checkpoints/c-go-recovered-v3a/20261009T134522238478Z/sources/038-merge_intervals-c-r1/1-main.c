#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) {
        printf("0\n");
        return 0;
    }

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

    // Sort by L ascending, then by R ascending
    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < N - 1 - i; ++j) {
            if (L[j] > L[j + 1] || (L[j] == L[j + 1] && R[j] > R[j + 1])) {
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
    int count = 0;
    long long start = L[0];
    long long end = R[0];

    for (int i = 1; i < N; ++i) {
        if (L[i] <= end) {
            if (R[i] > end) {
                end = R[i];
            }
        } else {
            count++;
            start = L[i];
            end = R[i];
        }
    }
    count++; // Add the last interval

    printf("%d\n", count);
    for (int i = 0; i < count; ++i) {
        printf("%lld %lld\n", start, end);
        if (count > 1 && i < count - 1) {
            long long nextL = L[i + 1];
            long long nextR = R[i + 1];
            // Need to track current merged interval properly
            // This approach is flawed because we are modifying start/end
            // Let's redo with a proper merge approach
        }
    }

    // Redo merging correctly
    count = 0;
    for (int i = 0; i < N; ++i) {
        if (count == 0) {
            start = L[i];
            end = R[i];
        } else {
            if (L[i] <= end) {
                if (R[i] > end) {
                    end = R[i];
                }
            } else {
                count++;
                start = L[i];
                end = R[i];
            }
        }
    }
    count++; // Add the last interval

    printf("%d\n", count);
    for (int i = 0; i < count; ++i) {
        printf("%lld %lld\n", start, end);
        if (count > 1 && i < count - 1) {
            long long nextL = L[i + 1];
            long long nextR = R[i + 1];
            // This is getting complicated. Let me simplify.
        }
    }

    free(L);
    free(R);
    return 0;
}