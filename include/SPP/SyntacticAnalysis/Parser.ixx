module;
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <optional>


#define PARSER_RESULT_TYPE(T) std::unique_ptr<T>

#define CREATE_PARSER_RULE(what, type) auto parse_##what() -> std::unique_ptr<type>;


export module spp.syntactic_analysis.parser;
import spp.lexical_analysis.tokens;
import spp.semantic_analysis.asts.ast_types;
import spp.syntactic_analysis.parser_error;
import spp.utils.error_formatter;


namespace SPP::SyntacticAnalysis {
    export class Parser;

    template <typename F>
    concept is_parser_member_function = requires(F f, Parser *p) {
        std::mem_fn(f)(p);
    };
}

using namespace SPP::SemanticAnalysis;


class SPP::SyntacticAnalysis::Parser {
    std::size_t pos = 0;
    std::size_t token_stream_size;
    std::string name;
    std::vector<LexicalAnalysis::RawToken> token_stream;
    Utils::ErrorFormatter error_formatter;
    std::optional<Errors::SyntaxError> error = std::nullopt;

    auto store_error(std::size_t pos, std::string error) -> bool;

public:
    explicit Parser(std::vector<LexicalAnalysis::RawToken> token_stream, std::string file_name = "", std::optional<Utils::ErrorFormatter> error_formatter = std::nullopt);
    auto get_current_token() const -> LexicalAnalysis::RawToken;
    auto get_current_pos() const -> std::size_t;
    auto set_current_pos(std::size_t new_index) -> void;

private:
    template <is_parser_member_function F>
    auto parse_once(F &&parser_rule) -> decltype(auto);

    template <typename F>
    auto parse_once(F &&parser_rule) -> decltype(auto);

    template <typename F>
    auto parse_optional(F &&parser_rule) -> std::optional<std::invoke_result_t<F, Parser*>>;

    template <typename F, is_parser_member_function S>
    auto parse_0_or_more(F &&parser_rule, S &&separator) -> std::vector<std::invoke_result_t<F, Parser*>>;

    template <typename F, is_parser_member_function S>
    auto parse_1_or_more(F &&parser_rule, S &&separator) -> std::vector<std::invoke_result_t<F, Parser*>>;

    template <typename F, is_parser_member_function S>
    auto parse_2_or_more(F &&parser_rule, S &&separator) -> std::vector<std::invoke_result_t<F, Parser*>>;

    template <typename F, typename... Fs>
    auto parse_alternate(F&& parser_rule, Fs &&... parser_rules) -> std::unique_ptr<Asts::Ast>;

    template <typename F>
    auto parse_alternate(F&& parser_rule) -> std::unique_ptr<Asts::Ast>;

public:
    auto parse() -> Asts::RootAst;

private:
    CREATE_PARSER_RULE(root, Asts::ModulePrototypeAst)
    CREATE_PARSER_RULE(eof, Asts::TokenAst)

    CREATE_PARSER_RULE(module_prototype, Asts::ModulePrototypeAst)
    CREATE_PARSER_RULE(module_implementation, Asts::ModuleImplementationAst)
    CREATE_PARSER_RULE(module_member, Asts::Ast)

    CREATE_PARSER_RULE(class_prototype, Asts::ClassPrototypeAst)
    CREATE_PARSER_RULE(class_implementation, Asts::ClassImplementationAst)
    CREATE_PARSER_RULE(class_member, Asts::Ast)
    CREATE_PARSER_RULE(class_attribute, Asts::ClassAttributeAst)

    CREATE_PARSER_RULE(sup_prototype_functions, Asts::SupPrototypeFunctionsAst);
    CREATE_PARSER_RULE(sup_prototype_extension, Asts::SupPrototypeExtensionAst);
    CREATE_PARSER_RULE(sup_implementation, Asts::SupImplementationAst);
    CREATE_PARSER_RULE(sup_member, Asts::Ast);
    CREATE_PARSER_RULE(sup_subroutine_prototype, Asts::SubroutinePrototypeAst);
    CREATE_PARSER_RULE(sup_coroutine_prototype, Asts::CoroutinePrototypeAst);
    CREATE_PARSER_RULE(sup_use_statement, Asts::UseStatementAst);

