#include <stdio.h>
#include <stdlib.h>

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

    long long *l = malloc(n * sizeof(long long));
    long long *r = malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &l[i], &r[i]);
    }

    // Sort intervals by L, then by R
    int count = n;
    while (count > 1) {
        int left = 0;
        int right = count - 1;
        int pivot = l[right];
        while (left < right) {
            if (l[left] < pivot) {
                left++;
            } else if (l[left] > pivot) {
                l[right] = l[left];
                r[right] = r[left];
                right--;
            } else {
                // l[left] == pivot, check R to maintain stable-ish order for equal L
                long long r_left = r[left];
                long long r_right = r[right];
                if (r_left < r_right) {
                    // swap
                    l[right] = l[left];
                    r[right] = r_left;
                    right--;
                } else {
                    left++;
                }
            }
        }
        // place pivot in correct position
        if (left < count - 1) {
            l[left + 1] = pivot;
            r[left + 1] = r[right];
        } else {
            // should not happen with standard partitioning
        }
    }

    int merged_count = 0;
    long long current_l = l[0];
    long long current_r = r[0];

    for (int i = 1; i < n; i++) {
        if (current_r >= l[i]) {
            // overlap, merge
            if (r[i] > current_r) {
                current_r = r[i];
            }
        } else {
            // no overlap, push current interval
            merged_count++;
            current_l = l[i];
            current_r = r[i];
        }
    }
    // push last interval
    merged_count++;

    printf("%d\n", merged_count);
    for (int i = 0; i < merged_count; i++) {
        printf("%lld %lld\n", l[i], r[i]);
    }

    free(l);
    free(r);
    return 0;
}