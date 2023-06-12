package operators;

public class Or extends AbstractBinaryLogicalExpression {
    public Or(Expression left, Expression right) {
        super(left, right);
    }

    @Override
    protected int getPriority() {
        return 2;
    }

    @Override
    protected String getSymbol() {
        return "|";
    }

    @Override
    protected boolean isRightAssociative() {
        return false;
    }
}
