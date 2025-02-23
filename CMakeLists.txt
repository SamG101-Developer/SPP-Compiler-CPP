cmake_minimum_required(VERSION 3.31)

project(SPP_Compiler_CPP)

#set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD 0e5b6991-d74f-4b3d-a41c-cf096e0b2508)
#set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_STANDARD ${CMAKE_CXX_STANDARD_LATEST})
include(FetchContent)

find_package(magic_enum REQUIRED)
find_package(RE2 REQUIRED)
find_package(Boost REQUIRED)

add_subdirectory(src/SPP)
add_executable(${PROJECT_NAME} main.cpp)
#target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} PRIVATE SPP::Modules)

#add_library(CXX_MODULE_SUPPORT INTERFACE)
#target_compile_features(CXX_MODULE_SUPPORT INTERFACE cxx_std_23)
#add_library(__CMAKE::CXX23 ALIAS CXX_MODULE_SUPPORT)
#target_link_libraries(${PROJECT_NAME} PRIVATE CXX_MODULE_SUPPORT)

#target_sources(CXX_MODULE_SUPPORT PUBLIC FILE_SET CXX_MODULES
#        BASE_DIRS "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.42.34433/modules" FILES
#        "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.42.34433/modules/std.ixx")
