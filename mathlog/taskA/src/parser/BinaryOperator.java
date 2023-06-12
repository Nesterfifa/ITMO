package parser;

import java.util.Map;

public enum BinaryOperator implements Operator {
    And, Or, Impl;

    private static final Map<BinaryOperator, String> SYMBOLS = Map.of(
            And, "&",
            Or, "|",
            Impl, "->"
    );

    private static final Map<BinaryOperator, Integer> PRIORITIES = Map.of(
            And, 2,
            Or, 1,
            Impl, 0
    );

    public int getPriority() {
        return PRIORITIES.get(this);
    }

    @Override
    public String toString() {
        return SYMBOLS.get(this);
    }
}
