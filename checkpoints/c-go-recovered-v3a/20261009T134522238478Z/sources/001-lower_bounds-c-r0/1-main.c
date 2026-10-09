#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, Q;
    if (scanf("%d %d", &N, &Q) != 2) return 0;

    long long *a = malloc(N * sizeof(long long));
    for (int i = 0; i < N; i++) {
        scanf("%lld", &a[i]);
    }

    for (int i = 0; i < Q; i++) {
        long long x;
        scanf("%lld", &x);

        int left = 0, right = N - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (a[mid] >= x) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        printf("%d\n", left);
    }

    free(a);
    return 0;
}