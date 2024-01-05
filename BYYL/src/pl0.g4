grammar pl0;

// 词法规则
PROGRAM : 'PROGRAM';
BEGIN   : 'BEGIN';
END     : 'END';
CONST   : 'CONST';
VAR     : 'VAR';
WHILE   : 'WHILE';
DO      : 'DO';
IF      : 'IF';
THEN    : 'THEN';

ID      : [a-zA-Z_] [a-zA-Z0-9_]*;
INT     : [0-9]+;

PLUS    : '+';
MINUS   : '-';
MULT    : '*';
DIV     : '/';
ASSIGN  : ':=';
EQ      : '=';
NEQ     : '<>';
GT      : '>';
GTE     : '>=';
LT      : '<';
LTE     : '<=';
LPAREN  : '(';
RPAREN  : ')';
SEMI    : ';';
COMMA   : ',';

WS      : [ \t\r\n]+ -> skip;
COMMENT : '//' ~[\r\n]* -> skip;

// 语法规则
program : programHeader subProgram;
programHeader : PROGRAM ID;
subProgram : (constSection)? (varSection)? statement;

constSection : CONST constDefinition (COMMA constDefinition)* SEMI;
constDefinition : ID ASSIGN INT;

varSection : VAR ID (COMMA ID)* SEMI;

statement : compoundStatement | assignmentStatement | ifStatement | whileStatement | emptyStatement;

compoundStatement : BEGIN statement (SEMI statement )* END;

assignmentStatement : ID ASSIGN expression;

expression : (plusminusOP)?term|expression plusminusOP term;

plusminusOP: PLUS | MINUS;

term : factor|term multdivOP factor;

multdivOP: MULT | DIV;

factor : ID | INT | LPAREN expression RPAREN;


ifStatement : IF condition THEN statement;

whileStatement : WHILE condition DO statement;

condition : expression relationalOp expression;

relationalOp : EQ | NEQ | LT | LTE | GT | GTE;

emptyStatement : SEMI;
