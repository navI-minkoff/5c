#include "sorting.h"

void inputArray_(int *const a, const size_t n) {
    for (size_t i = 0; i < n; i++)
        scanf("%d", &a[i]);
}

void outputArray_(const int *const a, const size_t n) {
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int isOrdered(const int *a, const size_t n) {
    for (size_t i = 1; i < n; i++) {
        if (a[i] < a[i - 1])
            return 0;
    }

    return 1;
}

void generateRandomArray(int *a, size_t size) {
    for (int i = 0; i < size; ++i)
        a[i] = rand() % 1000 + 42;
}

void generateOrderedArray(int *a, size_t size) {
    for (int i = 0; i < size - 1; i++)
        a[i] = i;
}

void generateOrderedBackwards(int *a, size_t size) {
    int i = 0;
    int j = size - 1;
    while (j > 0)
        a[i++] = j--;
}

void bubbleSort(int *a, const size_t n) {
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            if (a[i] > a[j])
                swap(&a[i], &a[j]);
}

void selectionSort(int *a, const size_t n) {
    int min;
    for (size_t i = 0; i < n - 1; i++) {
        min = i;
        for (size_t j = i + 1; j < n; j++) {
            if (a[j] < a[min])
                min = j;
        }
        swap(&a[i], &a[min]);
    }
}

void insertionSort(int *a, const size_t size) {
    for (size_t i = 1; i < size; i++) {
        int t = a[i];
        int j = i;
        while (j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
}

void combSort(int *a, const size_t n) {
    size_t step = n;
    int swapped = 1;
    while (step > 1 || swapped) {
        if (step > 1)
            step /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + step; j < n; i++, j++)
            if (a[i] > a[j]) {
                swap(&a[i], &a[j]);
                swapped = 1;
            }
    }
}

void shellSort(int *a, size_t n) {
    int i, j, step, tmp;
    for (step = n / 2; step > 0; step /= 2)
        for (i = step; i < n; i++) {
            tmp = a[i];
            for (j = i; j >= step; j -= step) {
                if (tmp < a[j - step])
                    a[j] = a[j - step];
                else
                    j = step - 1;
            }
            a[j] = tmp;
        }
}

int digit(int n, int k, int N, int M) {
    return (n >> (N * k) & (M - 1));
}

void radixSort_(int *l, int *r, int N) {
    int k = (32 + N - 1) / N;
    int M = 1 << N;
    int sz = r - l;
    int *b = (int *) malloc(sizeof(int) * sz);
    int *c = (int *) malloc(sizeof(int) * M);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < M; j++)
            c[j] = 0;

        for (int *j = l; j < r; j++)
            c[digit(*j, i, N, M)]++;

        for (int j = 1; j < M; j++)
            c[j] += c[j - 1];

        for (int *j = r - 1; j >= l; j--)
            b[--c[digit(*j, i, N, M)]] = *j;

        int cur = 0;
        for (int *j = l; j < r; j++)
            *j = b[cur++];
    }
    free(b);
    free(c);
}

void radixSort(int *a, size_t n) {
    radixSort_(a, a + n, 8);
}

void siftDown(int *numbers, int root, int bottom) {
    int maxChild;
    bool done = 0;
    while ((root * 2 <= bottom) && (!done)) {
        if (root * 2 == bottom)
            maxChild = root * 2;
        else if (numbers[root * 2] > numbers[root * 2 + 1])
            maxChild = root * 2;
        else
            maxChild = root * 2 + 1;
        if (numbers[root] < numbers[maxChild]) {
            int temp = numbers[root];
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
        } else
            done = 1;
    }
}

void heapSort(int *a, size_t n) {
    for (int i = (n / 2); i >= 0; i--)
        siftDown(a, i, n - 1);
    for (int i = n - 1; i >= 1; i--) {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        siftDown(a, 0, i - 1);
    }
}

void getMergeNComps(const int *a, const int n,
                    const int *b, const int m, int *c) {
    int i = 0, j = 0;
    while (i < n || j < m) {
        if (j == m || i < n && a[i] < b[j]) {
            c[i + j] = a[i];
            i++;
        } else {
            c[i + j] = b[j];
            j++;
        }
    }
}

void mergeSort_(int *source, int l, int r, int *buffer) {
    int n = r - l;
    if (n <= 1)
        return;

    int m = (l + r) / 2;
    mergeSort_(source, l, m, buffer);
    mergeSort_(source, m, r, buffer);

    getMergeNComps(source + l, m - l, source + m, r - m, buffer);
    memcpy(source + l, buffer, sizeof(int) * n);
}

void mergeSort(int *a, size_t n) {
    int *buffer = (int *) malloc(sizeof(int) * n);
    mergeSort_(a, 0, n, buffer);
    free(buffer);
}

