cmake_minimum_required(VERSION 3.10)
project(MyCppApp)

# Definir padrão C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Adicionar diretório de código-fonte
add_executable(app main.cpp)