import operators.Expression;

import java.util.List;
import java.util.Map;
import java.util.stream.IntStream;

public class Vertex {
    private final Map<Expression, Integer> hypothesis;
    private final List<Vertex> children;
    private final int level;
    private Expression expression;
    private String symbol = null;

    public Vertex(Map<Expression, Integer> hypothesis, Expression expression, String symbol, List<Vertex> children, int level) {
        this.hypothesis = Map.copyOf(hypothesis);
        this.expression = expression;
        this.symbol = symbol;
        this.children = children;
        this.level = level;
    }

    public Vertex(Vertex other) {
        hypothesis = Map.copyOf(other.hypothesis);
        expression = other.expression;
        symbol = other.symbol;
        children = List.copyOf(other.children);
        level = other.level;
    }

    public Expression getExpression() {
        return expression;
    }

    public Map<Expression, Integer> getHypothesis() {
        return hypothesis;
    }

    public String getSymbol() {
        return symbol;
    }

    public void setSymbol(String symbol) {
        this.symbol = symbol;
    }

    public void setExpression(Expression expression) {
        this.expression = expression;
    }

    public List<Vertex> getChildren() {
        return children;
    }

    public int getLevel() {
        return level;
    }

    @Override
    public String toString() {
        final StringBuilder builder = new StringBuilder().append("[").append(level).append("] ");
        hypothesis.forEach((e, cnt)
                -> IntStream.range(0, cnt).forEach(i -> builder.append(e.toString()).append(',')));
        if (builder.length() > 4) {
            builder.setLength(builder.length() - 1);
        }
        builder.append("|-").append(expression.toString()).append(" ").append(symbol);
        return builder.toString();
    }
}
