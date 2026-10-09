#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long L, R;
} Interval;

int compare_intervals(const void *a, const void *b) {
    const Interval *ia = (const Interval *)a;
    const Interval *ib = (const Interval *)b;
    if (ia->L != ib->L) return ia->L > ib->L ? 1 : -1;
    return ia->R > ib->R ? 1 : -1;
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
    for (int i = 0; i < N; i++) {
        scanf("%lld %lld", &intervals[i].L, &intervals[i].R);
    }

    qsort(intervals, N, sizeof(Interval), compare_intervals);

    int count = 1;
    long long merged_L = intervals[0].L;
    long long merged_R = intervals[0].R;

    for (int i = 1; i < N; i++) {
        if (intervals[i].L <= merged_R) {
            // Overlap - merge by extending R if needed
            if (intervals[i].R > merged_R) {
                merged_R = intervals[i].R;
            }
        } else {
            // No overlap - this interval starts a new group
            count++;
            merged_L = intervals[i].L;
            merged_R = intervals[i].R;
        }
    }

    printf("%d\n", count);
    
    // Now output each merged interval by iterating through sorted intervals
    long long current_L = intervals[0].L;
    long long current_R = intervals[0].R;
    
    for (int i = 1; i < N; i++) {
        if (intervals[i].L <= current_R) {
            // Still in the same merge group - extend R if needed
            if (intervals[i].R > current_R) {
                current_R = intervals[i].R;
            }
        } else {
            // End of current group - output and start new group
            printf("%lld %lld\n", current_L, current_R);
            current_L = intervals[i].L;
            current_R = intervals[i].R;
        }
    }
    // Output the last group
    printf("%lld %lld\n", current_L, current_R);

    free(intervals);
    return 0;
}