#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, Q;
    if (scanf("%d %d", &N, &Q) != 2) return 0;

    int *a = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < Q; i++) {
        int x;
        scanf("%d", &x);
        int lo = 0, hi = N - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (a[mid] >= x) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        printf("%d\n", lo);
    }

    free(a);
    return 0;
}