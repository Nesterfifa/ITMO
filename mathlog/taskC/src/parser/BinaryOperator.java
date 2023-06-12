package parser;

import java.util.Map;

public enum BinaryOperator implements Operator {
    And, Or, Impl, Add, Mul, Equal;

    private static final Map<BinaryOperator, String> SYMBOLS = Map.of(
            And, "&",
            Or, "|",
            Impl, "->",
            Add, "+",
            Mul, "*",
            Equal, "="
    );

    private static final Map<BinaryOperator, Integer> PRIORITIES = Map.of(
            Mul, 5,
            Add, 4,
            Equal, 3,
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
