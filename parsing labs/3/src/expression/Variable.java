package expression;

public class Variable implements ArithmeticExpression {
    private final String name;

    public Variable(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return name;
    }
}
