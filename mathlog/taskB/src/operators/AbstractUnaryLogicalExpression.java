package operators;

import java.util.Objects;

public abstract class AbstractUnaryLogicalExpression implements Expression {
    private final Expression expression;

    public AbstractUnaryLogicalExpression(Expression expression) {
        this.expression = expression;
    }

    protected abstract String getSymbol();

    @Override
    public String toString() {
        return getSymbol() + expression;
    }

    public String toPrefixString() {
        return "(" + getSymbol() + expression.toPrefixString() + ")";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        AbstractUnaryLogicalExpression that = (AbstractUnaryLogicalExpression) o;
        return Objects.equals(expression, that.expression);
    }

    @Override
    public int hashCode() {
        return Objects.hash(expression);
    }

    public Expression getExpression() {
        return expression;
    }
}
