module;
#include <variant>
#include <memory>
#include <string>
#include <vector>
#include <optional>

#define OR ,

#define PARSER_RESULT_TYPE(T) std::unique_ptr<T>

#define PARSER_RESULT_TYPE_VARIANT(T) UniqueVariant<T>

#define CREATE_PARSER_RULE(what, type)\
    private:\
        auto parse_##what() -> PARSER_RESULT_TYPE(type);


#define CREATE_PARSER_RULE_VARIANT(what, type)\
    private:\
        auto parse_##what() -> PARSER_RESULT_TYPE_VARIANT(type);


export module spp.syntactic_analysis.parser;
import spp.lexical_analysis.tokens;
import spp.semantic_analysis.asts.ast_types;
import spp.syntactic_analysis.parser_error;
import spp.utils.error_formatter;
import spp.utils.variant_intrinsics;


namespace SPP::SyntacticAnalysis {
    export class Parser;
}

using namespace SPP::SemanticAnalysis;


class SPP::SyntacticAnalysis::Parser {
    std::size_t pos = 0;
    std::size_t token_stream_size;
    std::string name;
    std::vector<LexicalAnalysis::RawToken> token_stream;
    ErrorFormatter error_formatter;
    std::optional<Errors::SyntaxError> error = std::nullopt;

    auto store_error(std::size_t pos, std::string error) -> bool;

public:
    explicit Parser(std::vector<LexicalAnalysis::RawToken> token_stream, std::string file_name = "", std::optional<ErrorFormatter> error_formatter = std::nullopt);
    auto get_current_token() const -> LexicalAnalysis::RawToken;
    auto get_current_pos() const -> std::size_t;
    auto set_current_pos(std::size_t new_index) -> void;

private:
    template <typename ...Args, std::invocable<Parser*, Args...> F> auto parse_once(F&& parser_rule, Args&&... args) -> std::invoke_result_t<F, Parser*, Args...>;
    template <typename ...Args, std::invocable<Parser*, Args...> F> auto parse_optional(F&& parser_rule, Args&&... args) -> std::optional<std::invoke_result_t<F, Parser*, Args...>>;

    template <std::invocable<Parser*> F, std::invocable<Parser*> S> auto parse_0_or_more(F&& parser_rule, S&& separator) -> std::vector<std::invoke_result_t<F, Parser*>>;
    template <std::invocable<Parser*> F, std::invocable<Parser*> S> auto parse_1_or_more(F&& parser_rule, S&& separator) -> std::vector<std::invoke_result_t<F, Parser*>>;
    template <std::invocable<Parser*> F, std::invocable<Parser*> S> auto parse_2_or_more(F&& parser_rule, S&& separator) -> std::vector<std::invoke_result_t<F, Parser*>>;

    template <std::invocable<Parser*>... Fs> auto parse_alternate(Fs&&... parser_rules) -> CollapsingVariant<std::invoke_result_t<Fs, Parser*>...>;

public:
    auto parse() -> Asts::RootAst;

    CREATE_PARSER_RULE(root, Asts::ModulePrototypeAst)
    CREATE_PARSER_RULE(eof, Asts::TokenAst)

    CREATE_PARSER_RULE(module_prototype, Asts::ModulePrototypeAst)
    CREATE_PARSER_RULE(module_implementation, Asts::ModuleImplementationAst)
    CREATE_PARSER_RULE_VARIANT(module_member, Asts::ModuleMemberAst)

    CREATE_PARSER_RULE(class_prototype, Asts::ClassPrototypeAst)
    CREATE_PARSER_RULE(class_implementation, Asts::ClassImplementationAst)
    CREATE_PARSER_RULE_VARIANT(class_member, Asts::ClassMemberAst)
    CREATE_PARSER_RULE(class_attribute, Asts::ClassAttributeAst)

