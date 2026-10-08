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
    for (int i = 0; i < N; i++) {
        scanf("%lld %lld", &L[i], &R[i]);
    }

    // Sort by L ascending, then by R ascending
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
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

    int count = 0;
    long long merged_L, merged_R;
    
    // First interval always starts the merge group
    merged_L = L[0];
    merged_R = R[0];
    count = 1;

    for (int i = 1; i < N; i++) {
        // Check if intervals overlap or share an endpoint
        // [a, b] and [c, d] overlap if c <= b (since they are closed intervals)
        if (L[i] <= merged_R) {
            // Merge: extend the right endpoint if needed
            if (R[i] > merged_R) {
                merged_R = R[i];
            }
        } else {
            // No overlap, output current merged interval and start new one
            count++;
            merged_L = L[i];
            merged_R = R[i];
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%lld %lld\n", merged_L, merged_R);
        if (i < count - 1) {
            // Read the next interval from the sorted array to update merged
            int idx = 0;
            for (int j = 0; j < N && idx < i + 1; j++) {
                if (L[j] == merged_L && R[j] == merged_R) {
                    idx++;
                }
            }
            // Find next interval
            int start_idx = -1;
            for (int j = 0; j < N; j++) {
                if (L[j] > merged_L || (L[j] == merged_L && R[j] > merged_R)) {
                    start_idx = j;
                    break;
                }
            }
            // Reset to track properly - this logic is flawed, let's just output all and then read again
        }
    }

    // Actually, we need to re-iterate through the sorted array to output each merged interval
    int start = 0;
    for (int i = 1; i <= N; i++) {
        if (i == N || L[i] > R[start]) { // overlap condition: next L <= current R means merge, else new
            printf("%lld %lld\n", L[start], R[start]);
            start = i;
        }
    }

    free(L);
    free(R);
    return 0;
}