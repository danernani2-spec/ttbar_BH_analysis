cmake_minimum_required(VERSION 3.10)
project(ttbar_BH_analysis)

# Configuração do C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

# Encontrar ROOT
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIRS})

# Adicionar executável
add_executable(top_inclusive_withBH_overlay 
    source/top_inclusive_withBH_overlay.cpp)

# Linkar com ROOT
target_link_libraries(top_inclusive_withBH_overlay ${ROOT_LIBRARIES})

# Definir o diretório de saída
set_target_properties(top_inclusive_withBH_overlay 
    PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/source")
