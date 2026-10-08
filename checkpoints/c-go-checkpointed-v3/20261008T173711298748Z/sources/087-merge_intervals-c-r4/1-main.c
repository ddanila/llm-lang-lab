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

    long *l = malloc(n * sizeof(long));
    long *r = malloc(n * sizeof(long));
    for (int i = 0; i < n; i++) {
        scanf("%ld %ld", &l[i], &r[i]);
    }

    // Sort by L, then by R
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (l[j] > l[j + 1] || (l[j] == l[j + 1] && r[j] > r[j + 1])) {
                long tl = l[j];
                long tr = r[j];
                l[j] = l[j + 1];
                r[j] = r[j + 1];
                l[j + 1] = tl;
                r[j + 1] = tr;
            }
        }
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0 || l[i] > r[count - 1]) {
            count++;
        }
    }

    printf("%d\n", count);
    long start = l[0];
    long end = r[0];
    for (int i = 1; i < n; i++) {
        if (l[i] <= end) {
            if (r[i] > end) {
                end = r[i];
            }
        } else {
            printf("%ld %ld\n", start, end);
            start = l[i];
            end = r[i];
        }
    }
    printf("%ld %ld\n", start, end);

    free(l);
    free(r);
    return 0;
}