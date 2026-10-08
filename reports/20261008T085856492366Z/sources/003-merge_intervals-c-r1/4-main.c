#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long L, R;
} Interval;

int cmp(const void *a, const void *b) {
    const Interval *ia = (const Interval *)a;
    const Interval *ib = (const Interval *)b;
    if (ia->L < ib->L) return -1;
    if (ia->L > ib->L) return 1;
    if (ia->R < ib->R) return -1;
    if (ia->R > ib->R) return 1;
    return 0;
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    if (N == 0) {
        printf("0\n");
        return 0;
    }

    Interval *intervals = malloc(N * sizeof(Interval));
    for (int i = 0; i < N; i++) {
        scanf("%lld %lld", &intervals[i].L, &intervals[i].R);
    }

    qsort(intervals, N, sizeof(Interval), cmp);

    int count = 1;
    long long start = intervals[0].L;
    long long end = intervals[0].R;
    for (int i = 1; i < N; i++) {
        if (intervals[i].L <= end) { // overlap or shared endpoint
            if (intervals[i].R > end) end = intervals[i].R;
        } else {
            count++;
            start = intervals[i].L;
            end = intervals[i].R;
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%lld %lld\n", start, end);
    }

    free(intervals);
    return 0;
}