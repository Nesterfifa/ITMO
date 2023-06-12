package operators;

public class Add extends AbstractBinaryLogicalExpression{
    public Add(Expression left, Expression right) {
        super(left, right);
    }

    @Override
    protected String getSymbol() {
        return "+";
    }
}
