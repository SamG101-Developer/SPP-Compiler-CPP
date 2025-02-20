add_library(SPP_SemanticAnalysis_Asts STATIC)

target_sources(SPP_SemanticAnalysis_Asts PUBLIC FILE_SET CXX_MODULES
        BASE_DIRS ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts FILES
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/_ast_members.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/_ast_types.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/AnnotationAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/Ast.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/CaseExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ClassAttributeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ClassImplementationAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ClassPrototypeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ConventionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/CoroutinePrototypeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionCallArgumentGroupAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionCallArgumentUnnamedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionCallArgumentNamedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionImplementationAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionParameterGroupAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionParameterOptionalAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionParameterRequiredAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionParameterSelfAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionParameterVariadicAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/FunctionPrototypeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericArgumentGroupAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericCompArgumentNamedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericCompArgumentUnnamedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericTypeArgumentNamedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericTypeArgumentUnnamedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericIdentifierAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericParameterGroupAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/IdentifierAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LoopExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ModuleImplementationAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ModulePrototypeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ParenthesizedExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/RootAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/SubroutinePrototypeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/SupImplementationAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/SupPrototypeExtensionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/SupPrototypeFunctionsAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/TokenAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/TypeSingleAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/WhereBlockAst.ixx)

target_sources(SPP_SemanticAnalysis_Asts PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Ast.cpp
        ${CMAKE_CURRENT_LIST_DIR}/RootAst.cpp)

target_include_directories(SPP_SemanticAnalysis_Asts PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts)

target_link_libraries(SPP_SemanticAnalysis_Asts PRIVATE
        magic_enum::magic_enum
        SPP::Compiler
        SPP::SemanticAnalysis::Meta
        SPP::SemanticAnalysis::Mixins
        SPP::SyntacticAnalysis)

add_library(SPP::SemanticAnalysis::Asts ALIAS SPP_SemanticAnalysis_Asts)
