#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

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
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (l[j] > l[j + 1] || (l[j] == l[j + 1] && r[j] > r[j + 1])) {
                long long tl = l[j], tr = r[j];
                l[j] = l[j + 1]; r[j] = r[j + 1];
                l[j + 1] = tl; r[j + 1] = tr;
            }
        }
    }

    // Merge intervals: overlap if L <= prev_R (not just adjacent)
    int count = 0;
    long long first_l, first_r;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            first_l = l[i];
            first_r = r[i];
        } else {
            if (l[i] <= first_r) {
                // Overlap or touch at endpoint -> merge
                if (r[i] > first_r) {
                    first_r = r[i];
                }
            } else {
                // No overlap -> push current and start new
                count++;
                first_l = l[i];
                first_r = r[i];
            }
        }
    }
    count++; // Add the last interval

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%lld %lld\n", first_l, first_r);
        // Reset for next iteration
        if (i + 1 < n) {
            // This loop structure is wrong for output. Let's fix.
        }
    }

    return 0;
}