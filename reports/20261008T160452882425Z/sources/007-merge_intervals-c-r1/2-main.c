#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long l, r;
} Interval;

int compare_intervals(const void *a, const void *b) {
    const Interval *ia = (const Interval *)a;
    const Interval *ib = (const Interval *)b;
    if (ia->l != ib->l) return (ia->l > ib->l) ? 1 : -1;
    return (ia->r > ib->r) ? 1 : -1;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    if (n == 0) {
        printf("0\n");
        return 0;
    }

    Interval *intervals = malloc(n * sizeof(Interval));
    for (int i = 0; i < n; i++) {
        scanf("%ld %ld", &intervals[i].l, &intervals[i].r);
    }

    qsort(intervals, n, sizeof(Interval), compare_intervals);

    int count = 0;
    Interval merged[n];

    long start = intervals[0].l;
    long end = intervals[0].r;

    for (int i = 1; i < n; i++) {
        if (intervals[i].l <= end) {
            // Overlap or shared endpoint, merge
            if (intervals[i].r > end) {
                end = intervals[i].r;
            }
        } else {
            // No overlap, push current interval and start new one
            merged[count++] = (Interval){start, end};
            start = intervals[i].l;
            end = intervals[i].r;
        }
    }
    // Push the last interval
    merged[count++] = (Interval){start, end};

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%ld %ld\n", merged[i].l, merged[i].r);
    }

    free(intervals);
    return 0;
}