package operators;

import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

public abstract class AbstractUnaryLogicalExpression implements Expression {
    private final Expression expression;
    protected final Set<Variable> freeVars = new HashSet<>();
    protected final Set<Variable> boundVars = new HashSet<>();
    protected final Set<Variable> usedVars = new HashSet<>();

    public AbstractUnaryLogicalExpression(Expression expression) {
        this.expression = expression;
        expression.getFreeVars().forEach(var -> {
            if (!boundVars.contains(var)) {
                freeVars.add(var);
            }
        });
        usedVars.addAll(expression.getUsedVars());
    }

    protected abstract String getSymbol();

    @Override
    public String toString() {
        return "(" + getSymbol() + expression + ")";
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

    @Override
    public void addBoundVar(Variable variable) {
        boundVars.add(variable);
        freeVars.remove(variable);
        expression.addBoundVar(variable);
    }

    @Override
    public Set<Variable> getUsedVars() {
        return usedVars;
    }

    @Override
    public Set<Variable> getFreeVars() {
        return freeVars;
    }

    @Override
    public Set<Variable> getBoundVars() {
        return boundVars;
    }
}
