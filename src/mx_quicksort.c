#include "libmx.h"

static void swap(char **a, char **b) {
    char* temp = *a;

    *a = *b;
    *b = temp;
}

int mx_quicksort(char **arr, int left, int right)
{
    int swaps = 0;
    int i = left;
    int j = right;
    int pivot = (i + j) / 2;

    if (i >= j) {
        return 0;
    }
    if (arr == NULL) {
        return -1;
    }

    while (i < j) {
        while (mx_strlen(arr[i]) < mx_strlen(arr[pivot])) {
            i++;
        }
        while (j > left
               && mx_strlen(arr[j]) >= mx_strlen(arr[pivot])) {
            j--;
        }
        if (i < j) {
            swap(&arr[i], &arr[j]);
            swaps++;
        }
    }

    if (i != pivot) {
        swap(&arr[i], &arr[pivot]);
        swaps++;
    }
    swaps += mx_quicksort(arr, left, i - 1);
    swaps += mx_quicksort(arr, i + 1, right);

    return swaps;
}