    CREATE_PARSER_RULE(subroutine_prototype, Asts::SubroutinePrototypeAst);
    CREATE_PARSER_RULE(coroutine_prototype, Asts::CoroutinePrototypeAst);
    CREATE_PARSER_RULE(function_implementation, Asts::FunctionImplementationAst);
    CREATE_PARSER_RULE(function_member, Asts::Ast);

    CREATE_PARSER_RULE(function_call_arguments, Asts::FunctionCallArgumentGroupAst);
    CREATE_PARSER_RULE(function_call_argument, Asts::Ast);
    CREATE_PARSER_RULE(function_call_argument_unnamed, Asts::FunctionCallArgumentUnnamedAst);
    CREATE_PARSER_RULE(function_call_argument_named, Asts::FunctionCallArgumentNamedAst);

    CREATE_PARSER_RULE(function_parameters, Asts::FunctionParameterGroupAst);
    CREATE_PARSER_RULE(function_parameter, Asts::Ast);
    CREATE_PARSER_RULE(function_parameter_self, Asts::FunctionParameterSelfAst);
    CREATE_PARSER_RULE(function_parameter_required, Asts::FunctionParameterRequiredAst);
    CREATE_PARSER_RULE(function_parameter_optional, Asts::FunctionParameterOptionalAst);
    CREATE_PARSER_RULE(function_parameter_variadic, Asts::FunctionParameterVariadicAst);

    CREATE_PARSER_RULE(generic_arguments, Asts::GenericArgumentGroupAst);
    CREATE_PARSER_RULE(generic_argument, Asts::Ast);
    CREATE_PARSER_RULE(generic_argument_type_named, Asts::GenericTypeArgumentNamedAst);
    CREATE_PARSER_RULE(generic_argument_type_unnamed, Asts::GenericTypeArgumentUnnamedAst);
    CREATE_PARSER_RULE(generic_argument_comp_named, Asts::GenericCompArgumentNamedAst);
    CREATE_PARSER_RULE(generic_argument_comp_unnamed, Asts::GenericCompArgumentUnnamedAst);

    CREATE_PARSER_RULE(generic_parameters, Asts::GenericParameterGroupAst);
    CREATE_PARSER_RULE(generic_parameter, Asts::Ast);
    CREATE_PARSER_RULE(generic_parameter_type_required, Asts::GenericTypeParameterRequiredAst);
    CREATE_PARSER_RULE(generic_parameter_type_optional, Asts::GenericTypeParameterOptionalAst);
    CREATE_PARSER_RULE(generic_parameter_type_variadic, Asts::GenericTypeParameterVariadicAst);
    CREATE_PARSER_RULE(generic_parameter_comp_required, Asts::GenericCompParameterRequiredAst);
    CREATE_PARSER_RULE(generic_parameter_comp_optional, Asts::GenericCompParameterOptionalAst);
    CREATE_PARSER_RULE(generic_parameter_comp_variadic, Asts::GenericCompParameterVariadicAst);
    CREATE_PARSER_RULE(generic_inline_constraints, Asts::GenericTypeParameterInlineConstraintsAst);

    CREATE_PARSER_RULE(where_block, Asts::WhereBlockAst);
    CREATE_PARSER_RULE(where_block_constraints_group, Asts::WhereConstraintsGroupAst);
    CREATE_PARSER_RULE(where_block_constraints, Asts::WhereConstraintsAst);

    CREATE_PARSER_RULE(annotation, Asts::AnnotationAst);

    CREATE_PARSER_RULE(expression, Asts::Ast);
    template <typename A1, typename A2>
    auto parse_binary_expression_precedence_level_n_rhs(A1 &&op, A2 &&rhs) -> std::pair<PARSER_RESULT_TYPE(Asts::TokenAst), PARSER_RESULT_TYPE(Asts::Ast)>;
    template <typename A1, typename A2, typename A3>
    auto parse_binary_expression_precedence_level_n(A1 &&lhs, A2 &&op, A3 &&rhs) -> PARSER_RESULT_TYPE(Asts::Ast);

