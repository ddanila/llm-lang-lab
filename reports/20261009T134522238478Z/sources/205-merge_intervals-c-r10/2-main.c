#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("0\n");
        return 0;
    }

    long long *l = malloc(n * sizeof(long long));
    long long *r = malloc(n * sizeof(long long));
    if (!l || !r) {
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &l[i], &r[i]);
    }

    if (n == 0) {
        printf("0\n");
        free(l);
        free(r);
        return 0;
    }

    // Sort intervals by L, then by R
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

    // Store merged intervals in arrays
    long long *ml = malloc(n * sizeof(long long));
    long long *mr = malloc(n * sizeof(long long));
    int mcount = 0;

    long long start = l[0];
    long long end = r[0];
    for (int i = 1; i < n; i++) {
        if (l[i] <= end) {
            // Overlapping or shared endpoint, merge
            if (r[i] > end) {
                end = r[i];
            }
        } else {
            // No overlap, output previous interval
            ml[mcount] = start;
            mr[mcount] = end;
            mcount++;
            start = l[i];
            end = r[i];
        }
    }
    // Output last interval
    ml[mcount] = start;
    mr[mcount] = end;
    mcount++;

    printf("%d\n", mcount);
    for (int i = 0; i < mcount; i++) {
        printf("%lld %lld\n", ml[i], mr[i]);
    }

    free(l);
    free(r);
    free(ml);
    free(mr);

    return 0;
}