export module spp.semantic_analysis.asts.array_literal_ast;
import spp.utils.variant_intrinsics;
import spp.semantic_analysis.asts.array_literal_0_element_ast;
import spp.semantic_analysis.asts.array_literal_n_elements_ast;


export namespace SPP::SemanticAnalysis::Asts {
    using ArrayLiteralAst = CollapsingVariant<
        ArrayLiteral0ElementAst,
        ArrayLiteralNElementsAst>;
}
