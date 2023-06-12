package parser;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class BaseParser {
    private final char end;
    private final CharSource source;
    protected char ch = 0xffff;

    protected BaseParser(char end, final CharSource source) {
        this.end = end;
        this.source = source;
    }

    protected void nextChar() {
        ch = source.hasNext() ? source.next() : end;
    }

    protected boolean test(char expected) {
        if (ch == expected) {
            nextChar();
            return true;
        }
        return false;
    }

    protected void expect(final char c) {
        if (ch != c) {
            throw error("Expected '" + c + "', found '" + ch + "'");
        }
        nextChar();
    }

    protected void expect(final String value) {
        for (char c : value.toCharArray()) {
            expect(c);
        }
    }

    protected boolean eof() {
        return test(end);
    }

    protected ParseException error(final String message) {
        return source.error(message);
    }

    protected boolean between(final char from, final char to) {
        return from <= ch && ch <= to;
    }
}