    CREATE_PARSER_RULE(binary_expression_precedence_level_1, Asts::Ast);
    CREATE_PARSER_RULE(binary_expression_precedence_level_2, Asts::Ast);
    CREATE_PARSER_RULE(binary_expression_precedence_level_3, Asts::Ast);
    CREATE_PARSER_RULE(binary_expression_precedence_level_4, Asts::Ast);
    CREATE_PARSER_RULE(binary_expression_precedence_level_5, Asts::Ast);
    CREATE_PARSER_RULE(binary_expression_precedence_level_6, Asts::Ast);

    CREATE_PARSER_RULE(unary_expression, Asts::Ast);
    CREATE_PARSER_RULE(postfix_expression, Asts::Ast);
    CREATE_PARSER_RULE(primary_expression, Asts::Ast);
    CREATE_PARSER_RULE(parenthesized_expression, Asts::ParenthesizedExpressionAst);
    CREATE_PARSER_RULE(self_identifier, Asts::IdentifierAst);
    CREATE_PARSER_RULE(fold_expression, Asts::TokenAst);

    CREATE_PARSER_RULE(case_expression, Asts::CaseExpressionAst);
    CREATE_PARSER_RULE(case_expression_patterns, Asts::CaseExpressionAst);
    CREATE_PARSER_RULE(case_expression_simple, Asts::CaseExpressionAst);
    CREATE_PARSER_RULE(loop_expression, Asts::LoopExpressionAst);
    CREATE_PARSER_RULE(loop_expression_condition, Asts::Ast);
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
    CREATE_PARSER_RULE(exit_statement_final_action, Asts::Ast);
    CREATE_PARSER_RULE(skip_statement, Asts::LoopControlFlowStatementAst);
    CREATE_PARSER_RULE(pin_statement, Asts::PinStatementAst);
    CREATE_PARSER_RULE(rel_statement, Asts::RelStatementAst);
    CREATE_PARSER_RULE(inner_scope, Asts::InnerScopeAst);
    CREATE_PARSER_RULE(statement, Asts::Ast);

    CREATE_PARSER_RULE(global_use_statement, Asts::UseStatementAst);
    CREATE_PARSER_RULE(use_statement, Asts::UseStatementAst);
    CREATE_PARSER_RULE(comp_global_constant, Asts::GlobalConstantAst);

    CREATE_PARSER_RULE(global_constant, Asts::GlobalConstantAst);
    CREATE_PARSER_RULE(let_statement, Asts::Ast);
    CREATE_PARSER_RULE(let_statement_initialized, Asts::LetStatementInitializedAst);
    CREATE_PARSER_RULE(let_statement_uninitialized, Asts::LetStatementUninitializedAst);
    CREATE_PARSER_RULE(local_variable, Asts::Ast);
    CREATE_PARSER_RULE(local_variable_destructure_skip_1_argument, Asts::LocalVariableDestructureSkip1ArgumentAst);
    CREATE_PARSER_RULE(local_variable_destructure_skip_n_arguments, Asts::LocalVariableDestructureSkipNArgumentsAst);
    CREATE_PARSER_RULE(local_variable_single_identifier, Asts::LocalVariableSingleIdentifierAst);
    CREATE_PARSER_RULE(local_variable_single_identifier_alias, Asts::LocalVariableSingleIdentifierAliasAst);
    CREATE_PARSER_RULE(local_variable_destructure_array, Asts::LocalVariableDestructureArrayAst);
    CREATE_PARSER_RULE(local_variable_destructure_object, Asts::LocalVariableDestructureObjectAst);
    CREATE_PARSER_RULE(local_variable_destructure_tuple, Asts::LocalVariableDestructureTupleAst);
    CREATE_PARSER_RULE(local_variable_attribute_binding, Asts::LocalVariableAttributeBindingAst);
    CREATE_PARSER_RULE(local_variable_nested_for_destructure_array, Asts::Ast);
    CREATE_PARSER_RULE(local_variable_nested_for_destructure_object, Asts::Ast);
    CREATE_PARSER_RULE(local_variable_nested_for_destructure_tuple, Asts::Ast);
    CREATE_PARSER_RULE(local_variable_nested_for_attribute_binding, Asts::Ast);

