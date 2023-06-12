package operators;

public class Equal extends AbstractBinaryLogicalExpression {
    public Equal(Expression left, Expression right) {
        super(left, right);
    }

    @Override
    protected String getSymbol() {
        return "=";
    }
}
