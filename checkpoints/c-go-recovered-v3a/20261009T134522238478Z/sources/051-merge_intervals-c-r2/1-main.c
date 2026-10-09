#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    if (n == 0) {
        printf("0\n");
        return 0;
    }

    long long *l = malloc(n * sizeof(long long));
    long long *r = malloc(n * sizeof(long long));

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &l[i], &r[i]);
    }

    // Sort by L ascending, then by R ascending
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (l[j] > l[j + 1] || (l[j] == l[j + 1] && r[j] > r[j + 1])) {
                long long tmp_l = l[j];
                long long tmp_r = r[j];
                l[j] = l[j + 1];
                r[j] = r[j + 1];
                l[j + 1] = tmp_l;
                r[j + 1] = tmp_r;
            }
        }
    }

    int count = 0;
    long long start = l[0], end = r[0];
    
    for (int i = 1; i < n; i++) {
        // Merge if intervals overlap or share an endpoint
        // Overlap condition: current start <= previous end
        if (l[i] <= end) {
            if (r[i] > end) {
                end = r[i];
            }
        } else {
            count++;
            start = l[i];
            end = r[i];
        }
    }
    count++; // Add the last interval

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%lld %lld\n", l[i], r[i]);
    }

    free(l);
    free(r);
    return 0;
}