package operators;

public class And extends AbstractBinaryLogicalExpression {
    public And(Expression left, Expression right) {
        super(left, right);
    }

    @Override
    protected int getPriority() {
        return 3;
    }

    @Override
    protected String getSymbol() {
        return "&";
    }

    @Override
    protected boolean isRightAssociative() {
        return false;
    }
}
