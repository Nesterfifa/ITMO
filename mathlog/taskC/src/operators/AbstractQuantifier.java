package operators;

import java.util.Objects;

public abstract class AbstractQuantifier extends AbstractUnaryLogicalExpression {
    private final Variable variable;

    public AbstractQuantifier(Expression expression, Variable variable) {
        super(expression);
        this.variable = variable;
        this.addBoundVar(variable);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        AbstractQuantifier that = (AbstractQuantifier) o;
        return Objects.equals(variable, that.variable);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), variable);
    }

    public Variable getVariable() {
        return variable;
    }

    @Override
    public String toString() {
        return "(" + getSymbol() + getVariable() + "." + getExpression() + ")";
    }
}
