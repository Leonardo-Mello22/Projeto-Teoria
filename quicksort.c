#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define NUM_RUNS 15

// Novos tamanhos mais granulares
#define S_XSMALL   100
#define S_SMALL    500
#define S_MSMALL   1000
#define S_MEDIUM   5000
#define S_MLARGE   10000
#define S_LARGE    50000
#define S_XLARGE   100000

// Estrutura para os casos de teste
typedef struct {
    int size;
    const char* type_name;
} TestCase;

// Gerador de dados aleatórios (caso médio)
int* gerar_dados(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) {
        perror("Erro ao alocar memória para gerar dados (caso médio)");
        exit(EXIT_FAILURE); // Usar EXIT_FAILURE para erros padronizados
    }
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100000; // Gera números aleatórios
    }
    return arr;
}

// Gerador de dados para o pior caso (já ordenado)
int* gerar_dados_pior_caso(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) {
        perror("Erro ao alocar memória para gerar dados (pior caso)");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        arr[i] = i; // Gera um array ordenado: 0, 1, 2, ..., size-1
    }
    return arr;
}

// Função para trocar dois elementos
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Função de partição para o Quick Sort (pivô como último elemento)
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Escolhe o último elemento como pivô
    int i = low - 1;       // Índice do menor elemento

    for (int j = low; j <= high - 1; j++) {
        // Se o elemento atual é menor ou igual ao pivô
        if (arr[j] <= pivot) {
            i++; // Incrementa o índice do menor elemento
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]); // Coloca o pivô na posição correta
    return i + 1; // Retorna o índice de partição
}

// Função principal do Quick Sort (Otimizada para profundidade de recursão O(log n))
void quickSort(int arr[], int low, int high) {
    while (low < high) {
        int pi = partition(arr, low, high);
        if ((pi - low) < (high - pi)) {
            quickSort(arr, low, pi - 1);
            low = pi + 1;         
        } else {
            quickSort(arr, pi + 1, high); 
            high = pi - 1;              
        }
    }
}

int main() {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Define os casos de teste
    TestCase test_cases[] = {
        {S_XSMALL, "Muito_Pequeno"},
        {S_SMALL,  "Pequeno"},
        {S_MSMALL, "Medio_Pequeno"},
        {S_MEDIUM, "Medio"},
        {S_MLARGE, "Medio_Grande"},
        {S_LARGE,  "Grande"},
        {S_XLARGE, "Muito_Grande"}
    };
    int num_test_cases = sizeof(test_cases) / sizeof(TestCase);

    // --- Testes de Quick Sort em C (Caso Médio O(n log n)) ---
    printf("--- Testes de Quick Sort em C (Caso Medio O(n log n)) ---\n");
    printf("%-20s | %-10s | %-16s | %-17s\n", "Cenario", "Tamanho", "Media Tempo (ms)", "Desvio Padrao (ms)");
    printf("----------------------|------------|------------------|-------------------\n");

    for (int i = 0; i < num_test_cases; i++) {
        int size = test_cases[i].size;
        const char* name = test_cases[i].type_name;
        double tempos[NUM_RUNS]; // Array para armazenar os tempos de cada execução

        // Gera os dados base uma vez para este tamanho
        int* base_data_medio = gerar_dados(size);
        if (base_data_medio == NULL) continue; // Se falhou, pula para o próximo caso

        for (int r = 0; r < NUM_RUNS; r++) {
            // Aloca e copia os dados para não modificar o array original em cada run
            int* temp_arr = (int*)malloc(size * sizeof(int));
            if (temp_arr == NULL) {
                perror("Erro ao alocar memória para temp_arr (caso médio)");
                free(base_data_medio);
                if (i < num_test_cases -1) { 
                    fprintf(stderr, "Pulando para o proximo caso de teste devido a falha de alocacao.\n");
                    goto next_test_case_medio; 
                } else {
                    return 1; // Encerra se for o último e falhar
                }
            }
            memcpy(temp_arr, base_data_medio, size * sizeof(int));

            clock_t start_time = clock(); 
            quickSort(temp_arr, 0, size - 1); 
            clock_t end_time = clock();  

            // Calcula o tempo decorrido em milissegundos
            tempos[r] = ((double)(end_time - start_time)) * 1000.0 / CLOCKS_PER_SEC;

            free(temp_arr); 
        }
        
        next_test_case_medio:
        free(base_data_medio); 

        // Calcula a média dos tempos
        double soma_tempos = 0.0;
        for (int j = 0; j < NUM_RUNS; j++) {
            soma_tempos += tempos[j];
        }
        double media_tempo = soma_tempos / NUM_RUNS;

        // Calcula o desvio padrão
        double soma_diferencas_quadradas = 0.0;
        for (int j = 0; j < NUM_RUNS; j++) {
            double diferenca = tempos[j] - media_tempo;
            soma_diferencas_quadradas += diferenca * diferenca;
        }
        double desvio_padrao = 0.0;
        if (NUM_RUNS > 1) {
            desvio_padrao = sqrt(soma_diferencas_quadradas / (NUM_RUNS - 1));
        }

        printf("%-20s | %-10d | %16.4f | %17.4f\n", name, size, media_tempo, desvio_padrao);
    }

    // --- Testes de Quick Sort em C (Pior Caso O(n^2)) ---
    printf("\n\n--- Testes de Quick Sort em C (Pior Caso O(n^2)) ---\n");
    printf("%-20s | %-10s | %-16s | %-17s\n", "Cenario", "Tamanho", "Media Tempo (ms)", "Desvio Padrao (ms)");
    printf("----------------------|------------|------------------|-------------------\n");

    for (int i = 0; i < num_test_cases; i++) {
        int size = test_cases[i].size;
        const char* name = test_cases[i].type_name;
        double tempos[NUM_RUNS];

        // Gera os dados base para o pior caso
        int* base_data_pior = gerar_dados_pior_caso(size);
        if (base_data_pior == NULL) continue;

        for (int r = 0; r < NUM_RUNS; r++) {
            int* temp_arr = (int*)malloc(size * sizeof(int));
             if (temp_arr == NULL) {
                perror("Erro ao alocar memória para temp_arr (pior caso)");
                free(base_data_pior);
                if (i < num_test_cases -1) {
                    fprintf(stderr, "Pulando para o proximo caso de teste devido a falha de alocacao.\n");
                    goto next_test_case_pior;
                } else {
                    return 1;
                }
            }
            memcpy(temp_arr, base_data_pior, size * sizeof(int));

            clock_t start_time = clock();
            quickSort(temp_arr, 0, size - 1);
            clock_t end_time = clock();

            tempos[r] = ((double)(end_time - start_time)) * 1000.0 / CLOCKS_PER_SEC;
            
            free(temp_arr);
        }
        
        next_test_case_pior:
        free(base_data_pior);

        double soma_tempos = 0.0;
        for (int j = 0; j < NUM_RUNS; j++) {
            soma_tempos += tempos[j];
        }
        double media_tempo = soma_tempos / NUM_RUNS;

        double soma_diferencas_quadradas = 0.0;
        for (int j = 0; j < NUM_RUNS; j++) {
            double diferenca = tempos[j] - media_tempo;
            soma_diferencas_quadradas += diferenca * diferenca;
        }
        double desvio_padrao = 0.0;
        if (NUM_RUNS > 1) {
            desvio_padrao = sqrt(soma_diferencas_quadradas / (NUM_RUNS - 1));
        }
        
        printf("%-20s | %-10d | %16.4f | %17.4f\n", name, size, media_tempo, desvio_padrao);
    }

    return 0;
}
