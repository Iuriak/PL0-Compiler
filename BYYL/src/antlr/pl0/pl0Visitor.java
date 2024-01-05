// Generated from E:/¥Û»˝…œ/BYYL/src/pl0.g4 by ANTLR 4.13.1
package pl0;
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link pl0Parser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface pl0Visitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link pl0Parser#program}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProgram(pl0Parser.ProgramContext ctx);
	/**
	 * Visit a parse tree produced by {@link pl0Parser#programHeader}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProgramHeader(pl0Parser.ProgramHeaderContext ctx);
	/**
	 * Visit a parse tree produced by {@link pl0Parser#subProgram}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitSubProgram(pl0Parser.SubProgramContext ctx);
	/**
	 * Visit a parse tree produced by {@link pl0Parser#constSection}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConstSection(pl0Parser.ConstSectionContext ctx);
	/**
	 * Visit a parse tree produced by {@link pl0Parser#constDefinition}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConstDefinition(pl0Parser.ConstDefinitionContext ctx);
	/**
	 * Visit a parse tree produced by {@link pl0Parser#varSection}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitVarSection(pl0Parser.VarSectionContext ctx);
	/**
	 * Visit a parse tree produced by {@link pl0Parser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStatement(pl0Parser.StatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link pl0Parser#compoundStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCompoundStatement(pl0Parser.CompoundStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link pl0Parser#assignmentStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAssignmentStatement(pl0Parser.AssignmentStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link pl0Parser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExpression(pl0Parser.ExpressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link pl0Parser#plusminusOP}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPlusminusOP(pl0Parser.PlusminusOPContext ctx);
	/**
	 * Visit a parse tree produced by {@link pl0Parser#term}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTerm(pl0Parser.TermContext ctx);
	/**
	 * Visit a parse tree produced by {@link pl0Parser#multdivOP}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMultdivOP(pl0Parser.MultdivOPContext ctx);
	/**
	 * Visit a parse tree produced by {@link pl0Parser#factor}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFactor(pl0Parser.FactorContext ctx);
	/**
	 * Visit a parse tree produced by {@link pl0Parser#ifStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIfStatement(pl0Parser.IfStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link pl0Parser#whileStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitWhileStatement(pl0Parser.WhileStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link pl0Parser#condition}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCondition(pl0Parser.ConditionContext ctx);
	/**
	 * Visit a parse tree produced by {@link pl0Parser#relationalOp}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRelationalOp(pl0Parser.RelationalOpContext ctx);
	/**
	 * Visit a parse tree produced by {@link pl0Parser#emptyStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitEmptyStatement(pl0Parser.EmptyStatementContext ctx);
}