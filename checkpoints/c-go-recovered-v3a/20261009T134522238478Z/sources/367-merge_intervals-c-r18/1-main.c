#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("0\n");
        return 0;
    }

    if (n == 0) {
        printf("0\n");
        return 0;
    }

    // Use long long for interval bounds to avoid overflow during comparisons,
    // though values fit in int. We'll store as int but compare carefully.
    int *l = malloc(n * sizeof(int));
    int *r = malloc(n * sizeof(int));
    if (!l || !r) {
        free(l);
        free(r);
        printf("0\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &l[i], &r[i]);
    }

    // Sort by left endpoint, then by right endpoint
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            int swapped = 0;
            if (l[j] > l[j + 1]) {
                int tmp_l = l[j];
                l[j] = l[j + 1];
                l[j + 1] = tmp_l;
                swapped = 1;
            }
            if (!swapped && l[j] == l[j + 1] && r[j] > r[j + 1]) {
                int tmp_r = r[j];
                r[j] = r[j + 1];
                r[j + 1] = tmp_r;
                swapped = 1;
            }
        }
    }

    // Merge intervals
    int count = 0;
    int *merged_l = malloc(n * sizeof(int));
    int *merged_r = malloc(n * sizeof(int));
    if (!merged_l || !merged_r) {
        free(l);
        free(r);
        printf("0\n");
        return 0;
    }

    merged_l[0] = l[0];
    merged_r[0] = r[0];
    count = 1;

    for (int i = 1; i < n; i++) {
        // Check if current interval overlaps with the last merged interval
        // Overlap condition: intervals [a,b] and [c,d] overlap if c <= b
        // Since we sorted by left endpoint, c >= a, so we only need to check c <= b
        if ((long long)l[i] <= (long long)merged_r[count - 1]) {
            // Merge: extend the right endpoint if needed
            merged_r[count - 1] = (r[i] > merged_r[count - 1]) ? r[i] : merged_r[count - 1];
        } else {
            // No overlap, start a new interval
            count++;
            merged_l[count - 1] = l[i];
            merged_r[count - 1] = r[i];
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d %d\n", merged_l[i], merged_r[i]);
    }

    free(l);
    free(r);
    free(merged_l);
    free(merged_r);

    return 0;
}