#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, Q;
    if (scanf("%d %d", &N, &Q) != 2) return 0;
    
    long long *arr = malloc(N * sizeof(long long));
    if (!arr) return 1;
    
    for (int i = 0; i < N; i++) {
        scanf("%lld", &arr[i]);
    }
    
    for (int i = 0; i < Q; i++) {
        long long x;
        scanf("%lld", &x);
        
        int idx = 0;
        while (idx < N && arr[idx] < x) {
            idx++;
        }
        printf("%d\n", idx);
    }
    
    free(arr);
    return 0;
}