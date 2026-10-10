#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, Q;
    if (scanf("%d %d", &N, &Q) != 2) return 0;

    int *arr = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    for (int j = 0; j < Q; j++) {
        int x;
        scanf("%d", &x);

        int low = 0, high = N;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] >= x) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        printf("%d\n", low);
    }

    free(arr);
    return 0;
}