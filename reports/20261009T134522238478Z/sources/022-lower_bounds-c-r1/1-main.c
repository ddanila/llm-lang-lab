#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, Q;
    if (scanf("%d %d", &N, &Q) != 2) return 0;

    long long *arr = malloc(N * sizeof(long long));
    if (!arr) return 1;

    for (int i = 0; i < N; i++) {
        scanf("%lld", &arr[i]);
    }

    for (int q = 0; q < Q; q++) {
        long long x;
        scanf("%lld", &x);

        int lo = 0, hi = N - 1;
        int ans = N;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (arr[mid] >= x) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }

        printf("%d\n", ans);
    }

    free(arr);
    return 0;
}