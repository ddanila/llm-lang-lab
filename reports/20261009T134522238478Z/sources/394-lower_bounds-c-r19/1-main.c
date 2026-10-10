#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;

    long long *arr = malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }

    for (int j = 0; j < q; j++) {
        long long x;
        scanf("%lld", &x);

        int idx = 0;
        while (idx < n && arr[idx] < x) {
            idx++;
        }
        printf("%d\n", idx);
    }

    free(arr);
    return 0;
}