    CREATE_PARSER_RULE(sup_prototype_functions, Asts::SupPrototypeFunctionsAst);
    CREATE_PARSER_RULE(sup_prototype_extension, Asts::SupPrototypeExtensionAst);
    CREATE_PARSER_RULE(sup_implementation, Asts::SupImplementationAst);
    CREATE_PARSER_RULE_VARIANT(sup_member, Asts::SupMemberAst);
    CREATE_PARSER_RULE(sup_subroutine_prototype, Asts::SubroutinePrototypeAst);
    CREATE_PARSER_RULE(sup_coroutine_prototype, Asts::CoroutinePrototypeAst);
    CREATE_PARSER_RULE(sup_use_statement, Asts::SupUseStatementAst);

    CREATE_PARSER_RULE(subroutine_prototype, Asts::SubroutinePrototypeAst);
    CREATE_PARSER_RULE(coroutine_prototype, Asts::CoroutinePrototypeAst);
    CREATE_PARSER_RULE(function_implementation, Asts::FunctionImplementationAst);
    CREATE_PARSER_RULE_VARIANT(function_member, Asts::FunctionMemberAst);

    CREATE_PARSER_RULE(function_call_arguments, Asts::FunctionCallArgumentGroupAst);
    CREATE_PARSER_RULE_VARIANT(function_call_argument, Asts::FunctionCallArgumentAst);
    CREATE_PARSER_RULE(function_call_argument_unnamed, Asts::FunctionCallArgumentUnnamedAst);
    CREATE_PARSER_RULE(function_call_argument_named, Asts::FunctionCallArgumentNamedAst);

    CREATE_PARSER_RULE(function_parameters, Asts::FunctionParameterGroupAst);
    CREATE_PARSER_RULE_VARIANT(function_parameter, Asts::FunctionParameterAst);
    CREATE_PARSER_RULE(function_parameter_self, Asts::FunctionParameterSelfAst);
    CREATE_PARSER_RULE(function_parameter_required, Asts::FunctionParameterRequiredAst);
    CREATE_PARSER_RULE(function_parameter_optional, Asts::FunctionParameterOptionalAst);
    CREATE_PARSER_RULE(function_parameter_variadic, Asts::FunctionParameterVariadicAst);

    CREATE_PARSER_RULE(generic_arguments, Asts::GenericArgumentGroupAst);
    CREATE_PARSER_RULE_VARIANT(generic_argument, Asts::GenericArgumentAst);
    CREATE_PARSER_RULE(generic_argument_type_named, Asts::GenericArgumentTypeNamedAst);
    CREATE_PARSER_RULE(generic_argument_type_unnamed, Asts::GenericArgumentTypeUnnamedAst);
    CREATE_PARSER_RULE(generic_argument_comp_named, Asts::GenericArgumentCompNamedAst);
    CREATE_PARSER_RULE(generic_argument_comp_unnamed, Asts::GenericArgumentCompUnnamedAst);

    CREATE_PARSER_RULE(generic_parameters, Asts::GenericParameterGroupAst);
    CREATE_PARSER_RULE_VARIANT(generic_parameter, Asts::GenericParameterAst);
    CREATE_PARSER_RULE(generic_parameter_type_required, Asts::GenericParameterTypeRequiredAst);
    CREATE_PARSER_RULE(generic_parameter_type_optional, Asts::GenericParameterTypeOptionalAst);
    CREATE_PARSER_RULE(generic_parameter_type_variadic, Asts::GenericParameterTypeVariadicAst);
    CREATE_PARSER_RULE(generic_parameter_comp_required, Asts::GenericParameterCompRequiredAst);
    CREATE_PARSER_RULE(generic_parameter_comp_optional, Asts::GenericParameterCompOptionalAst);
    CREATE_PARSER_RULE(generic_parameter_comp_variadic, Asts::GenericParameterCompVariadicAst);
    CREATE_PARSER_RULE(generic_inline_constraints, Asts::GenericTypeParameterInlineConstraintsAst);

    CREATE_PARSER_RULE(where_block, Asts::WhereBlockAst);
    CREATE_PARSER_RULE(where_block_constraints_group, Asts::WhereConstraintsGroupAst);
    CREATE_PARSER_RULE(where_block_constraints, Asts::WhereConstraintsAst);

    CREATE_PARSER_RULE(annotation, Asts::AnnotationAst);

