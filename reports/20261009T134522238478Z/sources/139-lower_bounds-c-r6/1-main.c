#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, Q;
    if (scanf("%d %d", &N, &Q) != 2) return 0;

    long long *arr = malloc(N * sizeof(long long));
    for (int i = 0; i < N; i++) {
        scanf("%lld", &arr[i]);
    }

    for (int j = 0; j < Q; j++) {
        long long x;
        scanf("%lld", &x);

        int lo = 0, hi = N - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (arr[mid] >= x) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        if (lo < N && arr[lo] >= x) {
            printf("%d\n", lo);
        } else {
            printf("%d\n", N);
        }
    }

    free(arr);
    return 0;
}