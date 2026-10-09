#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, Q;
    if (scanf("%d %d", &N, &Q) != 2) return 0;

    int *arr = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < Q; i++) {
        int x;
        scanf("%d", &x);
        
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