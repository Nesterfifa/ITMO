import operators.*;
import parser.LogicalParser;
import parser.StringSource;

import java.util.*;

public class Main {
    public final static Variable FALSE = new Variable("_|_");
    private final static Map<Expression, Integer> hypothesis = new LinkedHashMap<>();
    private final static Set<Expression> proven = new HashSet<>();
    private final static Map<Expression, Set<Expression>> provenImplRightToLeft = new HashMap<>();
    private final static Map<Expression, Expression> modusPonensRightToLeft = new HashMap<>();

    private static boolean isAxiom(Expression expression) {
        return Util.isAxiomScheme(expression);
    }

    private static boolean isHypothesis(Expression expression) {
        return hypothesis.containsKey(expression);
    }

    private static Expression findModusPonens(Expression expression) {
        if (provenImplRightToLeft.containsKey(expression)) {
            for (Expression e : provenImplRightToLeft.get(expression)) {
                if (proven.contains(e)) {
                    return e;
                }
            }
        }
        return null;
    }

    private static Vertex deduct(Vertex start, int cnt) {
        start.setSymbol("[I->]");

        Vertex cur = start;
        Map<Expression, Integer> deductedHypo = new HashMap<>(cur.getHypothesis());
        while (cnt-- > 0) {
            Expression expression = cur.getExpression();
            deductedHypo.putIfAbsent(((Impl) expression).getLeft(), 0);
            deductedHypo.computeIfPresent(((Impl) expression).getLeft(), (k, v) -> v + 1);
            Expression right = ((Impl) expression).getRight();
            cur.getChildren().add(new Vertex(deductedHypo, right, "[I->]", new ArrayList<>(), cur.getLevel() + 1));
            cur = cur.getChildren().get(0);
        }

        if (cur.getHypothesis().containsKey(cur.getExpression())) {
            cur.setSymbol("[Ax]");
        }
        return cur;
    }

    private static void addSimpleNaturalMP(Vertex vertex, Map<Expression, Integer> hypo, Expression left, Expression right) {
        vertex.getChildren().add(new Vertex(hypo, right, "[E->]", List.of(
                new Vertex(hypo, new Impl(left, right), "[Ax]", new ArrayList<>(), vertex.getLevel() + 2),
                new Vertex(hypo, left, "[Ax]", new ArrayList<>(), vertex.getLevel() + 2)
        ), vertex.getLevel() + 1));
    }
    
