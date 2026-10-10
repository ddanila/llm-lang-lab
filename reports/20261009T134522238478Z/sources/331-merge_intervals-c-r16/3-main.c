#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long L, R;
} Interval;

int compare_intervals(const void *a, const void *b) {
    const Interval *ia = (const Interval *)a;
    const Interval *ib = (const Interval *)b;
    if (ia->L < ib->L) return -1;
    if (ia->L > ib->L) return 1;
    if (ia->R < ib->R) return -1;
    if (ia->R > ib->R) return 1;
    return 0;
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) {
        printf("0\n");
        return 0;
    }

    Interval *arr = malloc(N * sizeof(Interval));
    if (!arr) {
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < N; i++) {
        scanf("%lld %lld", &arr[i].L, &arr[i].R);
    }

    if (N == 0) {
        printf("0\n");
        free(arr);
        return 0;
    }

    qsort(arr, N, sizeof(Interval), compare_intervals);

    Interval *merged = malloc(N * sizeof(Interval));
    int count = 1;
    merged[0].L = arr[0].L;
    merged[0].R = arr[0].R;

    for (int i = 1; i < N; i++) {
        if (arr[i].L <= merged[count - 1].R) {
            if (arr[i].R > merged[count - 1].R) {
                merged[count - 1].R = arr[i].R;
            }
        } else {
            count++;
            merged[count - 1].L = arr[i].L;
            merged[count - 1].R = arr[i].R;
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%lld %lld\n", merged[i].L, merged[i].R);
    }

    free(arr);
    free(merged);
    return 0;
}