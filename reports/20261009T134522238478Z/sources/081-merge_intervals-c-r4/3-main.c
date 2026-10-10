#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long l, r;
} Interval;

int cmp(const void *a, const void *b) {
    const Interval *ia = (const Interval *)a;
    const Interval *ib = (const Interval *)b;
    if (ia->l != ib->l) return (ia->l > ib->l) - (ia->l < ib->l);
    return (ia->r > ib->r) - (ia->r < ib->r);
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Interval *intervals = malloc(n * sizeof(Interval));
    if (!intervals) return 0;

    for (int i = 0; i < n; ++i) {
        scanf("%lld %lld", &intervals[i].l, &intervals[i].r);
    }

    if (n == 0) {
        printf("0\n");
        free(intervals);
        return 0;
    }

    qsort(intervals, n, sizeof(Interval), cmp);

    // Collect merged intervals into a separate array
    Interval *merged = malloc(n * sizeof(Interval));
    int count = 0;

    merged[count].l = intervals[0].l;
    merged[count].r = intervals[0].r;
    count++;

    for (int i = 1; i < n; ++i) {
        if (intervals[i].l <= merged[count - 1].r) {
            // Overlap or share endpoint, merge
            if (intervals[i].r > merged[count - 1].r) {
                merged[count - 1].r = intervals[i].r;
            }
        } else {
            // No overlap, start new interval
            merged[count].l = intervals[i].l;
            merged[count].r = intervals[i].r;
            count++;
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; ++i) {
        printf("%lld %lld\n", merged[i].l, merged[i].r);
    }

    free(intervals);
    free(merged);
    return 0;
}