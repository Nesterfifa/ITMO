package operators;

public class Impl extends AbstractBinaryLogicalExpression {
    public Impl(Expression left, Expression right) {
        super(left, right);
    }

    @Override
    protected String getSymbol() {
        return "->";
    }
}
