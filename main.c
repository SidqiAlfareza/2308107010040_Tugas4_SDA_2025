#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

#define MAX_SIZE 2000000

void print_menu() {
    printf("===== PILIH JENIS DATA =====\n");
    printf("1. Data Angka (data_angka.txt)\n");
    printf("2. Data Kata  (data_kata.txt)\n");
}

void print_data_options() {
    printf("===== PILIH JUMLAH DATA =====\n");
    printf("1. 10.000\n2. 50.000\n3. 100.000\n4. 250.000\n");
    printf("5. 500.000\n6. 1.000.000\n7. 1.500.000\n8. 2.000.000\n");
}

int get_data_amount(int option) {
    int options[] = {10000, 50000, 100000, 250000, 500000, 1000000, 1500000, 2000000};
    if (option < 1 || option > 8) return -1;
    return options[option - 1];
}

void print_memory_usage(const char *algo_name, size_t bytes) {
    double kb = bytes / 1024.0;
    double mb = kb / 1024.0;
    printf("%-15s Memory: %8.2f KB (%6.2f MB)\n", algo_name, kb, mb);
}

void run_sorting_for_int(int *data, int n) {
    int *copy = malloc(n * sizeof(int));
    clock_t start, end;

    printf("\n--- Sorting Data Angka (%d data) ---\n", n);

    memcpy(copy, data, n * sizeof(int));
    start = clock();
    bubble_sort_int(copy, n);
    end = clock();
    printf("Bubble Sort:    %.3f detik    ", (double)(end - start) / CLOCKS_PER_SEC);
    print_memory_usage("Bubble Sort", n * sizeof(int));

    memcpy(copy, data, n * sizeof(int));
    start = clock();
    selection_sort_int(copy, n);
    end = clock();
    printf("Selection Sort: %.3f detik    ", (double)(end - start) / CLOCKS_PER_SEC);
    print_memory_usage("Selection Sort", n * sizeof(int));

    memcpy(copy, data, n * sizeof(int));
    start = clock();
    insertion_sort_int(copy, n);
    end = clock();
    printf("Insertion Sort: %.3f detik    ", (double)(end - start) / CLOCKS_PER_SEC);
    print_memory_usage("Insertion Sort", n * sizeof(int));

    memcpy(copy, data, n * sizeof(int));
    start = clock();
    merge_sort_int(copy, 0, n - 1);
    end = clock();
    printf("Merge Sort:     %.3f detik    ", (double)(end - start) / CLOCKS_PER_SEC);
    print_memory_usage("Merge Sort", n * sizeof(int) * 3); // array + L + R

    memcpy(copy, data, n * sizeof(int));
    start = clock();
    quick_sort_int(copy, 0, n - 1);
    end = clock();
    printf("Quick Sort:     %.3f detik    ", (double)(end - start) / CLOCKS_PER_SEC);
    print_memory_usage("Quick Sort", n * sizeof(int)); // array + stack (kecil)

    memcpy(copy, data, n * sizeof(int));
    start = clock();
    shell_sort_int(copy, n);
    end = clock();
    printf("Shell Sort:     %.3f detik    ", (double)(end - start) / CLOCKS_PER_SEC);
    print_memory_usage("Shell Sort", n * sizeof(int));

    free(copy);
}

void run_sorting_for_str(char **data, int n) {
    char **copy = malloc(n * sizeof(char*));
    clock_t start, end;
    size_t avg_word_len = 8; // estimasi rata-rata panjang kata
    size_t total_str_mem = n * (sizeof(char*) + avg_word_len);

    printf("\n--- Sorting Data Kata (%d data) ---\n", n);

    for (int i = 0; i < n; i++) copy[i] = strdup(data[i]);
    start = clock();
    bubble_sort_str(copy, n);
    end = clock();
    printf("Bubble Sort:    %.3f detik    ", (double)(end - start) / CLOCKS_PER_SEC);
    print_memory_usage("Bubble Sort", total_str_mem);
    for (int i = 0; i < n; i++) free(copy[i]);

    for (int i = 0; i < n; i++) copy[i] = strdup(data[i]);
    start = clock();
    selection_sort_str(copy, n);
    end = clock();
    printf("Selection Sort: %.3f detik    ", (double)(end - start) / CLOCKS_PER_SEC);
    print_memory_usage("Selection Sort", total_str_mem);
    for (int i = 0; i < n; i++) free(copy[i]);

    for (int i = 0; i < n; i++) copy[i] = strdup(data[i]);
    start = clock();
    insertion_sort_str(copy, n);
    end = clock();
    printf("Insertion Sort: %.3f detik    ", (double)(end - start) / CLOCKS_PER_SEC);
    print_memory_usage("Insertion Sort", total_str_mem);
    for (int i = 0; i < n; i++) free(copy[i]);

    for (int i = 0; i < n; i++) copy[i] = strdup(data[i]);
    start = clock();
    merge_sort_str(copy, 0, n - 1);
    end = clock();
    printf("Merge Sort:     %.3f detik    ", (double)(end - start) / CLOCKS_PER_SEC);
    print_memory_usage("Merge Sort", total_str_mem * 2); // array + L + R
    for (int i = 0; i < n; i++) free(copy[i]);

    for (int i = 0; i < n; i++) copy[i] = strdup(data[i]);
    start = clock();
    quick_sort_str(copy, 0, n - 1);
    end = clock();
    printf("Quick Sort:     %.3f detik    ", (double)(end - start) / CLOCKS_PER_SEC);
    print_memory_usage("Quick Sort", total_str_mem);
    for (int i = 0; i < n; i++) free(copy[i]);

    for (int i = 0; i < n; i++) copy[i] = strdup(data[i]);
    start = clock();
    shell_sort_str(copy, n);
    end = clock();
    printf("Shell Sort:     %.3f detik    ", (double)(end - start) / CLOCKS_PER_SEC);
    print_memory_usage("Shell Sort", total_str_mem);
    for (int i = 0; i < n; i++) free(copy[i]);

    free(copy);
}

int main() {
    int data_type, data_option, data_count;

    print_menu();
    printf("Pilihan Anda: ");
    scanf("%d", &data_type);

    print_data_options();
    printf("Pilihan Anda: ");
    scanf("%d", &data_option);
    data_count = get_data_amount(data_option);

    if (data_count == -1) {
        printf("Pilihan jumlah data tidak valid.\n");
        return 1;
    }

    if (data_type == 1) {
        int *data = malloc(data_count * sizeof(int));
        if (read_numbers("data_angka.txt", data, data_count) < 0) {
            free(data);
            return 1;
        }
        run_sorting_for_int(data, data_count);
        free(data);
    } else if (data_type == 2) {
        char **data = malloc(data_count * sizeof(char*));
        if (read_words("data_kata.txt", data, data_count) < 0) {
            free(data);
            return 1;
        }
        run_sorting_for_str(data, data_count);
        for (int i = 0; i < data_count; i++) free(data[i]);
        free(data);
    } else {
        printf("Pilihan jenis data tidak valid.\n");
        return 1;
    }

    return 0;
}
