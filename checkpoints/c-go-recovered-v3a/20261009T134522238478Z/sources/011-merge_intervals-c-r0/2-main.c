#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long L, R;
} Interval;

int compare_intervals(const void *a, const void *b) {
    const Interval *ia = (const Interval *)a;
    const Interval *ib = (const Interval *)b;
    if (ia->L != ib->L) return (ia->L > ib->L) - (ia->L < ib->L);
    return (ia->R > ib->R) - (ia->R < ib->R);
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("0\n");
        return 0;
    }

    if (n == 0) {
        printf("0\n");
        return 0;
    }

    Interval *intervals = malloc(n * sizeof(Interval));
    if (!intervals) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%ld %ld", &intervals[i].L, &intervals[i].R);
    }

    qsort(intervals, n, sizeof(Interval), compare_intervals);

    Interval *merged = malloc(n * sizeof(Interval));
    if (!merged) {
        free(intervals);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int count = 0;
    merged[count].L = intervals[0].L;
    merged[count].R = intervals[0].R;

    for (int i = 1; i < n; i++) {
        if (intervals[i].L <= merged[count].R) {
            // Overlapping or sharing endpoint: merge
            if (intervals[i].R > merged[count].R) {
                merged[count].R = intervals[i].R;
            }
        } else {
            // Non-overlapping: add new interval
            count++;
            merged[count].L = intervals[i].L;
            merged[count].R = intervals[i].R;
        }
    }

    printf("%d\n", count + 1);
    for (int i = 0; i <= count; i++) {
        printf("%ld %ld\n", merged[i].L, merged[i].R);
    }

    free(intervals);
    free(merged);

    return 0;
}