    CREATE_PARSER_RULE(assignment_statement, Asts::AssignmentStatementAst);

    CREATE_PARSER_RULE(case_expression_branch_simple, Asts::CaseExpressionBranchAst);
    CREATE_PARSER_RULE(case_expression_branch, Asts::CaseExpressionBranchAst);
    CREATE_PARSER_RULE(pattern_flavour_destructuring, Asts::CaseExpressionBranchAst);
    CREATE_PARSER_RULE(pattern_flavour_non_destructuring, Asts::CaseExpressionBranchAst);
    CREATE_PARSER_RULE(pattern_flavour_else_case, Asts::CaseExpressionBranchAst);
    CREATE_PARSER_RULE(pattern_flavour_else, Asts::CaseExpressionBranchAst);
    CREATE_PARSER_RULE(pattern_group_destructure, Asts::Ast);
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
    CREATE_PARSER_RULE(pattern_variant_nested_for_destructure_array, Asts::Ast);
    CREATE_PARSER_RULE(pattern_variant_nested_for_destructure_object, Asts::Ast);
    CREATE_PARSER_RULE(pattern_variant_nested_for_destructure_tuple, Asts::Ast);
    CREATE_PARSER_RULE(pattern_variant_nested_for_attribute_binding, Asts::Ast);
    CREATE_PARSER_RULE(pattern_guard, Asts::PatternGuardAst);

    CREATE_PARSER_RULE(binary_op_precedence_level_1, Asts::TokenAst);
    CREATE_PARSER_RULE(binary_op_precedence_level_2, Asts::TokenAst);
    CREATE_PARSER_RULE(binary_op_precedence_level_3, Asts::TokenAst);
    CREATE_PARSER_RULE(binary_op_precedence_level_4, Asts::TokenAst);
    CREATE_PARSER_RULE(binary_op_precedence_level_5, Asts::TokenAst);
    CREATE_PARSER_RULE(binary_op_precedence_level_6, Asts::TokenAst);
    CREATE_PARSER_RULE(boolean_comparison_op, Asts::TokenAst);
    CREATE_PARSER_RULE(unary_op, Asts::Ast);
    CREATE_PARSER_RULE(unary_op_async_call, Asts::UnaryExpressionOperatorAsyncAst);
    CREATE_PARSER_RULE(postfix_op, Asts::Ast);
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
    CREATE_PARSER_RULE(object_initializer_argument, Asts::Ast);
    CREATE_PARSER_RULE(object_initializer_argument_named, Asts::ObjectInitializerArgumentNamedAst);
    CREATE_PARSER_RULE(object_initializer_argument_unnamed, Asts::ObjectInitializerArgumentUnnamedAst);

