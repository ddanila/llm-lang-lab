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

    int count = 1;
    long long merged_l = intervals[0].l;
    long long merged_r = intervals[0].r;

    for (int i = 1; i < n; ++i) {
        if (intervals[i].l <= merged_r) {
            // Overlap or share endpoint, merge
            if (intervals[i].r > merged_r) {
                merged_r = intervals[i].r;
            }
        } else {
            // No overlap, output previous interval and start new one
            count++;
            merged_l = intervals[i].l;
            merged_r = intervals[i].r;
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < n && i < count; ++i) {
        // We need to output in the order they were created, not from original array
        // Let's collect merged intervals into a separate array
    }

    free(intervals);
    return 0;
}