package parser;

import java.util.Map;

public enum UnaryOperator implements Operator {
    Not, ForAll, Exists;

    private static final Map<UnaryOperator, String> SYMBOLS = Map.of(
            Not, "!",
            ForAll, "@",
            Exists, "?"
    );

    @Override
    public String toString() {
        return SYMBOLS.get(this);
    }
}
