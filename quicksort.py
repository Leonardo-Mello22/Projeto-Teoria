import time
import math
import random
import sys

# Tamanhos dos arrays
S_XSMALL = 100
S_SMALL = 500
S_MSMALL = 1000
S_MEDIUM = 5000
S_MLARGE = 10000
S_LARGE = 50000
S_XLARGE = 100000
NUM_RUNS = 15


new_recursion_limit = S_XLARGE + 10000 # e.g., 1,010,000
sys.setrecursionlimit(new_recursion_limit)

# Gerador de dados aleatórios
def gerar_dados(tamanho):
    return [random.randint(0, 100000) for _ in range(tamanho)]

# Gerador de dados pior caso(já ordenado)
def gerar_dados_pior(tamanho):
    arr = [0] * tamanho
    for i in range(tamanho):
        arr[i] = i
    return arr

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

# Casos de teste com mais granularidade
test_cases = [
    (gerar_dados(S_XSMALL), S_XSMALL, "Muito_Pequeno"),
    (gerar_dados(S_SMALL), S_SMALL, "Pequeno"),
    (gerar_dados(S_MSMALL), S_MSMALL, "Medio_Pequeno"),
    (gerar_dados(S_MEDIUM), S_MEDIUM, "Medio"),
    (gerar_dados(S_MLARGE), S_MLARGE, "Medio_Grande"),
    (gerar_dados(S_LARGE), S_LARGE, "Grande"),
    (gerar_dados(S_XLARGE), S_XLARGE, "Muito_Grande")
]

# Cabeçalho
print("--- Testes de Quick Sort em Python (O(n log n)) ---")
print("{:<20} | {:<10} | {:<16} | {:<17}".format("Cenário", "Tamanho", "Média Tempo (ms)", "Desvio Padrão (ms)"))
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

    # Média
    avg_time = sum(times) / NUM_RUNS

    # Desvio padrão
    sum_squared_diff = sum((t - avg_time) ** 2 for t in times)
    std_dev = math.sqrt(sum_squared_diff / (NUM_RUNS - 1)) if NUM_RUNS > 1 else 0.0

    print("{:<20} | {:<10} | {:16.4f} | {:17.4f}".format(type_name, size, avg_time, std_dev))


# Casos de teste com mais granularidade
test_cases = [
    (gerar_dados_pior(S_XSMALL), S_XSMALL, "Muito_Pequeno"),
    (gerar_dados_pior(S_SMALL), S_SMALL, "Pequeno"),
    (gerar_dados_pior(S_MSMALL), S_MSMALL, "Medio_Pequeno"),
    (gerar_dados_pior(S_MEDIUM), S_MEDIUM, "Medio"),
    (gerar_dados_pior(S_MLARGE), S_MLARGE, "Medio_Grande"),
    (gerar_dados_pior(S_LARGE), S_LARGE, "Grande"),
    (gerar_dados_pior(S_XLARGE), S_XLARGE, "Muito_Grande")
]

print("--- Testes de Quick Sort em Python (O(n^2)) ---")
print("{:<20} | {:<10} | {:<16} | {:<17}".format("Cenário", "Tamanho", "Média Tempo (ms)", "Desvio Padrão (ms)"))
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

    # Média
    avg_time = sum(times) / NUM_RUNS

    # Desvio padrão
    sum_squared_diff = sum((t - avg_time) ** 2 for t in times)
    std_dev = math.sqrt(sum_squared_diff / (NUM_RUNS - 1)) if NUM_RUNS > 1 else 0.0

    print("{:<20} | {:<10} | {:16.4f} | {:17.4f}".format(type_name, size, avg_time, std_dev))