void qsort_(int *array, size_t n) {
    int i = 0;
    int j = n - 1;
    int mid = array[n / 2];

    do {
        while (array[i] < mid) {
            i++;
        }
        while (array[j] > mid) {
            j--;
        }
        if (i <= j) {
            int tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);
    if (j > 0) {
        qsort_(array, j + 1);
    }
    if (i < n) {
        qsort_(&array[i], n - i);
    }
}

long long getBubbleSortNComps(int *a, const size_t n) {
    long long nComps = 0;
    for (int i = 0; ++nComps && i < n; i++)
        for (int j = i; ++nComps && j < n; j++)
            if (++nComps && a[i] > a[j])
                swap(&a[i], &a[j]);

    return nComps;
}

long long getSelectionSortNComps(int *a, const size_t n) {
    long long nComps = 0;
    int min;
    for (size_t i = 0; ++nComps && i < n - 1; i++) {
        min = i;
        for (size_t j = i + 1; ++nComps && j < n; j++) {
            if (++nComps && a[j] < a[min])
                min = j;
        }
        swap(&a[i], &a[min]);
    }

    return nComps;
}

long long getInsertionSortNComps(int *a, const size_t size) {
    long long nComps = 0;
    for (size_t i = 1; ++nComps && i < size; i++) {
        int t = a[i];
        int j = i;
        while ((nComps += 2) && j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }

    return nComps;
}

long long getCombSortNComps(int *a, const size_t n) {
    long long nComps = 0;
    size_t step = n;
    int swapped = 1;
    while (++nComps && step > 1 || swapped) {
        if (step > 1)
            step /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + step; ++nComps && j < n; i++, j++)
            if (++nComps && a[i] > a[j]) {
                swap(&a[i], &a[j]);
                swapped = 1;
            }
    }

    return nComps;
}

long long getShellSortNComps(int *a, const size_t n) {
    long long nComps = 0;
    int i, j, step, tmp;
    for (step = n / 2; ++nComps && step > 0; step /= 2)
        for (i = step; ++nComps && i < n; i++) {
            tmp = a[i];
            for (j = i; ++nComps && j >= step; j -= step) {
                if (++nComps && tmp < a[j - step])
                    a[j] = a[j - step];
                else
                    j = step - 1;
            }
            a[j] = tmp;
        }

    return nComps;
}

long long _getRadixSortNComps(int *l, int *r, int N) {
    long long nComps = 0;
    int k = (32 + N - 1) / N;
    int M = 1 << N;
    int sz = r - l;
    int *b = (int *) malloc(sizeof(int) * sz);
    int *c = (int *) malloc(sizeof(int) * M);
    for (int i = 0; ++nComps && i < k; i++) {
        for (int j = 0; ++nComps && j < M; j++)
            c[j] = 0;

        for (int *j = l; ++nComps && j < r; j++)
            c[digit(*j, i, N, M)]++;

        for (int j = 1; ++nComps && j < M; j++)
            c[j] += c[j - 1];

        for (int *j = r - 1; ++nComps && j >= l; j--)
            b[--c[digit(*j, i, N, M)]] = *j;

        int cur = 0;
        for (int *j = l; ++nComps && j < r; j++)
            *j = b[cur++];
    }
    free(b);
    free(c);

    return nComps;
}

long long getRadixSortNComps(int *a, const size_t n) {
    return _getRadixSortNComps(a, a + n, 8);
}

long long getSiftDownNComps_(int *numbers, int root, int bottom) {
    long long nComps = 0;
    int maxChild;
    bool done = 0;
    while (++nComps && (root * 2 <= bottom) && (!done)) {
        if (root * 2 == bottom)
            maxChild = root * 2;
        else if (++nComps && numbers[root * 2] > numbers[root * 2 + 1])
            maxChild = root * 2;
        else
            maxChild = root * 2 + 1;
        if (++nComps && numbers[root] < numbers[maxChild]) {
            int temp = numbers[root];
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
        } else
            done = 1;
    }

    return nComps;
}

long long getHeapSortNComps(int *a, const size_t n) {
    long long nComps = 0;
    for (int i = (n / 2); ++nComps && i >= 0; i--)
        nComps += getSiftDownNComps_(a, i, n - 1);
    for (int i = n - 1; ++nComps && i >= 1; i--) {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        nComps += getSiftDownNComps_(a, 0, i - 1);
    }

    return nComps;
}

long long getMergeNComps_(const int *a, const int n,
                    const int *b, const int m, int *c) {
    long long nComps = 0;
    int i = 0, j = 0;
    while ((nComps += 2) && i < n || j < m) {
        if ((nComps += 3) && j == m || i < n && a[i] < b[j]) {
            c[i + j] = a[i];
            i++;
        } else {
            c[i + j] = b[j];
            j++;
        }
    }

    return nComps;
}

long long getMergeSortNComps_(int *source, int l, int r, int *buffer) {
    long long nComps = 0;
    int n = r - l;
    if (++nComps && n <= 1)
        return nComps;

    int m = (l + r) / 2;
    nComps += getMergeSortNComps_(source, l, m, buffer);
    nComps += getMergeSortNComps_(source, m, r, buffer);

    nComps += getMergeNComps_(source + l, m - l, source + m, r - m, buffer);
    memcpy(source + l, buffer, sizeof(int) * n);

    return nComps;
}

long long getMergeSortNComps(int *a, const size_t n) {
    int *buffer = (int *) malloc(sizeof(int) * n);
    long long nComps = getMergeSortNComps_(a, 0, n, buffer);
    free(buffer);

    return nComps;
}

long long getQsortNComps(int *array, const size_t n) {
    long long nComps = 0;
    int i = 0;
    int j = n - 1;
    int mid = array[n / 2];

    do {
        while (++nComps && array[i] < mid) {
            i++;
        }
        while (++nComps && array[j] > mid) {
            j--;
        }
        if (++nComps && i <= j) {
            int tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;

            i++;
            j--;
        }
    } while (++nComps && i <= j);
    if (++nComps && j > 0) {
        nComps += getQsortNComps(array, j + 1);
    }
    if (++nComps && i < n) {
        nComps += getQsortNComps(&array[i], n - i);
    }

    return nComps;
}