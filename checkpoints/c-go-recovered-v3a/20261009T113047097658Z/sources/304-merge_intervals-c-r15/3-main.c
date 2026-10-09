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

    int count = 1;
    long long merged_L = intervals[0].L;
    long long merged_R = intervals[0].R;

    for (int i = 1; i < n; i++) {
        if (intervals[i].L <= merged_R) {
            if (intervals[i].R > merged_R) {
                merged_R = intervals[i].R;
            }
        } else {
            count++;
            merged_L = intervals[i].L;
            merged_R = intervals[i].R;
        }
    }

    printf("%d\n", count);
    
    // Store merged intervals in a separate array for easy output
    Interval *merged = malloc(count * sizeof(Interval));
    int m = 0;
    long long curL = intervals[0].L, curR = intervals[0].R;
    
    for (int i = 0; i < n; i++) {
        if (m == 0) {
            merged[m].L = curL;
            merged[m].R = curR;
            m++;
        } else {
            if (curL != merged[m-1].L || curR != merged[m-1].R) {
                merged[m].L = curL;
                merged[m].R = curR;
                m++;
            }
        }
    }
    
    for (int i = 0; i < count; i++) {
        printf("%lld %lld\n", merged[i].L, merged[i].R);
    }

    free(intervals);
    free(merged);
    return 0;
}