    CREATE_PARSER_RULE_VARIANT(expression, Asts::ExpressionAst);
    template <std::invocable<Parser*> A1, std::invocable<Parser*> A2>
    auto parse_binary_expression_precedence_level_n_rhs(A1&& op, A2&& rhs) -> std::pair<PARSER_RESULT_TYPE(Asts::TokenAst), PARSER_RESULT_TYPE_VARIANT(Asts::ExpressionAst)>;
    template <std::invocable<Parser*> A1, std::invocable<Parser*> A2, std::invocable<Parser*> A3>
    auto parse_binary_expression_precedence_level_n(A1&& lhs, A2&& op, A3&& rhs) -> PARSER_RESULT_TYPE_VARIANT(Asts::ExpressionAst);

    CREATE_PARSER_RULE_VARIANT(binary_expression_precedence_level_1, Asts::ExpressionAst);
    CREATE_PARSER_RULE_VARIANT(binary_expression_precedence_level_2, Asts::ExpressionAst);
    CREATE_PARSER_RULE_VARIANT(binary_expression_precedence_level_3, Asts::ExpressionAst);
    CREATE_PARSER_RULE_VARIANT(binary_expression_precedence_level_4, Asts::ExpressionAst);
    CREATE_PARSER_RULE_VARIANT(binary_expression_precedence_level_5, Asts::ExpressionAst);
    CREATE_PARSER_RULE_VARIANT(binary_expression_precedence_level_6, Asts::ExpressionAst);

    CREATE_PARSER_RULE_VARIANT(unary_expression, Asts::ExpressionAst);
    CREATE_PARSER_RULE_VARIANT(postfix_expression, Asts::ExpressionAst);
    CREATE_PARSER_RULE_VARIANT(primary_expression, Asts::ExpressionAst);
    CREATE_PARSER_RULE(parenthesized_expression, Asts::ParenthesizedExpressionAst);
    CREATE_PARSER_RULE(self_identifier, Asts::IdentifierAst);
    CREATE_PARSER_RULE(fold_expression, Asts::TokenAst);

    CREATE_PARSER_RULE(case_expression, Asts::CaseExpressionAst);
    CREATE_PARSER_RULE(case_expression_patterns, Asts::CaseExpressionAst);
    CREATE_PARSER_RULE(case_expression_simple, Asts::CaseExpressionAst);
    CREATE_PARSER_RULE(loop_expression, Asts::LoopExpressionAst);
    CREATE_PARSER_RULE_VARIANT(loop_expression_condition, Asts::LoopConditionAst);
    CREATE_PARSER_RULE(loop_expression_condition_boolean, Asts::LoopConditionBooleanAst);
    CREATE_PARSER_RULE(loop_expression_condition_iterable, Asts::LoopConditionIterableAst);
    CREATE_PARSER_RULE(loop_else_statement, Asts::LoopElseStatementAst);
    CREATE_PARSER_RULE(gen_expression, Asts::GenExpressionAst);
    CREATE_PARSER_RULE(gen_expression_normal, Asts::GenExpressionAst);
    CREATE_PARSER_RULE(gen_expression_normal_no_expression, Asts::GenExpressionAst);
    CREATE_PARSER_RULE(gen_expression_normal_with_expression, Asts::GenExpressionAst);
    CREATE_PARSER_RULE(gen_expression_unroll, Asts::GenExpressionAst);

    CREATE_PARSER_RULE(ret_statement, Asts::RetStatementAst);
    CREATE_PARSER_RULE(exit_statement, Asts::LoopControlFlowStatementAst);
    CREATE_PARSER_RULE(exit_statement_final_action, Asts::LoopControlFlowFinalActionAst);
    CREATE_PARSER_RULE(skip_statement, Asts::LoopControlFlowStatementAst);
    CREATE_PARSER_RULE(pin_statement, Asts::PinStatementAst);
    CREATE_PARSER_RULE(rel_statement, Asts::RelStatementAst);
    CREATE_PARSER_RULE(inner_scope, Asts::InnerScopeAst);
    CREATE_PARSER_RULE_VARIANT(statement, Asts::StatementAst);

