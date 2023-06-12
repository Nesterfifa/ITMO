package operators;

public class Not extends AbstractUnaryLogicalExpression {
    public Not(Expression expression) {
        super(expression);
    }

    @Override
    protected String getSymbol() {
        return "!";
    }
}
