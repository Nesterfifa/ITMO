package operators;

public class And extends AbstractBinaryLogicalExpression {
    public And(Expression left, Expression right) {
        super(left, right);
    }

    @Override
    protected String getSymbol() {
        return "&";
    }
}
