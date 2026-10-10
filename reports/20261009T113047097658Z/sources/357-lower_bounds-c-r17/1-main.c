#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, Q;
    if (scanf("%d %d", &N, &Q) != 2) return 0;

    long long *arr = malloc(N * sizeof(long long));
    for (int i = 0; i < N; i++) {
        scanf("%lld", &arr[i]);
    }

    long long x;
    for (int j = 0; j < Q; j++) {
        if (scanf("%lld", &x) != 1) break;
        int idx = 0;
        while (idx < N && arr[idx] < x) {
            idx++;
        }
        printf("%d\n", idx);
    }

    free(arr);
    return 0;
}