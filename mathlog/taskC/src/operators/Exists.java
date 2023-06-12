package operators;

public class Exists extends AbstractQuantifier {
    public Exists(Expression expression, Variable variable) {
        super(expression, variable);
    }

    @Override
    protected String getSymbol() {
        return "?";
    }
}
