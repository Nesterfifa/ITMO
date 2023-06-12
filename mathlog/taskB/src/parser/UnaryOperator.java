package parser;

import java.util.Map;

public enum UnaryOperator implements Operator {
    Not;

    private static final Map<UnaryOperator, String> SYMBOLS = Map.of(
            Not, "!"
    );

    @Override
    public String toString() {
        return SYMBOLS.get(this);
    }
}
