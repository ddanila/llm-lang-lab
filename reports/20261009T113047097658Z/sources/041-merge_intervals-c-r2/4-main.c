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

    // Merge intervals
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (count == 0) {
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
            // Store merged interval in output buffer
        } else {
            // Check overlap with last stored interval
            long prevL, prevR;
            if (intervals[i].L <= prevR) {
                if (intervals[i].R > prevR) {
                    prevR = intervals[i].R;
                }
            } else {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}