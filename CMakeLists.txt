cmake_minimum_required(VERSION 3.29)
project(Ponderada_openmp)

# Definir a versão padrão do C++
set(CMAKE_CXX_STANDARD 20)

# Encontrar e ativar o OpenMP
find_package(OpenMP REQUIRED)

# Adicionar o executável
add_executable(Ponderada_openmp main.cpp)

# Linkar a biblioteca OpenMP ao projeto
if(OpenMP_CXX_FOUND)
    target_link_libraries(Ponderada_openmp PRIVATE OpenMP::OpenMP_CXX)
else()
    message(FATAL_ERROR "OpenMP não encontrado!")
endif()
