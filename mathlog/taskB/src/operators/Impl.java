package operators;

public class Impl extends AbstractBinaryLogicalExpression {
    public Impl(Expression left, Expression right) {
        super(left, right);
    }

    @Override
    protected int getPriority() {
        return 1;
    }

    @Override
    protected String getSymbol() {
        return "->";
    }

    @Override
    protected boolean isRightAssociative() {
        return true;
    }
}
