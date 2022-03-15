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

void _radixSort(int *l, int *r, int N) {
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
    _radixSort(a, a + n, 8);
}

// Функция "просеивания" через кучу - формирование кучи
void siftDown(int *numbers, int root, int bottom) {
    int maxChild; // индекс максимального потомка
    bool done = 0; // флаг того, что куча сформирована
    // Пока не дошли до последнего ряда
    while ((root * 2 <= bottom) && (!done)) {
        if (root * 2 == bottom)    // если мы в последнем ряду,
            maxChild = root * 2;    // запоминаем левый потомок
            // иначе запоминаем больший потомок из двух
        else if (numbers[root * 2] > numbers[root * 2 + 1])
            maxChild = root * 2;
        else
            maxChild = root * 2 + 1;
        // если элемент вершины меньше максимального потомка
        if (numbers[root] < numbers[maxChild]) {
            int temp = numbers[root]; // меняем их местами
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
        } else // иначе
            done = 1; // пирамида сформирована
    }
}

// Функция сортировки на куче
void heapSort(int *a, size_t n) {
    // Формируем нижний ряд пирамиды
    for (int i = (n / 2); i >= 0; i--)
        siftDown(a, i, n - 1);
    // Просеиваем через пирамиду остальные элементы
    for (int i = n - 1; i >= 1; i--) {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        siftDown(a, 0, i - 1);
    }
}

void merge(const int *a, const int n,
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

    // определяем середину последовательности
    // и рекурсивно вызываем функцию сортировки для каждой половины
    int m = (l + r) / 2;
    mergeSort_(source, l, m, buffer);
    mergeSort_(source, m, r, buffer);

    // производим слияние элементов, результат сохраняем в буфере
    merge(source + l, m - l, source + m, r - m, buffer);
    // переписываем сформированную последовательность с буфера
    // в исходный массив
    memcpy(source + l, buffer, sizeof(int) * n);
}

void mergeSort(int *a, size_t n) {
    // создаём буфер из которого будут браться элементы массива
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