#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int *l = malloc(n * sizeof(int));
    int *r = malloc(n * sizeof(int));
    if (!l || !r) return 1;

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &l[i], &r[i]);
    }

    if (n == 0) {
        printf("0\n");
        free(l);
        free(r);
        return 0;
    }

    // Sort intervals by L ascending, then R ascending for ties
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            int tmp_l = l[j];
            int tmp_r = r[j];
            if (l[j] > l[j + 1] || (l[j] == l[j + 1] && r[j] > r[j + 1])) {
                l[j] = l[j + 1];
                r[j] = r[j + 1];
                l[j + 1] = tmp_l;
                r[j + 1] = tmp_r;
            }
        }
    }

    int count = 0;
    long long cur_l = l[0];
    long long cur_r = r[0];

    for (int i = 1; i < n; i++) {
        if ((long long)l[i] <= cur_r) {
            // Overlapping or sharing endpoint -> merge
            if ((long long)r[i] > cur_r) {
                cur_r = r[i];
            }
        } else {
            // Non-overlapping -> output current and start new
            count++;
            cur_l = l[i];
            cur_r = r[i];
        }
    }
    count++; // Add the last interval

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%lld %lld\n", cur_l, cur_r);
        if (i == count - 1) break;
    }

    free(l);
    free(r);
    return 0;
}