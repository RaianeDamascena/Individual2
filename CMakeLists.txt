# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico_w CACHE STRING "Board type")

include(pico_sdk_import.cmake)
project(Individual2 C CXX ASM)
pico_sdk_init()

# Adiciona o arquivo principal do projeto que está na pasta Individual2
add_executable(Individual2 main.c)

# Define o nome do programa
pico_set_program_name(Individual2 "Individual2")

# Linka a biblioteca padrão do SDK do Pico
target_link_libraries(Individual2 pico_stdlib)

# Gera saídas extras (UF2, binário, etc.)
pico_add_extra_outputs(Individual2)
