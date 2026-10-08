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
    if (scanf("%d", &N) != 1) return 0;
    
    if (N == 0) {
        printf("0\n");
        return 0;
    }
    
    Interval *intervals = malloc(N * sizeof(Interval));
    if (!intervals) return 1;
    
    for (int i = 0; i < N; i++) {
        scanf("%lld %lld", &intervals[i].L, &intervals[i].R);
    }
    
    qsort(intervals, N, sizeof(Interval), compare_intervals);
    
    int count = 1;
    long long start = intervals[0].L;
    long long end = intervals[0].R;
    
    for (int i = 1; i < N; i++) {
        if (intervals[i].L <= end) {
            if (intervals[i].R > end) {
                end = intervals[i].R;
            }
            count++;
        } else {
            start = intervals[i].L;
            end = intervals[i].R;
        }
    }
    
    printf("%d\n", count);
    for (int i = 0; i < N; i++) {
        if (i == 0) continue;
        long long curL = intervals[i].L;
        long long curR = intervals[i].R;
        
        if (curL <= end && curR > start) {
            // Already merged, skip
            continue;
        } else if (curL > end) {
            printf("%lld %lld\n", start, end);
            start = curL;
            end = curR;
        } else {
            // This case shouldn't happen with proper logic
            printf("%lld %lld\n", start, end);
            start = curL;
            end = curR;
        }
    }
    
    free(intervals);
    return 0;
}