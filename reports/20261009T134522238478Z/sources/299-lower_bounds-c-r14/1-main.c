#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, Q;
    if (scanf("%d %d", &N, &Q) != 2) return 0;

    int *arr = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    for (int q = 0; q < Q; q++) {
        int x;
        scanf("%d", &x);

        int lo = 0, hi = N;
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