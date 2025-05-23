#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define S_SMALL 1000
#define S_MEDIUM 50000
#define S_LARGE 500000
#define NUM_RUNS 30

int* gerar_dados(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) {
        perror("Erro ao alocar memória para gerar dados");
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100000;
    }
    return arr;
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    srand(time(NULL));

    typedef struct {
        int size;
        const char* type_name;
    } TestCase;

    TestCase test_cases[] = {
        {S_SMALL, "Dados_Pequenos"},
        {S_MEDIUM, "Dados_Medios"},
        {S_LARGE, "Dados_Grandes"}
    };
    int num_test_cases = sizeof(test_cases) / sizeof(TestCase);

    printf("--- Testes de Quick Sort em C ---\n");
    printf("%-20s | %-7s | %-16s | %-17s\n", "Cenario", "Tamanho", "Media Tempo (ms)", "Desvio Padrao (ms)");
    printf("---------------------|---------|------------------|-------------------\n");

    for (int i = 0; i < num_test_cases; i++) {
        int size = test_cases[i].size;
        const char* name = test_cases[i].type_name;
        double tempos[NUM_RUNS];

        int* base_data = gerar_dados(size);

        for (int r = 0; r < NUM_RUNS; r++) {
            int* temp = (int*)malloc(size * sizeof(int));
            if (temp == NULL) {
                perror("Erro ao alocar memória para temp");
                return 1;
            }
            memcpy(temp, base_data, size * sizeof(int));

            clock_t start = clock();
            quickSort(temp, 0, size - 1);
            clock_t end = clock();

            tempos[r] = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;

            free(temp);
        }

        free(base_data);

        double soma = 0.0;
        for (int j = 0; j < NUM_RUNS; j++) soma += tempos[j];
        double media = soma / NUM_RUNS;

        double soma_quadrados = 0.0;
        for (int j = 0; j < NUM_RUNS; j++) {
            double diff = tempos[j] - media;
            soma_quadrados += diff * diff;
        }
        double desvio = sqrt(soma_quadrados / (NUM_RUNS - 1));

        printf("%-20s | %-7d | %16.4f | %17.4f\n", name, size, media, desvio);
    }

    return 0;
}
