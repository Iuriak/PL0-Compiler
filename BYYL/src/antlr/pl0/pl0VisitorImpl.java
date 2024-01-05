
package pl0;
import org.antlr.v4.runtime.tree.TerminalNode;

import java.util.HashMap;
import java.util.Map;
public class pl0VisitorImpl extends pl0BaseVisitor<String> {

    private Map<String, String> symbolTable;
    private int tempVarCounter = 0;
    private int labelCounter = 0;

    private int count=0;

    private String newTempVar() {
        String tempVar = "t" + tempVarCounter++;
        symbolTable.put(tempVar, "temp");
        return tempVar;
    }
    private String newLabel() {
        return "L" + labelCounter++;
    }

    public pl0VisitorImpl() {
        symbolTable = new HashMap<>();
    }

    @Override
    public String visitConstDefinition(pl0Parser.ConstDefinitionContext ctx){
        String type = "const";
       String name=ctx.ID().getText();
       declareVariable(name,type);
        return null;

    }
    public String visitVarSection(pl0Parser.VarSectionContext ctx){
        String type = "var";
        for (TerminalNode idNode : ctx.ID()) {
            String variable = idNode.getText();
            declareVariable(variable, type);
        }
        return null;

    }
    private void checkVariable(String variable) {
        if (!symbolTable.containsKey(variable)) {
            // Undeclared variable error
            System.err.println("Error: Undeclared variable '" + variable + "'");
        }
    }
    private void declareVariable(String variable, String type) {
        if (symbolTable.containsKey(variable)) {
            // Variable redeclaration error
            System.err.println("Error: Variable '" + variable + "' redeclaration");
        } else {
            symbolTable.put(variable, type);
        }
    }



    @Override
    public String visitAssignmentStatement(pl0Parser.AssignmentStatementContext ctx) {

        String variable = ctx.ID().getText();
        checkVariable(variable);
        String value = visit(ctx.expression());

        System.out.println(variable + " = " + value);
        return null;
    }

    @Override
    public String visitExpression(pl0Parser.ExpressionContext ctx) {
        if (ctx.children.size() == 1) {
            // Single term
            return visit(ctx.term());
        }
        else if(ctx.children.size() == 2){
            String op=ctx.plusminusOP().getText();
            String right = visit(ctx.term());
            String tempVar = newTempVar();
            System.out.println(tempVar + " = " + op + " " + right);
            String result = tempVar;
            return result;

        }
        else{
                String left=visit(ctx.expression());
                String op=ctx.plusminusOP().getText();
                String right=visit(ctx.term());
                String tempVar = newTempVar();
                System.out.println(tempVar + " = " + left + " " + op + " " + right);
                return tempVar;
            }

    }

    @Override
    public String visitTerm(pl0Parser.TermContext ctx) {
        if (ctx.children.size() == 1) {
            // Single factor
            return visit(ctx.factor());
        } else {
            String left = visit(ctx.term());
            String op=ctx.multdivOP().getText();
            String right=visit(ctx.factor());
            String tempVar = newTempVar();
            System.out.println(tempVar + " = " + left + " " + op + " " + right);
            return tempVar;

        }
    }

    @Override
    public String visitFactor(pl0Parser.FactorContext ctx) {
        if (ctx.ID() != null) {

            String variable = ctx.ID().getText();
            checkVariable(variable); // Add a check for the variable in the symbol table
            return variable;
        } else if(ctx.INT() != null){
            return ctx.INT().getText();
        }else{
            return visit(ctx.expression());

        }
    }

    @Override
    public String visitIfStatement(pl0Parser.IfStatementContext ctx) {
        String condition = visit(ctx.condition());
        String labelElse = newLabel();
        String labelEnd = newLabel();

        System.out.println("if " + condition + " goto " + labelElse);
        //visit(ctx.statement()); // Visit the true branch
        System.out.println("goto " + labelEnd);
        System.out.println(labelElse + ":");
        if (ctx.statement() != null) {
            visit(ctx.statement()); // Visit the false branch if it exists
        }
        System.out.println(labelEnd + ":");
        return null;
    }


    @Override
    public String visitWhileStatement(pl0Parser.WhileStatementContext ctx) {
        String labelStart = newLabel();
        String labelMiddle = newLabel();
        String labelEnd = newLabel();

        System.out.println(labelStart + ":");
        String condition = visit(ctx.condition());
        System.out.println("if " + condition + " goto " + labelMiddle);
        System.out.println("goto " + labelEnd);
        System.out.println(labelMiddle + ":");
        visit(ctx.statement());
        System.out.println("goto " + labelStart);
        System.out.println(labelEnd + ":");
        return null;
    }

    @Override
    public String visitCondition(pl0Parser.ConditionContext ctx) {
        String left = visit(ctx.expression(0));
        String right = visit(ctx.expression(1));
        String relationalOp = ctx.relationalOp().getText();
        return left + " " + relationalOp + " " + right;
    }
    @Override
    public String visitCompoundStatement(pl0Parser.CompoundStatementContext ctx) {
        visit(ctx.statement(0)); // Visit the first statement in the compound statement

        int numStatements = ctx.statement().size();
        for (int i = 1; i < numStatements; i++) {
            visit(ctx.statement(i));
        }

        return null;
    }
    public void printSymbolTable() {
        System.out.println("\n========================");
        System.out.println("Symbol Table:");
        for (Map.Entry<String, String> entry : symbolTable.entrySet()) {
            System.out.println(entry.getKey() + " : " + entry.getValue());
        }
    }

    // Add other visit methods as needed for different grammar rules

}