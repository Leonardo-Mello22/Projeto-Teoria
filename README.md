# Projeto-Teoria,

## Dados Utilizados nos Gráficos de Desempenho — Quick Sort (C vs Python)

### Quick Sort em C (Caso Médio - O(n log n))
| Cenário        | Tamanho | Média Tempo (ms) | Desvio Padrão (ms) |
| -------------- | ------- | ---------------- | ------------------ |
| Muito\_Pequeno | 100     | 0.0000           | 0.0000             |
| Pequeno        | 500     | 0.0000           | 0.0000             |
| Medio\_Pequeno | 1000    | 0.8000           | 2.3361             |
| Medio          | 5000    | 2.0667           | 2.9633             |
| Medio\_Grande  | 10000   | 5.6000           | 6.8013             |
| Grande         | 50000   | 20.7333          | 5.7504             |
| Muito\_Grande  | 100000  | 32.4000          | 6.3336             |

### Quick Sort em C (Pior Caso - O(n²))
| Cenário        | Tamanho | Média Tempo (ms) | Desvio Padrão (ms) |
| -------------- | ------- | ---------------- | ------------------ |
| Muito\_Pequeno | 100     | 0.1333           | 0.3519             |
| Pequeno        | 500     | 1.1333           | 2.2636             |
| Medio\_Pequeno | 1000    | 6.5333           | 2.0656             |
| Medio          | 5000    | 120.2667         | 16.5074            |
| Medio\_Grande  | 10000   | 454.4000         | 87.7430            |
| Grande         | 50000   | 11091.0667       | 2628.5530          |
| Muito\_Grande  | 100000  | 113246.6667      | 56160.0324         |

### Quick Sort em Python (Caso Médio - O(n log n))
| Cenário        | Tamanho | Média Tempo (ms) | Desvio Padrão (ms) |
| -------------- | ------- | ---------------- | ------------------ |
| Muito\_Pequeno | 100     | 0.4940           | 0.0236             |
| Pequeno        | 500     | 3.8338           | 0.7717             |
| Medio\_Pequeno | 1000    | 8.0444           | 1.8611             |
| Medio          | 5000    | 44.3834          | 5.4152             |
| Medio\_Grande  | 10000   | 105.6609         | 9.0916             |
| Grande         | 50000   | 629.8151         | 38.4671            |
| Muito\_Grande  | 100000  | 1263.4240        | 39.7341            |

### Quick Sort em Python (Pior Caso - O(n²))
| Cenário        | Tamanho | Média Tempo (ms) | Desvio Padrão (ms) |
| -------------- | ------- | ---------------- | ------------------ |
| Muito\_Pequeno | 100     | 0.8058           | 0.2766             |
| Pequeno        | 500     | 21.0384          | 1.6001             |
| Medio\_Pequeno | 1000    | 82.1778          | 3.7896             |
| Medio          | 5000    | 2296.1964        | 246.9325           |
| Medio\_Grande  | 10000   | 9211.3704        | 517.0758           |
| Grande         | 50000   | 262583.9901      | 15222.5014         |
| Muito\_Grande  | 100000  | 1002583.9901     | 151222.5014        |

