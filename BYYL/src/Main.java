//import pl0.Mypl0Listener;
import pl0.pl0VisitorImpl;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import pl0.pl0Lexer;
import pl0.pl0Parser;
import pl0.pl0BaseVisitor;

public class Main {
    public static void main(String[] args) {

        pl0Lexer lexer = new pl0Lexer(CharStreams.fromString("PROGRAM ArithmeticTest\n" +
                "CONST d :=2;\n"+
                "VAR a, b, c;\n" +

                "BEGIN\n" +
                "    a := 5;\n" +
                "    b := +2;\n" +
                "    c := (a + b) * 2;\n" +
                "    c := c / 2\n" +
                "END"));
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