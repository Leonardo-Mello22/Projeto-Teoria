import time
import math
import random

# Tamanhos dos arrays
S_SMALL = 1000
S_MEDIUM = 50000
S_LARGE = 500000
NUM_RUNS = 30

# Dados simulados (substitua por seus dados reais se necessário)
arr_small_data = [random.randint(0, 100000) for _ in range(S_SMALL)]
arr_medium_data = [random.randint(0, 100000) for _ in range(S_MEDIUM)]
arr_large_data = [random.randint(0, 100000) for _ in range(S_LARGE)]

# Função para trocar dois elementos
def swap(arr, i, j):
    arr[i], arr[j] = arr[j], arr[i]

# Partição para Quick Sort
def partition(arr, low, high):
    pivot = arr[high]
    i = low - 1
    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1
            swap(arr, i, j)
    swap(arr, i + 1, high)
    return i + 1

# Quick Sort
def quick_sort(arr, low, high):
    if low < high:
        pi = partition(arr, low, high)
        quick_sort(arr, low, pi - 1)
        quick_sort(arr, pi + 1, high)

# Casos de teste
test_cases = [
    (arr_small_data, S_SMALL, "Dados_Pequenos_Arquivo"),
    (arr_medium_data, S_MEDIUM, "Dados_Medios_Arquivo"),
    (arr_large_data, S_LARGE, "Dados_Grandes_Arquivo")
]

# Cabeçalho
print("--- Testes de Quick Sort em Python ---")
print("{:<25} | {:<7} | {:<16} | {:<17}".format("Cenário", "Tamanho", "Média Tempo (ms)", "Desvio Padrão (ms)"))
print("-" * 75)

# Loop principal
for data_source, size, type_name in test_cases:
    times = []

    for _ in range(NUM_RUNS):
        temp_arr = data_source.copy()

        start = time.perf_counter()
        quick_sort(temp_arr, 0, size - 1)
        end = time.perf_counter()

        elapsed_ms = (end - start) * 1000
        times.append(elapsed_ms)

    # Cálculo da média
    avg_time = sum(times) / NUM_RUNS

    # Cálculo do desvio padrão
    sum_squared_diff = sum((t - avg_time) ** 2 for t in times)
    std_dev = math.sqrt(sum_squared_diff / (NUM_RUNS - 1)) if NUM_RUNS > 1 else 0.0

    print("{:<25} | {:<7} | {:16.4f} | {:17.4f}".format(type_name, size, avg_time, std_dev))
