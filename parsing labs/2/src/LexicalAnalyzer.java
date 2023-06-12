import java.io.IOException;
import java.io.InputStream;
import java.text.ParseException;

public class LexicalAnalyzer {
    private final InputStream is;
    private int curChar;
    private int curPos;
    private Token curToken;

    public LexicalAnalyzer(InputStream is) throws ParseException {
        this.is = is;
        curPos = 0;
        nextChar();
    }

    private boolean isBlank(int c) {
        return Character.isWhitespace(c);
    }

    private void nextChar() throws ParseException {
        curPos++;
        try {
            curChar = is.read();
        } catch (IOException e) {
            throw new ParseException(e.getMessage(), curPos);
        }
    }

    public String nextToken() throws ParseException {
        while (isBlank(curChar)) {
            nextChar();
        }

        switch (curChar) {
            case '(':
                nextChar();
                curToken = Token.LPAREN;
                return "(";
            case ')':
                nextChar();
                curToken = Token.RPAREN;
                return ")";
            case ':':
                nextChar();
                curToken = Token.COLON;
                return ":";
            case ',':
                nextChar();
                curToken = Token.COMMA;
                return ",";
            case '<':
                nextChar();
                curToken = Token.LTRIANG;
                return "<";
            case '>':
                nextChar();
                curToken = Token.RTRIANG;
                return ">";
            case -1:
                curToken = Token.END;
                return "";
            default:
                if (!Character.isAlphabetic(curChar)) {
                    throw new ParseException("Invalid token at pos ", curPos);
                }
                StringBuilder token = new StringBuilder();
                while (Character.isAlphabetic(curChar) || Character.isDigit(curChar) || curChar == '_') {
                    token.append(Character.toChars(curChar));
                    nextChar();
                }
                if (token.toString().equals("fun")) {
                    curToken = Token.FUN;
                } else {
                    curToken = Token.NAME;
                }
                return token.toString();
        }
    }

    public Token curToken() {
        return curToken;
    }

    public int curPos() {
        return curPos;
    }
}
