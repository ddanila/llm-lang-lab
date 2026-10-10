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
        int left = 0, right = N - 1;
        int ans = N;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] >= x) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        printf("%d\n", ans);
    }

    free(arr);
    return 0;
}