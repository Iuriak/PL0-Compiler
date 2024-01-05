// Generated from E:/¥Û»˝…œ/BYYL/src/pl0.g4 by ANTLR 4.13.1
package pl0;
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link pl0Parser}.
 */
public interface pl0Listener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link pl0Parser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(pl0Parser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(pl0Parser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link pl0Parser#programHeader}.
	 * @param ctx the parse tree
	 */
	void enterProgramHeader(pl0Parser.ProgramHeaderContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#programHeader}.
	 * @param ctx the parse tree
	 */
	void exitProgramHeader(pl0Parser.ProgramHeaderContext ctx);
	/**
	 * Enter a parse tree produced by {@link pl0Parser#subProgram}.
	 * @param ctx the parse tree
	 */
	void enterSubProgram(pl0Parser.SubProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#subProgram}.
	 * @param ctx the parse tree
	 */
	void exitSubProgram(pl0Parser.SubProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link pl0Parser#constSection}.
	 * @param ctx the parse tree
	 */
	void enterConstSection(pl0Parser.ConstSectionContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#constSection}.
	 * @param ctx the parse tree
	 */
	void exitConstSection(pl0Parser.ConstSectionContext ctx);
	/**
	 * Enter a parse tree produced by {@link pl0Parser#constDefinition}.
	 * @param ctx the parse tree
	 */
	void enterConstDefinition(pl0Parser.ConstDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#constDefinition}.
	 * @param ctx the parse tree
	 */
	void exitConstDefinition(pl0Parser.ConstDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link pl0Parser#varSection}.
	 * @param ctx the parse tree
	 */
	void enterVarSection(pl0Parser.VarSectionContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#varSection}.
	 * @param ctx the parse tree
	 */
	void exitVarSection(pl0Parser.VarSectionContext ctx);
	/**
	 * Enter a parse tree produced by {@link pl0Parser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(pl0Parser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(pl0Parser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link pl0Parser#compoundStatement}.
	 * @param ctx the parse tree
	 */
	void enterCompoundStatement(pl0Parser.CompoundStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#compoundStatement}.
	 * @param ctx the parse tree
	 */
	void exitCompoundStatement(pl0Parser.CompoundStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link pl0Parser#assignmentStatement}.
	 * @param ctx the parse tree
	 */
	void enterAssignmentStatement(pl0Parser.AssignmentStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#assignmentStatement}.
	 * @param ctx the parse tree
	 */
	void exitAssignmentStatement(pl0Parser.AssignmentStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link pl0Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(pl0Parser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(pl0Parser.ExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link pl0Parser#plusminusOP}.
	 * @param ctx the parse tree
	 */
	void enterPlusminusOP(pl0Parser.PlusminusOPContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#plusminusOP}.
	 * @param ctx the parse tree
	 */
	void exitPlusminusOP(pl0Parser.PlusminusOPContext ctx);
	/**
	 * Enter a parse tree produced by {@link pl0Parser#term}.
	 * @param ctx the parse tree
	 */
	void enterTerm(pl0Parser.TermContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#term}.
	 * @param ctx the parse tree
	 */
	void exitTerm(pl0Parser.TermContext ctx);
	/**
	 * Enter a parse tree produced by {@link pl0Parser#multdivOP}.
	 * @param ctx the parse tree
	 */
	void enterMultdivOP(pl0Parser.MultdivOPContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#multdivOP}.
	 * @param ctx the parse tree
	 */
	void exitMultdivOP(pl0Parser.MultdivOPContext ctx);
	/**
	 * Enter a parse tree produced by {@link pl0Parser#factor}.
	 * @param ctx the parse tree
	 */
	void enterFactor(pl0Parser.FactorContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#factor}.
	 * @param ctx the parse tree
	 */
	void exitFactor(pl0Parser.FactorContext ctx);
	/**
	 * Enter a parse tree produced by {@link pl0Parser#ifStatement}.
	 * @param ctx the parse tree
	 */
	void enterIfStatement(pl0Parser.IfStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#ifStatement}.
	 * @param ctx the parse tree
	 */
	void exitIfStatement(pl0Parser.IfStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link pl0Parser#whileStatement}.
	 * @param ctx the parse tree
	 */
	void enterWhileStatement(pl0Parser.WhileStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#whileStatement}.
	 * @param ctx the parse tree
	 */
	void exitWhileStatement(pl0Parser.WhileStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link pl0Parser#condition}.
	 * @param ctx the parse tree
	 */
	void enterCondition(pl0Parser.ConditionContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#condition}.
	 * @param ctx the parse tree
	 */
	void exitCondition(pl0Parser.ConditionContext ctx);
	/**
	 * Enter a parse tree produced by {@link pl0Parser#relationalOp}.
	 * @param ctx the parse tree
	 */
	void enterRelationalOp(pl0Parser.RelationalOpContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#relationalOp}.
	 * @param ctx the parse tree
	 */
	void exitRelationalOp(pl0Parser.RelationalOpContext ctx);
	/**
	 * Enter a parse tree produced by {@link pl0Parser#emptyStatement}.
	 * @param ctx the parse tree
	 */
	void enterEmptyStatement(pl0Parser.EmptyStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link pl0Parser#emptyStatement}.
	 * @param ctx the parse tree
	 */
	void exitEmptyStatement(pl0Parser.EmptyStatementContext ctx);
}