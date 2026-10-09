#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long L, R;
} Interval;

int compare_intervals(const void *a, const void *b) {
    const Interval *ia = (const Interval *)a;
    const Interval *ib = (const Interval *)b;
    if (ia->L != ib->L) return (ia->L > ib->L) - (ia->L < ib->L);
    return (ia->R > ib->R) - (ia->R < ib->R);
}

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

    Interval *intervals = malloc(N * sizeof(Interval));
    if (!intervals) return 1;

    for (int i = 0; i < N; ++i) {
        scanf("%lld %lld", &intervals[i].L, &intervals[i].R);
    }

    qsort(intervals, N, sizeof(Interval), compare_intervals);

    // Merge intervals into a separate array
    Interval *merged = malloc(N * sizeof(Interval));
    if (!merged) { free(intervals); return 1; }

    int count = 0;
    merged[0].L = intervals[0].L;
    merged[0].R = intervals[0].R;
    count = 1;

    for (int i = 1; i < N; ++i) {
        if (intervals[i].L <= merged[count - 1].R) {
            if (intervals[i].R > merged[count - 1].R) {
                merged[count - 1].R = intervals[i].R;
            }
        } else {
            merged[count].L = intervals[i].L;
            merged[count].R = intervals[i].R;
            count++;
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; ++i) {
        printf("%lld %lld\n", merged[i].L, merged[i].R);
    }

    free(intervals);
    free(merged);
    return 0;
}