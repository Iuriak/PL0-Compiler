// Generated from E:/������/BYYL/src/pl0.g4 by ANTLR 4.13.1
package pl0;
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue", "this-escape"})
public class pl0Lexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		PROGRAM=1, BEGIN=2, END=3, CONST=4, VAR=5, WHILE=6, DO=7, IF=8, THEN=9, 
		ID=10, INT=11, PLUS=12, MINUS=13, MULT=14, DIV=15, ASSIGN=16, EQ=17, NEQ=18, 
		GT=19, GTE=20, LT=21, LTE=22, LPAREN=23, RPAREN=24, SEMI=25, COMMA=26, 
		WS=27, COMMENT=28;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"PROGRAM", "BEGIN", "END", "CONST", "VAR", "WHILE", "DO", "IF", "THEN", 
			"ID", "INT", "PLUS", "MINUS", "MULT", "DIV", "ASSIGN", "EQ", "NEQ", "GT", 
			"GTE", "LT", "LTE", "LPAREN", "RPAREN", "SEMI", "COMMA", "WS", "COMMENT"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'PROGRAM'", "'BEGIN'", "'END'", "'CONST'", "'VAR'", "'WHILE'", 
			"'DO'", "'IF'", "'THEN'", null, null, "'+'", "'-'", "'*'", "'/'", "':='", 
			"'='", "'<>'", "'>'", "'>='", "'<'", "'<='", "'('", "')'", "';'", "','"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "PROGRAM", "BEGIN", "END", "CONST", "VAR", "WHILE", "DO", "IF", 
			"THEN", "ID", "INT", "PLUS", "MINUS", "MULT", "DIV", "ASSIGN", "EQ", 
			"NEQ", "GT", "GTE", "LT", "LTE", "LPAREN", "RPAREN", "SEMI", "COMMA", 
			"WS", "COMMENT"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public pl0Lexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "pl0.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\u0004\u0000\u001c\u00a6\u0006\uffff\uffff\u0002\u0000\u0007\u0000\u0002"+
		"\u0001\u0007\u0001\u0002\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002"+
		"\u0004\u0007\u0004\u0002\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002"+
		"\u0007\u0007\u0007\u0002\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002"+
		"\u000b\u0007\u000b\u0002\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e"+
		"\u0002\u000f\u0007\u000f\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011"+
		"\u0002\u0012\u0007\u0012\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014"+
		"\u0002\u0015\u0007\u0015\u0002\u0016\u0007\u0016\u0002\u0017\u0007\u0017"+
		"\u0002\u0018\u0007\u0018\u0002\u0019\u0007\u0019\u0002\u001a\u0007\u001a"+
		"\u0002\u001b\u0007\u001b\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000"+
		"\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0002\u0001\u0002"+
		"\u0001\u0002\u0001\u0002\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0001\u0003\u0001\u0003\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0007\u0001\u0007\u0001\u0007"+
		"\u0001\b\u0001\b\u0001\b\u0001\b\u0001\b\u0001\t\u0001\t\u0005\ti\b\t"+
		"\n\t\f\tl\t\t\u0001\n\u0004\no\b\n\u000b\n\f\np\u0001\u000b\u0001\u000b"+
		"\u0001\f\u0001\f\u0001\r\u0001\r\u0001\u000e\u0001\u000e\u0001\u000f\u0001"+
		"\u000f\u0001\u000f\u0001\u0010\u0001\u0010\u0001\u0011\u0001\u0011\u0001"+
		"\u0011\u0001\u0012\u0001\u0012\u0001\u0013\u0001\u0013\u0001\u0013\u0001"+
		"\u0014\u0001\u0014\u0001\u0015\u0001\u0015\u0001\u0015\u0001\u0016\u0001"+
		"\u0016\u0001\u0017\u0001\u0017\u0001\u0018\u0001\u0018\u0001\u0019\u0001"+
		"\u0019\u0001\u001a\u0004\u001a\u0096\b\u001a\u000b\u001a\f\u001a\u0097"+
		"\u0001\u001a\u0001\u001a\u0001\u001b\u0001\u001b\u0001\u001b\u0001\u001b"+
		"\u0005\u001b\u00a0\b\u001b\n\u001b\f\u001b\u00a3\t\u001b\u0001\u001b\u0001"+
		"\u001b\u0000\u0000\u001c\u0001\u0001\u0003\u0002\u0005\u0003\u0007\u0004"+
		"\t\u0005\u000b\u0006\r\u0007\u000f\b\u0011\t\u0013\n\u0015\u000b\u0017"+
		"\f\u0019\r\u001b\u000e\u001d\u000f\u001f\u0010!\u0011#\u0012%\u0013\'"+
		"\u0014)\u0015+\u0016-\u0017/\u00181\u00193\u001a5\u001b7\u001c\u0001\u0000"+
		"\u0005\u0003\u0000AZ__az\u0004\u000009AZ__az\u0001\u000009\u0003\u0000"+
		"\t\n\r\r  \u0002\u0000\n\n\r\r\u00a9\u0000\u0001\u0001\u0000\u0000\u0000"+
		"\u0000\u0003\u0001\u0000\u0000\u0000\u0000\u0005\u0001\u0000\u0000\u0000"+
		"\u0000\u0007\u0001\u0000\u0000\u0000\u0000\t\u0001\u0000\u0000\u0000\u0000"+
		"\u000b\u0001\u0000\u0000\u0000\u0000\r\u0001\u0000\u0000\u0000\u0000\u000f"+
		"\u0001\u0000\u0000\u0000\u0000\u0011\u0001\u0000\u0000\u0000\u0000\u0013"+
		"\u0001\u0000\u0000\u0000\u0000\u0015\u0001\u0000\u0000\u0000\u0000\u0017"+
		"\u0001\u0000\u0000\u0000\u0000\u0019\u0001\u0000\u0000\u0000\u0000\u001b"+
		"\u0001\u0000\u0000\u0000\u0000\u001d\u0001\u0000\u0000\u0000\u0000\u001f"+
		"\u0001\u0000\u0000\u0000\u0000!\u0001\u0000\u0000\u0000\u0000#\u0001\u0000"+
		"\u0000\u0000\u0000%\u0001\u0000\u0000\u0000\u0000\'\u0001\u0000\u0000"+
		"\u0000\u0000)\u0001\u0000\u0000\u0000\u0000+\u0001\u0000\u0000\u0000\u0000"+
		"-\u0001\u0000\u0000\u0000\u0000/\u0001\u0000\u0000\u0000\u00001\u0001"+
		"\u0000\u0000\u0000\u00003\u0001\u0000\u0000\u0000\u00005\u0001\u0000\u0000"+
		"\u0000\u00007\u0001\u0000\u0000\u0000\u00019\u0001\u0000\u0000\u0000\u0003"+
		"A\u0001\u0000\u0000\u0000\u0005G\u0001\u0000\u0000\u0000\u0007K\u0001"+
		"\u0000\u0000\u0000\tQ\u0001\u0000\u0000\u0000\u000bU\u0001\u0000\u0000"+
		"\u0000\r[\u0001\u0000\u0000\u0000\u000f^\u0001\u0000\u0000\u0000\u0011"+
		"a\u0001\u0000\u0000\u0000\u0013f\u0001\u0000\u0000\u0000\u0015n\u0001"+
		"\u0000\u0000\u0000\u0017r\u0001\u0000\u0000\u0000\u0019t\u0001\u0000\u0000"+
		"\u0000\u001bv\u0001\u0000\u0000\u0000\u001dx\u0001\u0000\u0000\u0000\u001f"+
		"z\u0001\u0000\u0000\u0000!}\u0001\u0000\u0000\u0000#\u007f\u0001\u0000"+
		"\u0000\u0000%\u0082\u0001\u0000\u0000\u0000\'\u0084\u0001\u0000\u0000"+
		"\u0000)\u0087\u0001\u0000\u0000\u0000+\u0089\u0001\u0000\u0000\u0000-"+
		"\u008c\u0001\u0000\u0000\u0000/\u008e\u0001\u0000\u0000\u00001\u0090\u0001"+
		"\u0000\u0000\u00003\u0092\u0001\u0000\u0000\u00005\u0095\u0001\u0000\u0000"+
		"\u00007\u009b\u0001\u0000\u0000\u00009:\u0005P\u0000\u0000:;\u0005R\u0000"+
		"\u0000;<\u0005O\u0000\u0000<=\u0005G\u0000\u0000=>\u0005R\u0000\u0000"+
		">?\u0005A\u0000\u0000?@\u0005M\u0000\u0000@\u0002\u0001\u0000\u0000\u0000"+
		"AB\u0005B\u0000\u0000BC\u0005E\u0000\u0000CD\u0005G\u0000\u0000DE\u0005"+
		"I\u0000\u0000EF\u0005N\u0000\u0000F\u0004\u0001\u0000\u0000\u0000GH\u0005"+
		"E\u0000\u0000HI\u0005N\u0000\u0000IJ\u0005D\u0000\u0000J\u0006\u0001\u0000"+
		"\u0000\u0000KL\u0005C\u0000\u0000LM\u0005O\u0000\u0000MN\u0005N\u0000"+
		"\u0000NO\u0005S\u0000\u0000OP\u0005T\u0000\u0000P\b\u0001\u0000\u0000"+
		"\u0000QR\u0005V\u0000\u0000RS\u0005A\u0000\u0000ST\u0005R\u0000\u0000"+
		"T\n\u0001\u0000\u0000\u0000UV\u0005W\u0000\u0000VW\u0005H\u0000\u0000"+
		"WX\u0005I\u0000\u0000XY\u0005L\u0000\u0000YZ\u0005E\u0000\u0000Z\f\u0001"+
		"\u0000\u0000\u0000[\\\u0005D\u0000\u0000\\]\u0005O\u0000\u0000]\u000e"+
		"\u0001\u0000\u0000\u0000^_\u0005I\u0000\u0000_`\u0005F\u0000\u0000`\u0010"+
		"\u0001\u0000\u0000\u0000ab\u0005T\u0000\u0000bc\u0005H\u0000\u0000cd\u0005"+
		"E\u0000\u0000de\u0005N\u0000\u0000e\u0012\u0001\u0000\u0000\u0000fj\u0007"+
		"\u0000\u0000\u0000gi\u0007\u0001\u0000\u0000hg\u0001\u0000\u0000\u0000"+
		"il\u0001\u0000\u0000\u0000jh\u0001\u0000\u0000\u0000jk\u0001\u0000\u0000"+
		"\u0000k\u0014\u0001\u0000\u0000\u0000lj\u0001\u0000\u0000\u0000mo\u0007"+
		"\u0002\u0000\u0000nm\u0001\u0000\u0000\u0000op\u0001\u0000\u0000\u0000"+
		"pn\u0001\u0000\u0000\u0000pq\u0001\u0000\u0000\u0000q\u0016\u0001\u0000"+
		"\u0000\u0000rs\u0005+\u0000\u0000s\u0018\u0001\u0000\u0000\u0000tu\u0005"+
		"-\u0000\u0000u\u001a\u0001\u0000\u0000\u0000vw\u0005*\u0000\u0000w\u001c"+
		"\u0001\u0000\u0000\u0000xy\u0005/\u0000\u0000y\u001e\u0001\u0000\u0000"+
		"\u0000z{\u0005:\u0000\u0000{|\u0005=\u0000\u0000| \u0001\u0000\u0000\u0000"+
		"}~\u0005=\u0000\u0000~\"\u0001\u0000\u0000\u0000\u007f\u0080\u0005<\u0000"+
		"\u0000\u0080\u0081\u0005>\u0000\u0000\u0081$\u0001\u0000\u0000\u0000\u0082"+
		"\u0083\u0005>\u0000\u0000\u0083&\u0001\u0000\u0000\u0000\u0084\u0085\u0005"+
		">\u0000\u0000\u0085\u0086\u0005=\u0000\u0000\u0086(\u0001\u0000\u0000"+
		"\u0000\u0087\u0088\u0005<\u0000\u0000\u0088*\u0001\u0000\u0000\u0000\u0089"+
		"\u008a\u0005<\u0000\u0000\u008a\u008b\u0005=\u0000\u0000\u008b,\u0001"+
		"\u0000\u0000\u0000\u008c\u008d\u0005(\u0000\u0000\u008d.\u0001\u0000\u0000"+
		"\u0000\u008e\u008f\u0005)\u0000\u0000\u008f0\u0001\u0000\u0000\u0000\u0090"+
		"\u0091\u0005;\u0000\u0000\u00912\u0001\u0000\u0000\u0000\u0092\u0093\u0005"+
		",\u0000\u0000\u00934\u0001\u0000\u0000\u0000\u0094\u0096\u0007\u0003\u0000"+
		"\u0000\u0095\u0094\u0001\u0000\u0000\u0000\u0096\u0097\u0001\u0000\u0000"+
		"\u0000\u0097\u0095\u0001\u0000\u0000\u0000\u0097\u0098\u0001\u0000\u0000"+
		"\u0000\u0098\u0099\u0001\u0000\u0000\u0000\u0099\u009a\u0006\u001a\u0000"+
		"\u0000\u009a6\u0001\u0000\u0000\u0000\u009b\u009c\u0005/\u0000\u0000\u009c"+
		"\u009d\u0005/\u0000\u0000\u009d\u00a1\u0001\u0000\u0000\u0000\u009e\u00a0"+
		"\b\u0004\u0000\u0000\u009f\u009e\u0001\u0000\u0000\u0000\u00a0\u00a3\u0001"+
		"\u0000\u0000\u0000\u00a1\u009f\u0001\u0000\u0000\u0000\u00a1\u00a2\u0001"+
		"\u0000\u0000\u0000\u00a2\u00a4\u0001\u0000\u0000\u0000\u00a3\u00a1\u0001"+
		"\u0000\u0000\u0000\u00a4\u00a5\u0006\u001b\u0000\u0000\u00a58\u0001\u0000"+
		"\u0000\u0000\u0005\u0000jp\u0097\u00a1\u0001\u0006\u0000\u0000";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}