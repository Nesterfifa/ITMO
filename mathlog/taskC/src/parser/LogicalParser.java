package parser;

import operators.*;

import java.util.Map;

public class LogicalParser extends BaseParser {
    private static final Map<String, BinaryOperator> STRING_TO_BINARY_OP = Map.of(
            "+", BinaryOperator.Add,
            "*", BinaryOperator.Mul,
            "=", BinaryOperator.Equal,
            "&", BinaryOperator.And,
            "|", BinaryOperator.Or,
            "-", BinaryOperator.Impl
    );

    private static final Map<String, UnaryOperator> STRING_TO_UNARY_OP = Map.of(
            "!", UnaryOperator.Not,
            "@", UnaryOperator.ForAll,
            "?", UnaryOperator.Exists
    );

    private BinaryOperator lastBinaryOperator = null;
    private UnaryOperator lastUnaryOperator = null;

    public LogicalParser(final char end, final CharSource source) {
        super(end, source);
    }

    public Expression parse() {
        nextChar();
        return parseExpression(0);
    }

    private Expression parseExpression(final int priority) {
        if (priority == 6) {
            return parseSimpleExpression();
        }
        Expression result = parseExpression(priority + 1);
        while (hasPriorityBinaryOperation(priority)) {
            final BinaryOperator operator = lastBinaryOperator;
            lastBinaryOperator = null;
            if (operator == BinaryOperator.Impl) {
                result = makeBinaryOperation(operator, result, parseExpression(priority));
            } else {
                result = makeBinaryOperation(operator, result, parseExpression(priority + 1));
            }
        }
        while (test('\'')) {
            result = new Next(result);
        }
        return result;
    }

    private boolean hasPriorityBinaryOperation(final int level) {
        skipWhitespace();
        if (lastBinaryOperator == null) {
            StringBuilder builder = new StringBuilder().append(ch);
            while (STRING_TO_BINARY_OP.containsKey(builder.toString())) {
                nextChar();
                builder.append(ch);
            }
            builder.setLength(builder.length() - 1);
            lastBinaryOperator = STRING_TO_BINARY_OP.get(builder.toString());
            if (builder.length() > 0) {
                expect(lastBinaryOperator.toString().substring(builder.length()));
            }
        }
        return lastBinaryOperator != null && lastBinaryOperator.getPriority() == level;
    }

    private boolean hasUnaryOperation() {
        skipWhitespace();
        if (lastUnaryOperator == null) {
            StringBuilder builder = new StringBuilder().append(ch);
            while (STRING_TO_UNARY_OP.containsKey(builder.toString())) {
                nextChar();
                builder.append(ch);
            }
            builder.setLength(builder.length() - 1);
            lastUnaryOperator = STRING_TO_UNARY_OP.get(builder.toString());
            if (builder.length() > 0) {
                expect(lastUnaryOperator.toString().substring(builder.length()));
            }
        }
        return lastUnaryOperator != null;
    }

    private Expression parseSimpleExpression() {
        skipWhitespace();
        if (test('(')) {
            final Expression result = parseExpression(0);
            skipWhitespace();
            nextChar();
            return result;
        } else if (hasUnaryOperation()) {
            final UnaryOperator unaryOperator = lastUnaryOperator;
            lastUnaryOperator = null;
            if (unaryOperator.equals(UnaryOperator.ForAll) || unaryOperator.equals(UnaryOperator.Exists)) {
                final Variable quantifierVariable = (Variable) parseVariable();
                nextChar();
                return makeQuantifierOperation(unaryOperator, quantifierVariable, parseExpression(0));
            } else {
                return makeNot(parseExpression(3));
            }
        } else {
            return parseVariable();
        }
    }

    private Expression makeBinaryOperation(BinaryOperator operator, Expression a, Expression b) {
        switch (operator) {
            case Equal: return new Equal(a, b);
            case Mul: return new Mul(a, b);
            case Add: return new Add(a, b);
            case And: return new And(a, b);
            case Or: return new Or(a, b);
            case Impl: return new Impl(a, b);
            default: throw new ParseException("Unknown binary operator: " + operator);
        }
    }

    private Expression makeQuantifierOperation(UnaryOperator operator, Variable quantifierVariable, Expression e) {
        switch (operator) {
            case ForAll: return new ForAll(e, quantifierVariable);
            case Exists: return new Exists(e, quantifierVariable);
            default: throw new ParseException("Unknown unary operator: " + operator);
        }
    }

    private Expression makeNot(Expression expression) {
        return new Not(expression);
    }

    private Expression parseVariable() {
        final StringBuilder builder = new StringBuilder();
        while (between('a', 'z') || ch == '0' || between('A', 'Z')) {
            builder.append(ch);
            nextChar();
        }
        Expression result = new Variable(builder.toString());
        while (test('\'')) {
            result = new Next(result);
        }
        return result;
    }

    private void skipWhitespace() {
        while (test(' ') || test('\r') || test('\n') || test('\t')) {

        }
    }
}
