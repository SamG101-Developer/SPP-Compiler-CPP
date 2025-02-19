add_library(SPP_Utils STATIC)

target_sources(SPP_Utils PUBLIC FILE_SET CXX_MODULES
        BASE_DIRS ${CMAKE_SOURCE_DIR}/include/SPP/Utils FILES
        ${CMAKE_SOURCE_DIR}/include/SPP/Utils/Converter.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/Utils/ErrorFormatter.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/Utils/PrettyPrinter.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/Utils/VariantIntrinsics.ixx)

target_sources(SPP_Utils PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/ErrorFormatter.cpp)

target_include_directories(SPP_Utils PRIVATE
        ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(SPP_Utils PRIVATE
        SPP::LexicalAnalysis
        GenEx::GenEx)

add_library(SPP::Utils ALIAS SPP_Utils)
