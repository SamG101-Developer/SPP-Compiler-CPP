add_library(SPP_SemanticAnalysis_Asts STATIC)

target_sources(SPP_SemanticAnalysis_Asts PUBLIC FILE_SET CXX_MODULES
        BASE_DIRS ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts FILES
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/_ast_members.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/_ast_types.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/AnnotationAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/AssignmentStatementAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/Ast.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/CaseExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/CaseExpressionBranchAst.ixx
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
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericCompParameterOptionalAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericCompParameterRequiredAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericCompParameterVariadicAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericTypeArgumentNamedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericTypeArgumentUnnamedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericTypeParameterInlineConstraintsAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericTypeParameterOptionalAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericTypeParameterRequiredAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericTypeParameterVariadicAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericIdentifierAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenericParameterGroupAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GenExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/GlobalConstantAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/IdentifierAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/InnerScopeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LetStatementInitializedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LetStatementUninitializedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LocalVariableAttributeBindingAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LocalVariableDestructureArrayAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LocalVariableDestructureObjectAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LocalVariableDestructureSkip1ArgumentAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LocalVariableDestructureSkipNArgumentsAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LocalVariableDestructureTupleAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LocalVariableSingleIdentifierAliasAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LocalVariableSingleIdentifierAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LoopConditionBooleanAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LoopConditionIterableAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LoopElseStatementAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/LoopExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ModuleImplementationAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ModulePrototypeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ObjectInitializerAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ObjectInitializerArgumentGroupAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ObjectInitializerArgumentNamedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ObjectInitializerArgumentUnnamedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/ParenthesizedExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantAttributeBindingAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantDestructureArrayAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantDestructureObjectAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantDestructureSkip1ArgumentAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantDestructureSkipNArgumentsAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantDestructureTupleAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantElseAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantElseCaseAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantExpressionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantLiteralAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PatternVariantSingleIdentifierAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PostfixExpressionOperatorEarlyReturnAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PostfixExpressionOperatorFunctionCallAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PostfixExpressionOperatorMemberAccessAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PostfixExpressionOperatorNotKeywordAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PostfixExpressionOperatorStepKeywordAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/PinStatementAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/RelStatementAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/RetStatementAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/RootAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/SubroutinePrototypeAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/SupImplementationAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/SupPrototypeExtensionAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/SupPrototypeFunctionsAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/TokenAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/TypeParenthesizedAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/TypeSingleAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/UnaryExpressionOperatorAsyncAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/UseStatementAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/WhereBlockAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/WhereConstraintsAst.ixx
        ${CMAKE_SOURCE_DIR}/include/SPP/SemanticAnalysis/Asts/WhereConstraintsGroupAst.ixx)

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
