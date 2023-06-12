package operators;

public class Next extends AbstractUnaryLogicalExpression {
    public Next(Expression expression) {
        super(expression);
    }

    @Override
    protected String getSymbol() {
        return "'";
    }

    @Override
    public String toString() {
        return getExpression() + getSymbol();
    }
}
