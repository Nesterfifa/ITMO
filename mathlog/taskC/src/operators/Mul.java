package operators;

public class Mul extends AbstractBinaryLogicalExpression {
    public Mul(Expression left, Expression right) {
        super(left, right);
    }

    @Override
    protected String getSymbol() {
        return "*";
    }
}
