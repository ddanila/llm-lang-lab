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

    // Sort intervals by L, then by R using insertion sort
    for (int i = 1; i < n; i++) {
        int j = i;
        while (j > 0) {
            if (l[j-1] > l[j]) {
                long long temp_l = l[j];
                long long temp_r = r[j];
                l[j] = l[j-1];
                r[j] = r[j-1];
                l[j-1] = temp_l;
                r[j-1] = temp_r;
                j--;
            } else {
                break;
            }
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