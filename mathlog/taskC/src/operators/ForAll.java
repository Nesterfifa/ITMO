package operators;

public class ForAll extends AbstractQuantifier {
    public ForAll(Expression expression, Variable variable) {
        super(expression, variable);
    }

    @Override
    protected String getSymbol() {
        return "@";
    }
}
