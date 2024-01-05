//import pl0.Mypl0Listener;
import pl0.pl0VisitorImpl;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import pl0.pl0Lexer;
import pl0.pl0Parser;
import pl0.pl0BaseVisitor;

public class Main {
    public static void main(String[] args) {

        pl0Lexer lexer = new pl0Lexer(CharStreams.fromString("PROGRAM add\n" +
                "VAR x,y;\n" +
                "BEGIN\n" +
                "x:=1;\n" +
                "y:=2;\n" +
                "WHILE x<5 DO x:=x+1;\n" +
                "y:=3;\n"+
                "IF y>0 THEN y:=y-1;\n" +
                "y:=y+x\n" +
                "END\n"));
        pl0Parser parser = new pl0Parser((new CommonTokenStream(lexer)));
        //parser.start();
        parser.setBuildParseTree(true);
        pl0Parser.ProgramContext tree = parser.program();
        pl0VisitorImpl visitor = new pl0VisitorImpl();
        visitor.visit(tree);
        visitor.printSymbolTable();


        //Mypl0Listener listener = new Mypl0Listener();

        // 注册Listener
        //parser.addParseListener(listener);

        // 开始解析
        //parser.program();
        //listener.printVariableValues();
        System.out.println("parser has executed");

    }
}