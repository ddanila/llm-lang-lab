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

        int left = 0, right = N;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] >= x) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        printf("%d\n", left);
    }

    free(arr);
    return 0;
}