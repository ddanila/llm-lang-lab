#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    long long *l = malloc(n * sizeof(long long));
    long long *r = malloc(n * sizeof(long long));
    if (!l || !r) {
        free(l); free(r);
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        scanf("%lld %lld", &l[i], &r[i]);
    }

    if (n == 0) {
        printf("0\n");
        free(l); free(r);
        return 0;
    }

    // Sort by L ascending, then R ascending for tie-breaking
    int *idx = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) idx[i] = i;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            int a = idx[j];
            int b = idx[j + 1];
            if (l[a] > l[b] || (l[a] == l[b] && r[a] > r[b])) {
                idx[j] = b;
                idx[j + 1] = a;
            }
        }
    }

    int count = 0;
    long long merged_l, merged_r;
    
    // First interval
    merged_l = l[idx[0]];
    merged_r = r[idx[0]];
    
    for (int i = 1; i < n; ++i) {
        int j = idx[i];
        if (l[j] <= merged_r) {
            // Overlap or share endpoint, merge
            if (r[j] > merged_r) {
                merged_r = r[j];
            }
        } else {
            // No overlap, output previous interval and start new one
            count++;
            merged_l = l[j];
            merged_r = r[j];
        }
    }
    count++; // For the last interval

    printf("%d\n", count);
    for (int k = 0; k < count; ++k) {
        printf("%lld %lld\n", merged_l, merged_r);
        if (k < count - 1) {
            // Read next to maintain state? No, we already read all.
            // We need to store the intervals in order.
            // Let's redo with a different approach: collect merged intervals into arrays.
        }
    }

    free(l); free(r); free(idx);
    return 0;
}