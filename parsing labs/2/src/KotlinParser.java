import java.io.InputStream;
import java.text.ParseException;

public class KotlinParser {
    private LexicalAnalyzer lex;
    private String token;

    private Tree S() throws ParseException {
        if (lex.curToken() == Token.FUN) {
            token = lex.nextToken();
            return new Tree("S", new Tree("fun"), N());
        } else {
            throw new ParseException("`fun` expected at pos " + lex.curPos(), lex.curPos());
        }
    }

    private Tree N() throws ParseException {
        if (lex.curToken() == Token.NAME) {
            String name = token;
            token = lex.nextToken();
            if (lex.curToken() != Token.LPAREN) {
                throw new ParseException("`(` expected at pos " + lex.curPos(), lex.curPos());
            }
            token = lex.nextToken();
            Tree p = P();
            if (lex.curToken() != Token.RPAREN) {
                throw new ParseException("`)` expected at pos " + lex.curPos(), lex.curPos());
            }
            token = lex.nextToken();
            Tree t = T();
            if (lex.curToken() != Token.END) {
                throw new ParseException("Eof expected at pos " + lex.curPos(), lex.curPos());
            }
            return new Tree("N", new Tree(name), new Tree("LPAREN"), p, new Tree("RPAREN"), t);
        }
        throw new ParseException("Expression expected at pos " + lex.curPos(), lex.curPos());
    }

    private Tree P() throws ParseException {
        if (lex.curToken() == Token.RPAREN) {
            return new Tree("P", new Tree("eps"));
        } else if (lex.curToken() == Token.NAME) {
            Tree pp = PPrime();
            Tree c = C();
            return new Tree("P", pp, c);
        }
        throw new ParseException("Unexpected token at pos " + lex.curPos(), lex.curPos());
    }

    private Tree PPrime() throws ParseException {
        String name = token;
        token = lex.nextToken();
        if (lex.curToken() != Token.COLON) {
            throw new ParseException("`:` expected at pos " + lex.curPos(), lex.curPos());
        }
        token = lex.nextToken();
        Tree g = G();
        return new Tree("PPrime", new Tree(name), new Tree("COLON"), g);
    }

    private Tree C() throws ParseException {
        if (lex.curToken() != Token.COMMA && lex.curToken() != Token.RPAREN) {
            throw new ParseException("',' or ')' expected at pos " + lex.curPos(), lex.curPos());
        }
        if (lex.curToken() == Token.RPAREN) {
            return new Tree("C", new Tree("eps"));
        }
        token = lex.nextToken();
        Tree pp = PPrime();
        Tree c = C();
        return new Tree("C", new Tree("COMMA"), pp, c);
    }

    private Tree T() throws ParseException {
        if (lex.curToken() == Token.END) {
            return new Tree("T", new Tree("eps"));
        }
        if (lex.curToken() != Token.COLON) {
            throw new ParseException("`:` expected at pos " + lex.curPos(), lex.curPos());
        }
        token = lex.nextToken();
        Tree g = G();
        if (lex.curToken() != Token.END) {
            throw new ParseException("Eof expected at pos " + lex.curPos(), lex.curPos());
        }
        return new Tree("T", g);
    }

    private Tree G() throws ParseException {
        if (lex.curToken() != Token.NAME) {
            throw new ParseException("Expression expected at pos " + lex.curPos(), lex.curPos());
        }
        String typeName = token;
        token = lex.nextToken();
        return new Tree("G", new Tree(typeName), GPrime());
    }

    private Tree GPrime() throws ParseException {
        if (lex.curToken() != Token.LTRIANG) {
            return new Tree("GPrime", new Tree("eps"));
        }
        token = lex.nextToken();
        Tree g = G();
        if (lex.curToken() != Token.RTRIANG) {
            throw new ParseException("'>' expected at pos " + lex.curPos(), lex.curPos());
        }
        token = lex.nextToken();
        return new Tree("GPrime", new Tree("LTRIANG"), g, new Tree("RTRIANG"));
    }

    public Tree parse(InputStream is) throws ParseException {
        lex = new LexicalAnalyzer(is);
        token = lex.nextToken();
        return S();
    }
}
