#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ===================== GLOBAL WAKTU UNTUK STRING SORT =====================
clock_t start_time_str;
#define MAX_LIMIT_SEKON 900.0  // 15 menit (batas maksimum sorting string)

// ===================== HELPER FUNCTION =====================
// Menukar posisi dua pointer string
void swap_str(char **a, char **b) {
    char *tmp = *a;
    *a = *b;
    *b = tmp;
}

// ===================== BUBBLE SORT =====================
// Sorting angka dengan bubble sort
void bubble_sort_int(int arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
}

// Sorting string dengan bubble sort (dengan pembatasan waktu)
void bubble_sort_str(char *arr[], int n) {
    start_time_str = clock();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j], arr[j+1]) > 0)
                swap_str(&arr[j], &arr[j+1]);
            if ((double)(clock() - start_time_str) / CLOCKS_PER_SEC >= MAX_LIMIT_SEKON)
                return;
        }
    }
}

// ===================== SELECTION SORT =====================
// Sorting angka dengan selection sort
void selection_sort_int(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        int tmp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = tmp;
    }
}

// Sorting string dengan selection sort (dengan pembatasan waktu)
void selection_sort_str(char *arr[], int n) {
    start_time_str = clock();
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (strcmp(arr[j], arr[min_idx]) < 0)
                min_idx = j;
            if ((double)(clock() - start_time_str) / CLOCKS_PER_SEC >= MAX_LIMIT_SEKON)
                return;
        }
        swap_str(&arr[i], &arr[min_idx]);
    }
}

// ===================== INSERTION SORT =====================
// Sorting angka dengan insertion sort
void insertion_sort_int(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key)
            arr[j+1] = arr[j--];
        arr[j+1] = key;
    }
}

// Sorting string dengan insertion sort (dengan pembatasan waktu)
void insertion_sort_str(char *arr[], int n) {
    start_time_str = clock();
    for (int i = 1; i < n; i++) {
        char *key = arr[i];
        int j = i - 1;
        while (j >= 0 && strcmp(arr[j], key) > 0) {
            arr[j+1] = arr[j];
            j--;
            if ((double)(clock() - start_time_str) / CLOCKS_PER_SEC >= MAX_LIMIT_SEKON)
                return;
        }
        arr[j+1] = key;
    }
}

// ===================== MERGE SORT =====================
// Fungsi bantu menggabungkan dua array angka
void merge_int(int arr[], int l, int m, int r) {
    int n1 = m-l+1, n2 = r-m;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = arr[l+i];
    for (int j = 0; j < n2; j++) R[j] = arr[m+1+j];
    int i=0, j=0, k=l;
    while (i<n1 && j<n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i<n1) arr[k++] = L[i++];
    while (j<n2) arr[k++] = R[j++];
    free(L); free(R);
}

// Sorting angka dengan merge sort (rekursif)
void merge_sort_int(int arr[], int l, int r) {
    if (l < r) {
        int m = l+(r-l)/2;
        merge_sort_int(arr, l, m);
        merge_sort_int(arr, m+1, r);
        merge_int(arr, l, m, r);
    }
}

// Fungsi bantu menggabungkan dua array string (dengan pembatasan waktu)
void merge_str(char *arr[], int l, int m, int r) {
    int n1 = m-l+1, n2 = r-m;
    char **L = malloc(n1 * sizeof(char*));
    char **R = malloc(n2 * sizeof(char*));
    for (int i = 0; i < n1; i++) L[i] = arr[l+i];
    for (int j = 0; j < n2; j++) R[j] = arr[m+1+j];
    int i=0, j=0, k=l;
    while (i<n1 && j<n2) {
        arr[k++] = (strcmp(L[i], R[j]) <= 0) ? L[i++] : R[j++];
        if ((double)(clock() - start_time_str) / CLOCKS_PER_SEC >= MAX_LIMIT_SEKON) {
            free(L); free(R); return;
        }
    }
    while (i<n1) arr[k++] = L[i++];
    while (j<n2) arr[k++] = R[j++];
    free(L); free(R);
}

