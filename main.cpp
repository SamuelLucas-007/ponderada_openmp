#include <iostream>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <chrono>
#include <omp.h>

// Função para gerar um vetor aleatório
std::vector<int> generate_random_vector(int size) {
    std::vector<int> vec(size);
    for (int &val : vec) {
        val = rand() % 100 + 1;
    }
    return vec;
}

// Soma serial
long long serial_sum(const std::vector<int>& vec) {
    return std::accumulate(vec.begin(), vec.end(), 0LL);
}

// Soma paralela otimizada
long long parallel_sum(const std::vector<int>& vec, int num_threads) {
    long long total_sum = 0;
    #pragma omp parallel num_threads(num_threads)
    {
        long long local_sum = 0; // Soma local para cada thread
        #pragma omp for schedule(static)
        for (size_t i = 0; i < vec.size(); ++i) {
            local_sum += vec[i];
        }
        #pragma omp critical
        total_sum += local_sum; // Redução manual para evitar conflitos
    }
    return total_sum;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int vector_size = 777777777; // Reduza para testes em hardware limitado
    std::vector<int> vec = generate_random_vector(vector_size);

    // Tempo da soma serial
    auto start = std::chrono::high_resolution_clock::now();
    long long serialResult = serial_sum(vec);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> serial_time = end - start;
    std::cout << "Soma serial: " << serialResult << " | Tempo: " << serial_time.count() << " segundos\n";

    // Descubra o número de núcleos disponíveis
    int max_threads = omp_get_max_threads();
    std::cout << "Maximo de threads disponiveis: " << max_threads << "\n";

    // Soma paralela com diferentes números de threads
    for (int threads = 2; threads <= max_threads; threads *= 2) {
        start = std::chrono::high_resolution_clock::now();
        long long parallelResult = parallel_sum(vec, threads);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> parallel_time = end - start;
        std::cout << "Soma com " << threads << " threads: " << parallelResult
                  << " | Tempo: " << parallel_time.count() << " segundos\n";
    }

    return 0;
}
