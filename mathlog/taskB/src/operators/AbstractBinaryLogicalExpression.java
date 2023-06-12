package operators;

import java.util.Objects;

public abstract class AbstractBinaryLogicalExpression implements Expression {
    private final Expression left;
    private final Expression right;

    protected AbstractBinaryLogicalExpression(Expression left, Expression right) {
        this.left = left;
        this.right = right;
    }

    protected abstract int getPriority();
    protected abstract String getSymbol();
    protected abstract boolean isRightAssociative();

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
}
