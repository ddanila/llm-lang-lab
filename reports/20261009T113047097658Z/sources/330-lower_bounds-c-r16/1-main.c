#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;

    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int k = 0; k < q; k++) {
        int x;
        scanf("%d", &x);

        int low = 0, high = n;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (a[mid] >= x) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        printf("%d\n", low);
    }

    free(a);
    return 0;
}