    template <typename A1, typename A2>
    auto parse_type_binary_expression_precedence_level_n_rhs(A1 &&op, A2 &&rhs) -> std::pair<PARSER_RESULT_TYPE(Asts::TokenAst), PARSER_RESULT_TYPE(Asts::Ast)>;
    template <typename A1, typename A2, typename A3>
    auto parse_type_binary_expression_precedence_level_n(A1 &&lhs, A2 &&op, A3 &&rhs) -> PARSER_RESULT_TYPE(Asts::Ast);
    CREATE_PARSER_RULE(type_binary_expression_precedence_level_1, Asts::Ast);
    CREATE_PARSER_RULE(type_binary_expression_precedence_level_2, Asts::Ast);
    CREATE_PARSER_RULE(type, Asts::Ast);
    CREATE_PARSER_RULE(type_binary_op_precedence_level_1, Asts::TokenAst);
    CREATE_PARSER_RULE(type_binary_op_precedence_level_2, Asts::TokenAst);
    CREATE_PARSER_RULE(type_unary_expression, Asts::Ast);
    CREATE_PARSER_RULE(type_postfix_expression, Asts::Ast);
    CREATE_PARSER_RULE(type_primary_expression, Asts::Ast);
    CREATE_PARSER_RULE(type_parenthesized, Asts::Ast);
    CREATE_PARSER_RULE(type_array, Asts::Ast);
    CREATE_PARSER_RULE(type_tuple, Asts::Ast);
    CREATE_PARSER_RULE(type_single, Asts::TypeSingleAst);
    CREATE_PARSER_RULE(type_unary_op, Asts::Ast);
    CREATE_PARSER_RULE(type_unary_op_namespace, Asts::TypeUnaryOperatorNamespaceAst);
    CREATE_PARSER_RULE(type_postfix_op, Asts::Ast);
    CREATE_PARSER_RULE(type_postfix_op_nested_type, Asts::TypePostfixOperatorNestedTypeAst);
    CREATE_PARSER_RULE(type_postfix_op_indexed_type, Asts::TypePostfixOperatorIndexedTypeAst);
    CREATE_PARSER_RULE(type_postfix_op_optional_type, Asts::TypePostfixOperatorOptionalTypeAst);
    CREATE_PARSER_RULE(type_tuple_1_items, Asts::TypeTupleAst);
    CREATE_PARSER_RULE(type_tuple_n_items, Asts::TypeTupleAst);

    CREATE_PARSER_RULE(identifier, Asts::IdentifierAst);
    CREATE_PARSER_RULE(numeric_identifier, Asts::IdentifierAst);
    CREATE_PARSER_RULE(upper_identifier, Asts::IdentifierAst);
    CREATE_PARSER_RULE(generic_identifier, Asts::GenericIdentifierAst);

    CREATE_PARSER_RULE(literal, Asts::Ast);
    CREATE_PARSER_RULE(literal_float, Asts::FloatLiteralAst);
    CREATE_PARSER_RULE(literal_integer, Asts::IntegerLiteralAst);
    CREATE_PARSER_RULE(literal_string, Asts::StringLiteralAst);
    CREATE_PARSER_RULE(literal_boolean, Asts::BooleanLiteralAst);
    CREATE_PARSER_RULE(literal_array, Asts::Ast);
    CREATE_PARSER_RULE(literal_comp_array, Asts::Ast);
    CREATE_PARSER_RULE(literal_tuple, Asts::TupleLiteralAst);
    CREATE_PARSER_RULE(literal_comp_tuple, Asts::TupleLiteralAst);

    CREATE_PARSER_RULE(literal_float_b10, Asts::FloatLiteralAst);
    CREATE_PARSER_RULE(literal_integer_b10, Asts::IntegerLiteralAst);
    CREATE_PARSER_RULE(literal_integer_b16, Asts::IntegerLiteralAst);
    CREATE_PARSER_RULE(literal_integer_b02, Asts::IntegerLiteralAst);
    CREATE_PARSER_RULE(numeric_prefix_op, Asts::TokenAst);
    CREATE_PARSER_RULE(integer_postfix_type, Asts::IdentifierAst);
    CREATE_PARSER_RULE(float_postfix_type, Asts::IdentifierAst);

    CREATE_PARSER_RULE(literal_array_0_items, Asts::Ast);
    CREATE_PARSER_RULE(literal_array_n_items, Asts::Ast);
    CREATE_PARSER_RULE(literal_comp_array_n_items, Asts::Ast);
    CREATE_PARSER_RULE(literal_tuple_0_items, Asts::TupleLiteralAst);
    CREATE_PARSER_RULE(literal_tuple_1_items, Asts::TupleLiteralAst);
    CREATE_PARSER_RULE(literal_tuple_n_items, Asts::TupleLiteralAst);
    CREATE_PARSER_RULE(literal_comp_tuple_1_items, Asts::TupleLiteralAst);
    CREATE_PARSER_RULE(literal_comp_tuple_n_items, Asts::TupleLiteralAst);

    CREATE_PARSER_RULE(comp_value, Asts::Ast);
    CREATE_PARSER_RULE(comp_object_initializer, Asts::ObjectInitializerAst);
    CREATE_PARSER_RULE(comp_object_initializer_arguments, Asts::ObjectInitializerArgumentGroupAst);
    CREATE_PARSER_RULE(comp_object_initializer_argument_named, Asts::Ast);

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