    CREATE_PARSER_RULE(global_use_statement, Asts::UseStatementAst);
    CREATE_PARSER_RULE(use_statement, Asts::UseStatementAst);
    CREATE_PARSER_RULE(comp_global_constant, Asts::GlobalConstantAst);

    CREATE_PARSER_RULE(global_constant, Asts::GlobalConstantAst);
    CREATE_PARSER_RULE_VARIANT(let_statement, Asts::LetStatementAst);
    CREATE_PARSER_RULE(let_statement_initialized, Asts::LetStatementInitializedAst);
    CREATE_PARSER_RULE(let_statement_uninitialized, Asts::LetStatementUninitializedAst);
    CREATE_PARSER_RULE_VARIANT(local_variable, Asts::LocalVariableAst);
    CREATE_PARSER_RULE(local_variable_destructure_skip_1_argument, Asts::LocalVariableDestructureSkip1ArgumentAst);
    CREATE_PARSER_RULE(local_variable_destructure_skip_n_arguments, Asts::LocalVariableDestructureSkipNArgumentsAst);
    CREATE_PARSER_RULE(local_variable_single_identifier, Asts::LocalVariableSingleIdentifierAst);
    CREATE_PARSER_RULE(local_variable_single_identifier_alias, Asts::LocalVariableSingleIdentifierAliasAst);
    CREATE_PARSER_RULE(local_variable_destructure_array, Asts::LocalVariableDestructureArrayAst);
    CREATE_PARSER_RULE(local_variable_destructure_object, Asts::LocalVariableDestructureObjectAst);
    CREATE_PARSER_RULE(local_variable_destructure_tuple, Asts::LocalVariableDestructureTupleAst);
    CREATE_PARSER_RULE(local_variable_attribute_binding, Asts::LocalVariableAttributeBindingAst);
    CREATE_PARSER_RULE(local_variable_nested_for_destructure_array, Asts::LocalVariableNestedForDestructureArrayAst);
    CREATE_PARSER_RULE(local_variable_nested_for_destructure_object, Asts::LocalVariableNestedForDestructureObjectAst);
    CREATE_PARSER_RULE(local_variable_nested_for_destructure_tuple, Asts::LocalVariableNestedForDestructureTupleAst);
    CREATE_PARSER_RULE(local_variable_nested_for_attribute_binding, Asts::LocalVariableNestedForAttributeBindingAst);

    CREATE_PARSER_RULE(assignment_statement, Asts::AssignmentStatementAst);

    CREATE_PARSER_RULE(case_expression_branch_simple, Asts::CaseExpressionBranchAst);
    CREATE_PARSER_RULE(case_expression_branch, Asts::CaseExpressionBranchAst);
    CREATE_PARSER_RULE(pattern_flavour_destructuring, Asts::CaseExpressionBranchAst);
    CREATE_PARSER_RULE(pattern_flavour_non_destructuring, Asts::CaseExpressionBranchAst);
    CREATE_PARSER_RULE(pattern_flavour_else_case, Asts::CaseExpressionBranchAst);
    CREATE_PARSER_RULE(pattern_flavour_else, Asts::CaseExpressionBranchAst);
    CREATE_PARSER_RULE_VARIANT(pattern_group_destructure, Asts::PatternGroupDestructureAst);
    CREATE_PARSER_RULE(pattern_variant_skip_argument, Asts::PatternVariantDestructureSkip1ArgumentAst);
    CREATE_PARSER_RULE(pattern_variant_skip_arguments, Asts::PatternVariantDestructureSkipNArgumentsAst);
    CREATE_PARSER_RULE(pattern_variant_single_identifier, Asts::PatternVariantSingleIdentifierAst);
    CREATE_PARSER_RULE(pattern_variant_destructure_array, Asts::PatternVariantDestructureArrayAst);
    CREATE_PARSER_RULE(pattern_variant_destructure_object, Asts::PatternVariantDestructureObjectAst);
    CREATE_PARSER_RULE(pattern_variant_destructure_tuple, Asts::PatternVariantDestructureTupleAst);
    CREATE_PARSER_RULE(pattern_variant_attribute_binding, Asts::PatternVariantAttributeBindingAst);
    CREATE_PARSER_RULE(pattern_variant_literal, Asts::PatternVariantLiteralAst)
    CREATE_PARSER_RULE(pattern_variant_expression, Asts::PatternVariantExpressionAst);
    CREATE_PARSER_RULE(pattern_variant_else, Asts::PatternVariantElseAst);
    CREATE_PARSER_RULE(pattern_variant_else_case, Asts::PatternVariantElseCaseAst);
    CREATE_PARSER_RULE(pattern_variant_nested_for_destructure_array, Asts::PatternVariantNestedForDestructureArrayAst);
    CREATE_PARSER_RULE(pattern_variant_nested_for_destructure_object, Asts::PatternVariantNestedForDestructureObjectAst);
    CREATE_PARSER_RULE(pattern_variant_nested_for_destructure_tuple, Asts::PatternVariantNestedForDestructureTupleAst);
    CREATE_PARSER_RULE(pattern_variant_nested_for_attribute_binding, Asts::PatternVariantNestedForAttributeBindingAst);
    CREATE_PARSER_RULE(pattern_guard, Asts::PatternGuardAst);

