#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("0\n");
        return 0;
    }

    int *l = malloc(n * sizeof(int));
    int *r = malloc(n * sizeof(int));
    if (!l || !r) {
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &l[i], &r[i]);
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
                int tmp_l = l[j];
                int tmp_r = r[j];
                l[j] = l[j + 1];
                r[j] = r[j + 1];
                l[j + 1] = tmp_l;
                r[j + 1] = tmp_r;
            }
        }
    }

    int count = 0;
    int start = l[0], end = r[0];
    for (int i = 1; i < n; i++) {
        if (l[i] <= end) {
            // Overlapping or shared endpoint, merge
            if (r[i] > end) {
                end = r[i];
            }
        } else {
            // No overlap, output previous interval
            count++;
            start = l[i];
            end = r[i];
        }
    }
    // Output last interval
    count++;

    printf("%d\n", count);
    for (int i = 0; i < count - 1; i++) {
        // We need to output the merged intervals, but we only stored start/end of current
        // So we need to recompute or store them. Let's fix this.
    }

    // Correct approach: store merged intervals in arrays
    int *ml = malloc(n * sizeof(int));
    int *mr = malloc(n * sizeof(int));
    int mcount = 0;

    start = l[0];
    end = r[0];
    for (int i = 1; i < n; i++) {
        if (l[i] <= end) {
            if (r[i] > end) {
                end = r[i];
            }
        } else {
            ml[mcount] = start;
            mr[mcount] = end;
            mcount++;
            start = l[i];
            end = r[i];
        }
    }
    ml[mcount] = start;
    mr[mcount] = end;
    mcount++;

    printf("%d\n", mcount);
    for (int i = 0; i < mcount; i++) {
        printf("%d %d\n", ml[i], mr[i]);
    }

    free(l);
    free(r);
    free(ml);
    free(mr);

    return 0;
}