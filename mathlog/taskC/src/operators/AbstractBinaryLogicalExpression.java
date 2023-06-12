package operators;

import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

public abstract class AbstractBinaryLogicalExpression implements Expression {
    private final Expression left;
    private final Expression right;
    protected final Set<Variable> freeVars = new HashSet<>();
    protected final Set<Variable> boundVars = new HashSet<>();
    protected final Set<Variable> usedVars = new HashSet<>();

    protected AbstractBinaryLogicalExpression(Expression left, Expression right) {
        this.left = left;
        this.right = right;
        propagateFreeVars(left);
        propagateFreeVars(right);
    }

    protected abstract String getSymbol();

    public String toString() {
        return "(" + left + getSymbol() + right + ")";
    }

    public String toPrefixString() {
        return "(" + getSymbol() + "," + left.toPrefixString() + "," + right.toPrefixString() + ")";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        AbstractBinaryLogicalExpression that = (AbstractBinaryLogicalExpression) o;
        return Objects.equals(left, that.left) &&
                Objects.equals(right, that.right);
    }

    @Override
    public int hashCode() {
        return Objects.hash(left, right);
    }

    public Expression getLeft() {
        return left;
    }

    public Expression getRight() {
        return right;
    }

    @Override
    public void addBoundVar(Variable variable) {
        boundVars.add(variable);
        freeVars.remove(variable);
        left.addBoundVar(variable);
        right.addBoundVar(variable);
    }

    private void propagateFreeVars(Expression e) {
        e.getFreeVars().forEach(var -> {
            if (!boundVars.contains(var)) {
                freeVars.add(var);
            }
        });
        usedVars.addAll(e.getUsedVars());
    }

    @Override
    public Set<Variable> getUsedVars() {
        return usedVars;
    }

    public Set<Variable> getBoundVars() {
        return boundVars;
    }

    public Set<Variable> getFreeVars() {
        return freeVars;
    }
}
