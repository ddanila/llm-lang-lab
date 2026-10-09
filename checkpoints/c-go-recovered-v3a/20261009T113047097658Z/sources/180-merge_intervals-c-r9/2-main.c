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
            // Overlap or touch at endpoint - merge
            if (intervals[i].R > merged_R) {
                merged_R = intervals[i].R;
            }
        } else {
            // No overlap - output current and start new
            count++;
            merged_L = intervals[i].L;
            merged_R = intervals[i].R;
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < N; i++) {
        if (i == 0) {
            // Output first merged interval
            long long current_L = merged_L;
            long long current_R = merged_R;
            
            // Find how many intervals are in the first merge group
            int j = 1;
            while (j < N && intervals[j].L <= current_R) {
                if (intervals[j].R > current_R) current_R = intervals[j].R;
                j++;
            }
            printf("%lld %lld\n", current_L, current_R);
            
            // Continue with next group starting from j
            current_L = intervals[j].L;
            current_R = intervals[j].R;
            while (j < N && intervals[j+1].L <= current_R) {
                if (intervals[j+1].R > current_R) current_R = intervals[j+1].R;
                j++;
            }
            printf("%lld %lld\n", current_L, current_R);
            
            // Continue until end
            while (j < N) {
                current_L = intervals[j].L;
                current_R = intervals[j].R;
                j++;
                if (j < N && intervals[j].L <= current_R) {
                    if (intervals[j].R > current_R) current_R = intervals[j].R;
                } else {
                    printf("%lld %lld\n", current_L, current_R);
                    if (j < N) {
                        current_L = intervals[j].L;
                        current_R = intervals[j].R;
                    }
                }
            }
        } else {
            // This branch will never be reached with current logic
        }
    }

    free(intervals);
    return 0;
}