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

    int count = 1;
    long long current_L = arr[0].L;
    long long current_R = arr[0].R;

    for (int i = 1; i < N; i++) {
        if (arr[i].L <= current_R) {
            if (arr[i].R > current_R) {
                current_R = arr[i].R;
            }
        } else {
            count++;
            current_L = arr[i].L;
            current_R = arr[i].R;
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%lld %lld\n", current_L, current_R);
        if (i < count - 1) {
            current_L = arr[count + i].L;
            current_R = arr[count + i].R;
        }
    }

    free(arr);
    return 0;
}