package operators;

public class Or extends AbstractBinaryLogicalExpression {
    public Or(Expression left, Expression right) {
        super(left, right);
    }

    @Override
    protected String getSymbol() {
        return "|";
    }
}