    CREATE_PARSER_RULE(binary_op_precedence_level_1, Asts::TokenAst);
    CREATE_PARSER_RULE(binary_op_precedence_level_2, Asts::TokenAst);
    CREATE_PARSER_RULE(binary_op_precedence_level_3, Asts::TokenAst);
    CREATE_PARSER_RULE(binary_op_precedence_level_4, Asts::TokenAst);
    CREATE_PARSER_RULE(binary_op_precedence_level_5, Asts::TokenAst);
    CREATE_PARSER_RULE(binary_op_precedence_level_6, Asts::TokenAst);
    CREATE_PARSER_RULE(boolean_comparison_op, Asts::TokenAst);
    CREATE_PARSER_RULE(unary_op, Asts::UnaryExpressionOperatorAst);
    CREATE_PARSER_RULE(unary_op_async_call, Asts::UnaryExpressionOperatorAsyncAst);
    CREATE_PARSER_RULE(postfix_op, Asts::PostfixExpressionOperatorAst);
    CREATE_PARSER_RULE(postfix_op_early_return, Asts::PostfixExpressionOperatorEarlyReturnAst);
    CREATE_PARSER_RULE(postfix_op_function_call, Asts::PostfixExpressionOperatorFunctionCallAst);
    CREATE_PARSER_RULE(postfix_op_member_access, Asts::PostfixExpressionOperatorMemberAccessAst);
    CREATE_PARSER_RULE(postfix_op_member_access_runtime, Asts::PostfixExpressionOperatorMemberAccessAst);
    CREATE_PARSER_RULE(postfix_op_member_access_static, Asts::PostfixExpressionOperatorMemberAccessAst);
    CREATE_PARSER_RULE(postfix_op_step_keyword, Asts::PostfixExpressionOperatorStepKeywordAst);
    CREATE_PARSER_RULE(postfix_op_not_keyword, Asts::PostfixExpressionOperatorNotKeywordAst);

    CREATE_PARSER_RULE(convention, Asts::ConventionAst);
    CREATE_PARSER_RULE(convention_mov, Asts::ConventionAst);
    CREATE_PARSER_RULE(convention_mut, Asts::ConventionAst);
    CREATE_PARSER_RULE(convention_ref, Asts::ConventionAst);

    CREATE_PARSER_RULE(object_initializer, Asts::ObjectInitializerAst);
    CREATE_PARSER_RULE(object_initializer_arguments, Asts::ObjectInitializerArgumentGroupAst);
    CREATE_PARSER_RULE(object_initializer_argument, Asts::ObjectInitializerArgumentAst);
    CREATE_PARSER_RULE(object_initializer_argument_named, Asts::ObjectInitializerArgumentNamedAst);
    CREATE_PARSER_RULE(object_initializer_argument_unnamed, Asts::ObjectInitializerArgumentUnnamedAst);

