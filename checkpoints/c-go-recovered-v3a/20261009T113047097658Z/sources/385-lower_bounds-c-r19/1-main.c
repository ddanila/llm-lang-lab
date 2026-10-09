#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;

    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int j = 0; j < q; j++) {
        int x;
        scanf("%d", &x);

        int lo = 0, hi = n;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (a[mid] >= x) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        printf("%d\n", lo);
    }

    free(a);
    return 0;
}