package expression;

public class BinaryArithmeticExpression implements ArithmeticExpression {
    private final ArithmeticExpression left;
    private final ArithmeticExpression right;
    private final String symbol;

    public BinaryArithmeticExpression(ArithmeticExpression left, ArithmeticExpression right, String symbol) {
        this.left = left;
        this.right = right;
        this.symbol = symbol;
    }

    @Override
    public String toString() {
        return String.format("(%s %s %s)", left.toString(), symbol, right.toString());
    }
}