    template <std::invocable<Parser*> A1, std::invocable<Parser*> A2>
    auto parse_type_binary_expression_precedence_level_n_rhs(A1&& op, A2&& rhs) -> std::pair<PARSER_RESULT_TYPE(Asts::TokenAst), PARSER_RESULT_TYPE_VARIANT(Asts::TypeAst)>;
    template <std::invocable<Parser*> A1, std::invocable<Parser*> A2, std::invocable<Parser*> A3>
    auto parse_type_binary_expression_precedence_level_n(A1&& lhs, A2&& op, A3&& rhs) -> PARSER_RESULT_TYPE_VARIANT(Asts::TypeAst);
    CREATE_PARSER_RULE_VARIANT(type_binary_expression_precedence_level_1, Asts::TypeAst);
    CREATE_PARSER_RULE_VARIANT(type_binary_expression_precedence_level_2, Asts::TypeAst);
    CREATE_PARSER_RULE_VARIANT(type, Asts::TypeAst);
    CREATE_PARSER_RULE(type_binary_op_precedence_level_1, Asts::TokenAst);
    CREATE_PARSER_RULE(type_binary_op_precedence_level_2, Asts::TokenAst);
    CREATE_PARSER_RULE(type_unary_expression, Asts::TypeUnaryExpressionAst);
    CREATE_PARSER_RULE(type_postfix_expression, Asts::TypePostfixExpressionAst);
    CREATE_PARSER_RULE(type_primary_expression, Asts::TypePrimaryExpressionAst);
    CREATE_PARSER_RULE(type_parenthesized, Asts::TypeParenthesizedAst);
    CREATE_PARSER_RULE(type_array, Asts::TypeArrayAst);
    CREATE_PARSER_RULE(type_tuple, Asts::TypeTupleAst);
    CREATE_PARSER_RULE(type_single, Asts::TypeSingleAst);
    CREATE_PARSER_RULE_VARIANT(type_unary_op, Asts::TypeUnaryOperatorAst);
    CREATE_PARSER_RULE(type_unary_op_namespace, Asts::TypeUnaryOperatorNamespaceAst);
    CREATE_PARSER_RULE_VARIANT(type_postfix_op, Asts::TypePostfixOperatorAst);
    CREATE_PARSER_RULE(type_postfix_op_nested_type, Asts::TypePostfixOperatorNestedTypeAst);
    CREATE_PARSER_RULE(type_postfix_op_indexed_type, Asts::TypePostfixOperatorIndexedTypeAst);
    CREATE_PARSER_RULE(type_postfix_op_optional_type, Asts::TypePostfixOperatorOptionalTypeAst);
    CREATE_PARSER_RULE(type_tuple_1_items, Asts::TypeTupleAst);
    CREATE_PARSER_RULE(type_tuple_n_items, Asts::TypeTupleAst);

    CREATE_PARSER_RULE(identifier, Asts::IdentifierAst);
    CREATE_PARSER_RULE(numeric_identifier, Asts::IdentifierAst);
    CREATE_PARSER_RULE(upper_identifier, Asts::IdentifierAst);
    CREATE_PARSER_RULE(generic_identifier, Asts::GenericIdentifierAst);

    CREATE_PARSER_RULE(literal, Asts::LiteralAst);
    CREATE_PARSER_RULE(literal_float, Asts::FloatLiteralAst);
    CREATE_PARSER_RULE(literal_integer, Asts::IntegerLiteralAst);
    CREATE_PARSER_RULE(literal_string, Asts::StringLiteralAst);
    CREATE_PARSER_RULE(literal_boolean, Asts::BooleanLiteralAst);
    CREATE_PARSER_RULE(literal_array, Asts::ArrayLiteralAst);
    CREATE_PARSER_RULE(literal_comp_array, Asts::ArrayLiteralAst);
    CREATE_PARSER_RULE(literal_tuple, Asts::TupleLiteralAst);
    CREATE_PARSER_RULE(literal_comp_tuple, Asts::TupleLiteralAst);

