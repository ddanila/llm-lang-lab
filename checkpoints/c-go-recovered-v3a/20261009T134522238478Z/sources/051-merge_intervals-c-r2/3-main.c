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

    // Merge intervals and store results in a separate array
    int count = 0;
    long long start, end;
    
    // Initialize first interval
    start = l[0];
    end = r[0];
    count = 1;
    
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

    // Store merged intervals in separate arrays
    long long *ml = malloc(count * sizeof(long long));
    long long *mr = malloc(count * sizeof(long long));
    
    int mc = 0;
    start = l[0];
    end = r[0];
    
    for (int i = 0; i < count; i++) {
        ml[mc] = start;
        mr[mc] = end;
        mc++;
        
        if (i + 1 < n && l[i + 1] > end) {
            start = l[i + 1];
            end = r[i + 1];
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%lld %lld\n", ml[i], mr[i]);
    }

    free(l);
    free(r);
    free(ml);
    free(mr);
    return 0;
}