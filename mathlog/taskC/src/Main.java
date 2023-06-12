import operators.*;
import parser.LogicalParser;
import parser.StringSource;

import java.util.*;

public class Main {
    private final static List<Expression> expressionList = new ArrayList<>();
    private final static Map<Expression, Integer> expressionToIndex = new HashMap<>();
    private final static Set<Expression> proven = new HashSet<>();
    private final static Map<Expression, Set<Integer>> provenImplRightToLeft = new HashMap<>();

    static void annotateScheme(int number, String scheme, Expression proofStage) {
        System.out.println("[" + number + ". Ax. sch. " + scheme + "] " + proofStage);
    }

    static void annotateAx(int number, String axiom, Expression proofStage) {
        System.out.println("[" + number + ". Ax. " + axiom + "] " + proofStage);
    }

    static int[] findModusPonens(Expression e) {
        if (provenImplRightToLeft.containsKey(e)) {
            for (Integer left : provenImplRightToLeft.get(e)) {
                if (proven.contains(((AbstractBinaryLogicalExpression) expressionList.get(left)).getLeft())) {
                    return new int[] {
                            expressionToIndex.get(
                                    ((AbstractBinaryLogicalExpression) expressionList.get(left)).getLeft()),
                            left
                    };
                }
            }
        }
        return null;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Expression proving = new LogicalParser('\0', new StringSource(scanner.nextLine().substring(2))).parse();
        System.out.println("|-" + proving);
        int cnt = 1;
        expressionList.add(null);
        while (scanner.hasNextLine()) {
            Expression proofStage = new LogicalParser('\0', new StringSource(scanner.nextLine())).parse();
            final int[] mp = findModusPonens(proofStage);
            Object check11 = Util.isAxiomScheme11(proofStage);
            Object check12 = Util.isAxiomScheme12(proofStage);
            if (Util.isAxiomScheme1(proofStage)) {
                annotateScheme(cnt, "1", proofStage);
            } else if (Util.isAxiomScheme2(proofStage)) {
                annotateScheme(cnt, "2", proofStage);
            } else if (Util.isAxiomScheme3(proofStage)) {
                annotateScheme(cnt, "3", proofStage);
            } else if (Util.isAxiomScheme4(proofStage)) {
                annotateScheme(cnt, "4", proofStage);
            } else if (Util.isAxiomScheme5(proofStage)) {
                annotateScheme(cnt, "5", proofStage);
            } else if (Util.isAxiomScheme6(proofStage)) {
                annotateScheme(cnt, "6", proofStage);
            } else if (Util.isAxiomScheme7(proofStage)) {
                annotateScheme(cnt, "7", proofStage);
            } else if (Util.isAxiomScheme8(proofStage)) {
                annotateScheme(cnt, "8", proofStage);
            } else if (Util.isAxiomScheme9(proofStage)) {
                annotateScheme(cnt, "9", proofStage);
            } else if (Util.isAxiomScheme10(proofStage)) {
                annotateScheme(cnt, "10", proofStage);
            } else if (check11.equals(true)) {
                annotateScheme(cnt, "11", proofStage);
            } else if (check12.equals(true)) {
                annotateScheme(cnt, "12", proofStage);
            } else if (Util.isAxiom1(proofStage)) {
                annotateAx(cnt, "A1", proofStage);
            } else if (Util.isAxiom2(proofStage)) {
                annotateAx(cnt, "A2", proofStage);
            } else if (Util.isAxiom3(proofStage)) {
                annotateAx(cnt, "A3", proofStage);
            } else if (Util.isAxiom4(proofStage)) {
                annotateAx(cnt, "A4", proofStage);
            } else if (Util.isAxiom5(proofStage)) {
                annotateAx(cnt, "A5", proofStage);
            } else if (Util.isAxiom6(proofStage)) {
                annotateAx(cnt, "A6", proofStage);
            } else if (Util.isAxiom7(proofStage)) {
                annotateAx(cnt, "A7", proofStage);
            } else if (Util.isAxiom8(proofStage)) {
                annotateAx(cnt, "A8", proofStage);
            } else if (Util.isAxiomSchemeA9(proofStage)) {
                annotateScheme(cnt, "A9", proofStage);
            } else if (mp != null) {
                System.out.println("[" + cnt + ". M.P. " + mp[0] + ", " + mp[1] + "] " + proofStage);
            } else if (proofStage instanceof Impl
                    && ((Impl) proofStage).getLeft() instanceof Exists
                    && proven.contains(
                            new Impl(
                                    ((Exists) ((Impl) proofStage).getLeft()).getExpression(),
                                    ((Impl) proofStage).getRight()))) {
                if (!((Impl) proofStage).getRight().getFreeVars().contains(
                        ((Exists) ((Impl) proofStage).getLeft()).getVariable())) {
                    System.out.println(
                            "[" + cnt + ". ?-intro " + expressionToIndex.get(
                                    new Impl(
                                            ((Exists) ((Impl) proofStage).getLeft()).getExpression(),
                                            ((Impl) proofStage).getRight())) + "] " + proofStage);
                } else {
                    System.out.println("Expression "
                                    + cnt
                                    + ": variable "
                                    + ((Exists) ((Impl) proofStage).getLeft()).getVariable()
                                    + " occurs free in ?-rule.");
                    return;
                }
            } else if (proofStage instanceof Impl
                    && ((Impl) proofStage).getRight() instanceof ForAll
                    && proven.contains(
                            new Impl(
                                    ((Impl) proofStage).getLeft(),
                                    ((ForAll) ((Impl) proofStage).getRight()).getExpression()))) {
                if (!((Impl) proofStage).getLeft().getFreeVars().contains(
                        ((ForAll) ((Impl) proofStage).getRight()).getVariable())) {
                    System.out.println(
                            "[" + cnt + ". @-intro " + expressionToIndex.get(
                                    new Impl(
                                            ((Impl) proofStage).getLeft(),
                                            ((ForAll) ((Impl) proofStage).getRight()).getExpression())) + "] " + proofStage);
                } else {
                    System.out.println("Expression "
                            + cnt
                            + ": variable "
                            + ((ForAll) ((Impl) proofStage).getRight()).getVariable()
                            + " occurs free in @-rule.");
                    return;
                }
            } else if (check12 instanceof Expression) {
                System.out.println("Expression "
                        + cnt
                        + ": variable "
                        + ((Exists) ((Impl) proofStage).getRight()).getVariable()
                        + " is not free for term "
                        + check12
                        + " in ?-axiom.");
                return;
            } else if (check11 instanceof Expression) {
                System.out.println("Expression "
                        + cnt
                        + ": variable "
                        + ((ForAll) ((Impl) proofStage).getLeft()).getVariable()
                        + " is not free for term "
                        + check11
                        + " in @-axiom.");
                return;
            } else {
                System.out.println("Expression " + cnt + " is not proved.");
                return;
            }
            int finalCnt = cnt;
            expressionList.add(proofStage);
            expressionToIndex.putIfAbsent(proofStage, finalCnt);
            cnt++;
            proven.add(proofStage);
            if (proofStage instanceof Impl) {
                provenImplRightToLeft.putIfAbsent(
                        ((Impl) proofStage).getRight(),
                        new LinkedHashSet<>());
                provenImplRightToLeft.get(((Impl) proofStage).getRight())
                        .add(finalCnt);
            }
            if (!scanner.hasNextLine() && !proofStage.equals(proving)) {
                System.out.println("The proof proves different expression.");
                return;
            }
        }
    }
}