    CREATE_PARSER_RULE(literal_float_b10, Asts::FloatLiteralAst);
    CREATE_PARSER_RULE(literal_integer_b10, Asts::IntegerLiteralAst);
    CREATE_PARSER_RULE(literal_integer_b16, Asts::IntegerLiteralAst);
    CREATE_PARSER_RULE(literal_integer_b02, Asts::IntegerLiteralAst);
    CREATE_PARSER_RULE(numeric_prefix_op, Asts::TokenAst);
    CREATE_PARSER_RULE(integer_postfix_type, Asts::IdentifierAst);
    CREATE_PARSER_RULE(float_postfix_type, Asts::IdentifierAst);

    CREATE_PARSER_RULE(literal_array_0_items, Asts::ArrayLiteralAst);
    CREATE_PARSER_RULE(literal_array_n_items, Asts::ArrayLiteralAst);
    CREATE_PARSER_RULE(literal_comp_array_n_items, Asts::ArrayLiteralAst);
    CREATE_PARSER_RULE(literal_tuple_0_items, Asts::TupleLiteralAst);
    CREATE_PARSER_RULE(literal_tuple_1_items, Asts::TupleLiteralAst);
    CREATE_PARSER_RULE(literal_tuple_n_items, Asts::TupleLiteralAst);
    CREATE_PARSER_RULE(literal_comp_tuple_1_items, Asts::TupleLiteralAst);
    CREATE_PARSER_RULE(literal_comp_tuple_n_items, Asts::TupleLiteralAst);

    CREATE_PARSER_RULE_VARIANT(comp_value, Asts::ExpressionAst);
    CREATE_PARSER_RULE(comp_object_initializer, Asts::ObjectInitializerAst);
    CREATE_PARSER_RULE(comp_object_initializer_arguments, Asts::ObjectInitializerArgumentGroupAst);
    CREATE_PARSER_RULE(comp_object_initializer_argument_named, Asts::ObjectInitializerArgumentNamedAst);

    auto parse_token_left_curly_brace() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_right_curly_brace() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_left_parenthesis() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_right_parenthesis() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_left_square_bracket() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_right_square_bracket() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_dot() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_comma() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_colon() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_at() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_assign() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_newline() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_question_mark() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_borrow() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_union() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_lt() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_gt() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_add() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_sub() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_mul() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_div() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_rem() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_underscore() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_speech_mark() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_double_colon() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_double_dot() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_rightward_arrow() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_eq() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_ne() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_le() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_ge() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_add_assign() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_sub_assign() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_ss() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_mul_assign() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_div_assign() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_rem_assign() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_mod_assign() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_exp_assign() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_mod() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_exp() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_nothing() -> std::unique_ptr<Asts::TokenAst>;

    auto parse_keyword_cls() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_sup() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_ext() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_fun() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_cor() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_use() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_let() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_mut() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_cmp() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_where() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_self_val() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_self_type() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_case() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_loop() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_with() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_gen() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_ret() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_skip() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_exit() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_else() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_false() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_true() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_of() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_in() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_pin() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_rel() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_as() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_is() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_and() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_or() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_not() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_async() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_keyword_step() -> std::unique_ptr<Asts::TokenAst>;

    auto parse_lexeme_dec_integer() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_lexeme_bin_integer() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_lexeme_hex_integer() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_lexeme_string() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_lexeme_identifier() -> std::unique_ptr<Asts::TokenAst>;
    auto parse_lexeme_upper_identifier() -> std::unique_ptr<Asts::TokenAst>;

    auto parse_lexeme(LexicalAnalysis::RawTokenTypes token_type) -> PARSER_RESULT_TYPE(Asts::TokenAst);
    auto parse_characters(std::string&& characters) -> PARSER_RESULT_TYPE(Asts::TokenAst);
    auto parse_character(char character) -> PARSER_RESULT_TYPE(Asts::TokenAst);
    auto parse_keyword_primitive(LexicalAnalysis::TokenTypes keyword) -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_primitive(LexicalAnalysis::RawTokenTypes token_type) -> PARSER_RESULT_TYPE(Asts::TokenAst);
};