    auto parse_characters(std::string &&characters) -> PARSER_RESULT_TYPE(Asts::TokenAst);
    auto parse_character(char character) -> PARSER_RESULT_TYPE(Asts::TokenAst);
    auto parse_keyword_primitive(LexicalAnalysis::TokenTypes keyword) -> std::unique_ptr<Asts::TokenAst>;
    auto parse_token_primitive(LexicalAnalysis::RawTokenTypes token_type) -> PARSER_RESULT_TYPE(Asts::TokenAst);
};

template <SPP::SyntacticAnalysis::is_parser_member_function F>
auto SPP::SyntacticAnalysis::Parser::parse_once(F &&parser_rule) -> decltype(auto) {
    return std::mem_fn(std::forward<F>(parser_rule))(this);
}

template <typename F>
auto SPP::SyntacticAnalysis::Parser::parse_once(F &&parser_rule) -> decltype(auto) {
    return std::invoke(std::forward<F>(parser_rule), this);
}

template <typename F>
auto SPP::SyntacticAnalysis::Parser::parse_optional(F &&parser_rule) -> std::optional<std::invoke_result_t<F, Parser*>> {
    const auto index = pos;

    try {
        auto result = parse_once(std::forward<F>(parser_rule));
        auto optional_type = std::optional<decltype(result)>();
        optional_type = std::move(result);
        return optional_type;
    }
    catch (Errors::SyntaxError &) {
        pos = index;
        return std::nullopt;
    }
}

template <typename F, SPP::SyntacticAnalysis::is_parser_member_function S>
auto SPP::SyntacticAnalysis::Parser::parse_0_or_more(F &&parser_rule, S &&separator) -> std::vector<std::invoke_result_t<F, Parser*>> {
    auto done_1_parse = false;
    auto result = std::vector<std::invoke_result_t<F, Parser*>>{};
    auto temp_index = pos;

    while (true) {
        if (done_1_parse) {
            const auto sep = parse_optional(std::forward<S>(separator));
            if (not sep.has_value()) { return result; }
        }

        try {
            const auto ast = parse_once(std::forward<F>(parser_rule));
            result.push_back(std::move(ast));
            done_1_parse = true;
            temp_index = pos;
        }
        catch (Errors::SyntaxError &) {
            pos = temp_index;
            return result;
        }
    }
}

template <typename F, SPP::SyntacticAnalysis::is_parser_member_function S>
auto SPP::SyntacticAnalysis::Parser::parse_1_or_more(F &&parser_rule, S &&separator) -> std::vector<std::invoke_result_t<F, Parser*>> {
    const auto result = parse_0_or_more(std::forward<F>(parser_rule), std::forward<S>(separator));
    if (result.empty()) {
        throw Errors::SyntaxError{pos, "Expected at least one element"};
    }
    return result;
}

template <typename F, SPP::SyntacticAnalysis::is_parser_member_function S>
auto SPP::SyntacticAnalysis::Parser::parse_2_or_more(F &&parser_rule, S &&separator) -> std::vector<std::invoke_result_t<F, Parser*>> {
    const auto result = parse_0_or_more(std::forward<F>(parser_rule), std::forward<S>(separator));
    if (result.size() < 2) {
        throw Errors::SyntaxError{pos, "Expected at least two elements"};
    }
    return result;
}

template <typename F, typename ... Fs>
auto SPP::SyntacticAnalysis::Parser::parse_alternate(F&& parser_rule, Fs &&... parser_rules) -> std::unique_ptr<Asts::Ast> {
    auto result = parse_optional(std::forward<F>(parser_rule));
    return result.value_or(parse_alternate(std::forward<Fs>(parser_rules)...));
}

template <typename F>
auto SPP::SyntacticAnalysis::Parser::parse_alternate(F&& parser_rule) -> std::unique_ptr<Asts::Ast> {
    return std::mem_fn(std::forward<F>(parser_rule))(this);
}
