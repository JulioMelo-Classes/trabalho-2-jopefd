cmake_minimum_required(VERSION 3.5)
project(concordo VERSION 0.1 LANGUAGES CXX )


### Executável
# Diretório contendo os .hpp
include_directories(include)

# Cria um executável com nome "concordo", adiciona neste executável os arquivos
# src/concordo.cpp src/sistema.cpp src/executor.cpp
add_executable(concordo
               src/canal_texto.cpp
               src/concordo.cpp
               src/executor.cpp
               src/mensagem.cpp
               src/servidor.cpp
               src/sistema.cpp 
               src/usuario.cpp)

# The end
