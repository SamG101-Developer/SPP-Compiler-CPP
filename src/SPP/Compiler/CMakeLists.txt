add_library(SPP_Compiler STATIC)

target_sources(SPP_Compiler PUBLIC FILE_SET CXX_MODULES
        BASE_DIRS ${CMAKE_SOURCE_DIR}/include/SPP/Compiler FILES
        ${CMAKE_SOURCE_DIR}/include/SPP/Compiler/Compiler.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/Compiler/CompilerModuleTree.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/Compiler/CompilerStages.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/Compiler/Program.ixx)

target_sources(SPP_Compiler PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Compiler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CompilerModuleTree.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CompilerStages.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Program.cpp)

target_include_directories(SPP_Compiler PRIVATE
        ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(SPP_Compiler PRIVATE
        SPP::Utils)

add_library(SPP::Compiler ALIAS SPP_Compiler)
