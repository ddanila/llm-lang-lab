#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long L;
    long R;
} Interval;

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
    for (int i = 0; i < n; i++) {
        scanf("%ld %ld", &intervals[i].L, &intervals[i].R);
    }

    // Sort by L, then R
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (intervals[j].L > intervals[j + 1].L || 
                (intervals[j].L == intervals[j + 1].L && intervals[j].R > intervals[j + 1].R)) {
                Interval tmp = intervals[j];
                intervals[j] = intervals[j + 1];
                intervals[j + 1] = tmp;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (count == 0) {
            // First interval
            long curL = intervals[i].L;
            long curR = intervals[i].R;
            
            // Try to merge with subsequent intervals
            int j = i + 1;
            while (j < n && intervals[j].L <= curR) {
                if (intervals[j].R > curR) {
                    curR = intervals[j].R;
                }
                j++;
            }
            
            count++;
            // Store merged interval
        } else {
            // Check if this interval overlaps with the last stored one
            long prevL, prevR;
            // We need to store intervals properly
        }
    }

    // Let's redo with proper storage
    free(intervals);
    
    Interval *merged = malloc(n * sizeof(Interval));
    int mcount = 0;
    
    for (int i = 0; i < n; i++) {
        if (mcount == 0) {
            merged[mcount].L = intervals[i].L;
            merged[mcount].R = intervals[i].R;
        } else {
            // Check overlap with last merged interval
            if (intervals[i].L <= merged[mcount - 1].R) {
                // Merge
                if (intervals[i].R > merged[mcount - 1].R) {
                    merged[mcount - 1].R = intervals[i].R;
                }
            } else {
                // No overlap, add new interval
                mcount++;
                merged[mcount].L = intervals[i].L;
                merged[mcount].R = intervals[i].R;
            }
        }
    }

    printf("%d\n", mcount);
    for (int i = 0; i < mcount; i++) {
        printf("%ld %ld\n", merged[i].L, merged[i].R);
    }

    free(intervals);
    free(merged);
    return 0;
}