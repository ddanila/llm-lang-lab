#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long L, R;
} Interval;

int compare_intervals(const void *a, const void *b) {
    const Interval *ia = (const Interval *)a;
    const Interval *ib = (const Interval *)b;
    if (ia->L < ib->L) return -1;
    if (ia->L > ib->L) return 1;
    return 0;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("0\n");
        return 0;
    }

    Interval *intervals = malloc(n * sizeof(Interval));
    if (!intervals) {
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &intervals[i].L, &intervals[i].R);
    }

    if (n == 0) {
        printf("0\n");
        free(intervals);
        return 0;
    }

    qsort(intervals, n, sizeof(Interval), compare_intervals);

    // Store merged intervals in a separate array
    Interval *merged = malloc(n * sizeof(Interval));
    int count = 0;
    
    long long curL = intervals[0].L;
    long long curR = intervals[0].R;
    
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            merged[count].L = curL;
            merged[count].R = curR;
            count++;
        } else {
            // Check if current interval overlaps with the last merged one
            if (intervals[i].L <= merged[count-1].R) {
                // Overlap - merge by extending right endpoint
                if (intervals[i].R > merged[count-1].R) {
                    merged[count-1].R = intervals[i].R;
                }
            } else {
                // No overlap - start new interval
                merged[count].L = intervals[i].L;
                merged[count].R = intervals[i].R;
                count++;
            }
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%lld %lld\n", merged[i].L, merged[i].R);
    }

    free(intervals);
    free(merged);
    return 0;
}