// Sorting string dengan merge sort (rekursif dan pembatasan waktu)
void merge_sort_str(char *arr[], int l, int r) {
    if (l < r) {
        if ((double)(clock() - start_time_str) / CLOCKS_PER_SEC >= MAX_LIMIT_SEKON)
            return;
        int m = l + (r - l) / 2;
        merge_sort_str(arr, l, m);
        merge_sort_str(arr, m+1, r);
        merge_str(arr, l, m, r);
    }
}

// ===================== QUICK SORT =====================
// Fungsi bantu untuk quick sort angka
int partition_int(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] < pivot)
            { i++; int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp; }
    int tmp = arr[i+1]; arr[i+1] = arr[high]; arr[high] = tmp;
    return i + 1;
}

// Sorting angka dengan quick sort
void quick_sort_int(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition_int(arr, low, high);
        quick_sort_int(arr, low, pi - 1);
        quick_sort_int(arr, pi + 1, high);
    }
}

// Fungsi bantu untuk quick sort string (dengan pembatasan waktu)
int partition_str(char *arr[], int low, int high) {
    char *pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            swap_str(&arr[i], &arr[j]);
        }
        if ((double)(clock() - start_time_str) / CLOCKS_PER_SEC >= MAX_LIMIT_SEKON)
            return high;
    }
    swap_str(&arr[i+1], &arr[high]);
    return i + 1;
}

// Sorting string dengan quick sort (rekursif dan pembatasan waktu)
void quick_sort_str(char *arr[], int low, int high) {
    if (low < high) {
        if ((double)(clock() - start_time_str) / CLOCKS_PER_SEC >= MAX_LIMIT_SEKON)
            return;
        int pi = partition_str(arr, low, high);
        quick_sort_str(arr, low, pi - 1);
        quick_sort_str(arr, pi + 1, high);
    }
}

// ===================== SHELL SORT =====================
// Sorting angka dengan shell sort
void shell_sort_int(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++) {
            int temp = arr[i], j;
            for (j = i; j >= gap && arr[j-gap] > temp; j -= gap)
                arr[j] = arr[j-gap];
            arr[j] = temp;
        }
}

// Sorting string dengan shell sort (dengan pembatasan waktu)
void shell_sort_str(char *arr[], int n) {
    start_time_str = clock();
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            char *temp = arr[i];
            int j;
            for (j = i; j >= gap && strcmp(arr[j-gap], temp) > 0; j -= gap) {
                arr[j] = arr[j-gap];
                if ((double)(clock() - start_time_str) / CLOCKS_PER_SEC >= MAX_LIMIT_SEKON)
                    return;
            }
            arr[j] = temp;
        }
    }
}

// ===================== PEMBACAAN FILE =====================
// Membaca data angka dari file ke array
int read_numbers(const char *filename, int *arr, int limit) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Gagal membuka file angka");
        return -1;
    }
    int count = 0;
    while (count < limit && fscanf(fp, "%d", &arr[count]) == 1)
        count++;
    fclose(fp);
    return count;
}

// Membaca data kata dari file ke array
int read_words(const char *filename, char **arr, int limit) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Gagal membuka file kata");
        return -1;
    }
    int count = 0;
    char buffer[100];
    while (count < limit && fscanf(fp, "%s", buffer) == 1) {
        arr[count] = strdup(buffer);
        count++;
    }
    fclose(fp);
    return count;
}

// ===================== PENGUKUR WAKTU KHUSUS STRING =====================
// Mengukur waktu eksekusi fungsi sorting string, dan return -1 jika melebihi waktu
double ukur_waktu_kata(void (*sort_fn)(char *[], int), char *arr[], int n) {
    clock_t start = clock();
    sort_fn(arr, n);
    clock_t end = clock();
    double durasi = (double)(end - start) / CLOCKS_PER_SEC;
    return (durasi >= MAX_LIMIT_SEKON) ? -1.0 : durasi;
}

#endif
