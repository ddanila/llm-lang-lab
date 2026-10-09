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
    int N;
    if (scanf("%d", &N) != 1) {
        printf("0\n");
        return 0;
    }

    Interval *intervals = malloc(sizeof(Interval) * N);
    if (!intervals) {
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < N; i++) {
        scanf("%lld %lld", &intervals[i].L, &intervals[i].R);
    }

    if (N == 0) {
        printf("0\n");
        free(intervals);
        return 0;
    }

    qsort(intervals, N, sizeof(Interval), compare_intervals);

    Interval *merged = malloc(sizeof(Interval) * N);
    int mcount = 0;

    merged[0].L = intervals[0].L;
    merged[0].R = intervals[0].R;
    mcount = 1;

    for (int i = 1; i < N; i++) {
        if (intervals[i].L <= merged[mcount - 1].R) {
            if (intervals[i].R > merged[mcount - 1].R) {
                merged[mcount - 1].R = intervals[i].R;
            }
        } else {
            merged[mcount].L = intervals[i].L;
            merged[mcount].R = intervals[i].R;
            mcount++;
        }
    }

    printf("%d\n", mcount);
    for (int i = 0; i < mcount; i++) {
        printf("%lld %lld\n", merged[i].L, merged[i].R);
    }

    free(intervals);
    free(merged);
    return 0;
}