    private static void solve(Vertex vertex) {
        if (vertex.getSymbol() == null) {
            Expression expression = vertex.getExpression();
            if (vertex.getHypothesis().containsKey(expression)) {
                vertex.setSymbol("[Ax]");
            } else if (modusPonensRightToLeft.containsKey(expression)) {
                Expression left = modusPonensRightToLeft.get(expression);
                vertex.getChildren().addAll(List.of(
                        new Vertex(hypothesis, new Impl(left, expression), null, new ArrayList<>(), vertex.getLevel() + 1),
                        new Vertex(hypothesis, left, null, new ArrayList<>(), vertex.getLevel() + 1)));
                vertex.setSymbol("[E->]");
            } else if (Util.isAxiomScheme1(expression)) {
                deduct(vertex, 2);
            } else if (Util.isAxiomScheme2(expression)) {
                Vertex deducted = deduct(vertex, 3);
                deducted.setSymbol("[E->]");
                Map<Expression, Integer> deductedHypo = new LinkedHashMap<>(deducted.getHypothesis());
                Expression alpha = ((Impl) ((Impl) expression).getLeft()).getLeft();
                Expression beta = ((Impl) ((Impl) expression).getLeft()).getRight();
                Expression gamma = ((Impl) ((Impl) ((Impl) expression).getRight()).getRight()).getRight();
                addSimpleNaturalMP(deducted, deductedHypo, alpha, new Impl(beta, gamma));
                addSimpleNaturalMP(deducted, deductedHypo, alpha, beta);
            } else if (Util.isAxiomScheme3(expression)) {
                Vertex deducted = deduct(vertex, 2);
                deducted.setSymbol("[I&]");
                Map<Expression, Integer> deductedHypo = new LinkedHashMap<>(deducted.getHypothesis());
                Expression alpha = ((Impl) expression).getLeft();
                Expression beta = ((Impl) ((Impl) expression).getRight()).getLeft();
                deducted.getChildren().add(new Vertex(deductedHypo, alpha, "[Ax]", new ArrayList<>(), deducted.getLevel() + 1));
                deducted.getChildren().add(new Vertex(deductedHypo, beta, "[Ax]", new ArrayList<>(), deducted.getLevel() + 1));
            } else if (Util.isAxiomScheme45(expression)) {
                Vertex deducted = deduct(vertex, 1);

                Expression alpha = ((And) ((Impl) expression).getLeft()).getLeft();
                Expression beta = ((And) ((Impl) expression).getLeft()).getRight();
                deducted.setSymbol(alpha.equals(((Impl) expression).getRight()) ? "[El&]" : "[Er&]");
                Map<Expression, Integer> deductedHypo = new LinkedHashMap<>(deducted.getHypothesis());
                deducted.getChildren().add(new Vertex(deductedHypo, new And(alpha, beta), "[Ax]", new ArrayList<>(), deducted.getLevel() + 1));
            } else if (Util.isAxiomScheme6(expression)) {
                Vertex deducted = deduct(vertex, 1);
                Expression left = ((Impl) expression).getLeft();
                deducted.setSymbol("[Il|]");
                Map<Expression, Integer> deductedHypo = new LinkedHashMap<>(deducted.getHypothesis());
                deducted.getChildren().add(new Vertex(deductedHypo, left, "[Ax]", new ArrayList<>(), deducted.getLevel() + 1));
            } else if (Util.isAxiomScheme7(expression)) {
                Vertex deducted = deduct(vertex, 1);
                Expression left = ((Impl) expression).getLeft();
                deducted.setSymbol("[Ir|]");
                Map<Expression, Integer> deductedHypo = new LinkedHashMap<>(deducted.getHypothesis());
                deducted.getChildren().add(new Vertex(deductedHypo, left, "[Ax]", new ArrayList<>(), deducted.getLevel() + 1));
            } else if (Util.isAxiomScheme8(expression)) {
                Vertex deducted = deduct(vertex, 3);

                Expression alpha = ((Impl) ((Impl) expression).getLeft()).getLeft();
                Expression gamma = ((Impl) ((Impl) expression).getLeft()).getRight();
                Expression beta = ((Impl) ((Impl) ((Impl) expression).getRight()).getLeft()).getLeft();
                deducted.setSymbol("[E|]");
                Map<Expression, Integer> deductedHypo = new LinkedHashMap<>(deducted.getHypothesis());
                deductedHypo.compute(alpha, (k, v) -> v == null ? 1 : v + 1);
                addSimpleNaturalMP(deducted, deductedHypo, alpha, gamma);
                deductedHypo.compute(alpha, (k, v) -> v - 1);
                deductedHypo.remove(alpha, 0);
                deductedHypo.compute(beta, (k, v) -> v == null ? 1 : v + 1);
                addSimpleNaturalMP(deducted, deductedHypo, beta, gamma);
                deductedHypo.compute(beta, (k, v) -> v - 1);
                deductedHypo.remove(beta, 0);
                deducted.getChildren().add(new Vertex(deductedHypo, new Or(alpha, beta), "[Ax]", new ArrayList<>(), deducted.getLevel() + 1));
            } else if (Util.isAxiomScheme9(expression)) {
                Expression alpha = ((Impl) ((Impl) expression).getLeft()).getLeft();
                Expression beta = ((Impl) ((Impl) expression).getLeft()).getRight();

                Vertex deducted = deduct(vertex, 3);

                deducted.setSymbol("[E->]");
                Map<Expression, Integer> deductedHypo = new LinkedHashMap<>(deducted.getHypothesis());
                addSimpleNaturalMP(deducted, deductedHypo, alpha, new Impl(beta, FALSE));
                addSimpleNaturalMP(deducted, deductedHypo, alpha, beta);
            } else if (Util.isAxiomScheme10(expression)) {
                Expression alpha = ((Impl) expression).getLeft();

                Vertex deducted = deduct(vertex, 2);

                deducted.setSymbol("[E_|_]");
                Map<Expression, Integer> deductedHypo = new LinkedHashMap<>(deducted.getHypothesis());
                addSimpleNaturalMP(deducted, deductedHypo, alpha, FALSE);
            }
        }

        for (Vertex u : vertex.getChildren()) {
            solve(u);
        }
        System.out.println(vertex);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String[] header = scanner.nextLine().split("[|]-");
        if (!header[0].isEmpty()) {
            String[] hypothesisStrings = header[0].split(",");
            for (String e : hypothesisStrings) {
                Expression h = new LogicalParser('\0', new StringSource(e)).parse();
                hypothesis.putIfAbsent(h, 0);
                hypothesis.computeIfPresent(h, (k, v) -> v + 1);
            }
        }
        final Expression finalExpression = new LogicalParser('\0', new StringSource(header[1])).parse();

        int line = 2;
        while (scanner.hasNextLine()) {
            Expression proofStage = new LogicalParser('\0', new StringSource(scanner.nextLine())).parse();
            if (isAxiom(proofStage) || isHypothesis(proofStage)) {
                proven.add(proofStage);
            } else {
                Expression left = findModusPonens(proofStage);
                if (left != null) {
                    proven.add(proofStage);
                    modusPonensRightToLeft.put(proofStage, left);
                } else {
                    System.out.println("Proof is incorrect at line " + line);
                    return;
                }
            }
            if (proofStage instanceof Impl) {
                provenImplRightToLeft.computeIfAbsent(
                        ((Impl) proofStage).getRight(),
                        x -> new HashSet<>(List.of(((Impl) proofStage).getLeft())));
                provenImplRightToLeft.get(((Impl) proofStage).getRight())
                        .add(((Impl) proofStage).getLeft());
            }
            if (!scanner.hasNextLine() && !proofStage.equals(finalExpression)) {
                System.out.println("The proof does not prove the required expression");
                return;
            }
            line++;
        }
        if (line == 2) {
            System.out.println("The proof does not prove the required expression");
            return;
        }

        solve(new Vertex(hypothesis, finalExpression, null, new ArrayList<>(), 0));
    }
}
