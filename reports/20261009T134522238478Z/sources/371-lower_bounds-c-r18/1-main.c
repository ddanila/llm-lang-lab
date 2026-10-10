#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;

    long long *arr = malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }

    for (int i = 0; i < q; i++) {
        long long x;
        scanf("%lld", &x);

        int lo = 0, hi = n;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (arr[mid] >= x) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        printf("%d\n", lo);
    }

    free(arr);
    return 0;
}