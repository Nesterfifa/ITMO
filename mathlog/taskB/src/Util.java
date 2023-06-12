import operators.*;

public class Util {
    public final static Variable FALSE = new Variable("_|_");

    public static boolean isAxiomScheme(Expression e) {
        return isAxiomScheme1(e)
                || isAxiomScheme2(e)
                || isAxiomScheme3(e)
                || isAxiomScheme45(e)
                || isAxiomScheme6(e)
                || isAxiomScheme7(e)
                || isAxiomScheme8(e)
                || isAxiomScheme9(e)
                || isAxiomScheme10(e);
    }

    public static boolean isAxiomScheme1(Expression e) {
        return e instanceof Impl
                && ((Impl) e).getRight() instanceof Impl
                && ((Impl) e).getLeft().equals(((Impl) ((Impl) e).getRight()).getRight());
    }

    public static boolean isAxiomScheme2(Expression e) {
        return e instanceof Impl
                && ((Impl) e).getRight() instanceof Impl
                && ((Impl) e).getLeft() instanceof Impl
                && ((Impl) ((Impl) e).getRight()).getLeft() instanceof Impl
                && ((Impl) ((Impl) e).getRight()).getRight() instanceof Impl
                && ((Impl) ((Impl) ((Impl) e).getRight()).getLeft()).getRight() instanceof Impl
                && ((Impl) ((Impl) e).getLeft()).getLeft().equals(
                        ((Impl) ((Impl) ((Impl) e).getRight()).getLeft()).getLeft())
                && ((Impl) ((Impl) e).getLeft()).getLeft().equals(
                        ((Impl) ((Impl) ((Impl) e).getRight()).getRight()).getLeft())
                && ((Impl) ((Impl) e).getLeft()).getRight().equals(
                        ((Impl) ((Impl) ((Impl) ((Impl) e).getRight()).getLeft()).getRight()).getLeft())
                && ((Impl) ((Impl) ((Impl) ((Impl) e).getRight()).getLeft()).getRight()).getRight().equals(
                        ((Impl) ((Impl) ((Impl) e).getRight()).getRight()).getRight());
    }

    public static boolean isAxiomScheme3(Expression e) {
        return e instanceof Impl
                && ((Impl) e).getRight() instanceof Impl
                && ((Impl) ((Impl) e).getRight()).getRight() instanceof And
                && ((Impl) e).getLeft().equals(((And) ((Impl) ((Impl) e).getRight()).getRight()).getLeft())
                && ((Impl) ((Impl) e).getRight()).getLeft().equals(
                        ((And) ((Impl) ((Impl) e).getRight()).getRight()).getRight());
    }

    public static boolean isAxiomScheme45(Expression e) {
        return e instanceof Impl
                && ((Impl) e).getLeft() instanceof And
                && (((And) ((Impl) e).getLeft()).getLeft().equals(((Impl) e).getRight())
                || ((And) ((Impl) e).getLeft()).getRight().equals(((Impl) e).getRight()));
    }

    public static boolean isAxiomScheme6(Expression e) {
        return e instanceof Impl
                && ((Impl) e).getRight() instanceof Or
                && ((Impl) e).getLeft().equals(((Or) ((Impl) e).getRight()).getLeft());
    }

    public static boolean isAxiomScheme7(Expression e) {
        return e instanceof Impl
                && ((Impl) e).getRight() instanceof Or
                && ((Impl) e).getLeft().equals(((Or) ((Impl) e).getRight()).getRight());
    }

    public static boolean isAxiomScheme8(Expression e) {
        return e instanceof Impl
                && ((Impl) e).getLeft() instanceof Impl
                && ((Impl) e).getRight() instanceof Impl
                && ((Impl) ((Impl) e).getRight()).getLeft() instanceof Impl
                && ((Impl) ((Impl) e).getRight()).getRight() instanceof Impl
                && ((Impl) ((Impl) ((Impl) e).getRight()).getRight()).getLeft() instanceof Or
                && ((Impl) ((Impl) e).getLeft()).getLeft().equals(
                        ((Or) ((Impl) ((Impl) ((Impl) e).getRight()).getRight()).getLeft()).getLeft())
                && ((Impl) ((Impl) ((Impl) e).getRight()).getLeft()).getLeft().equals(
                        ((Or) ((Impl) ((Impl) ((Impl) e).getRight()).getRight()).getLeft()).getRight())
                && ((Impl) ((Impl) e).getLeft()).getRight().equals(
                        ((Impl) ((Impl) ((Impl) e).getRight()).getLeft()).getRight())
                && ((Impl) ((Impl) e).getLeft()).getRight().equals(
                        ((Impl) ((Impl) ((Impl) e).getRight()).getRight()).getRight());
    }

    public static boolean isAxiomScheme9(Expression e) {
        return e instanceof Impl
                && ((Impl) e).getLeft() instanceof Impl
                && ((Impl) e).getRight() instanceof Impl
                && ((Impl) ((Impl) e).getRight()).getLeft() instanceof Impl
                && ((Impl) ((Impl) ((Impl) e).getRight()).getLeft()).getRight() instanceof Impl
                && ((Impl) ((Impl) e).getRight()).getRight() instanceof Impl
                && ((Impl) ((Impl) e).getLeft()).getLeft().equals(
                        ((Impl) ((Impl) ((Impl) e).getRight()).getLeft()).getLeft())
                && ((Impl) ((Impl) e).getLeft()).getLeft().equals(
                        ((Impl) ((Impl) ((Impl) e).getRight()).getRight()).getLeft())
                && ((Impl) ((Impl) e).getLeft()).getRight().equals(
                        ((Impl) ((Impl) ((Impl) ((Impl) e).getRight()).getLeft()).getRight()).getLeft())
                && ((Impl) ((Impl) ((Impl) ((Impl) e).getRight()).getLeft()).getRight()).getRight().equals(FALSE)
                && ((Impl) ((Impl) ((Impl) e).getRight()).getRight()).getRight().equals(FALSE);
    }

    public static boolean isAxiomScheme10(Expression e) {
        return e instanceof Impl
                && ((Impl) e).getRight() instanceof Impl
                && ((Impl) ((Impl) e).getRight()).getLeft() instanceof Impl
                && ((Impl) e).getLeft().equals(
                        ((Impl) ((Impl) ((Impl) e).getRight()).getLeft()).getLeft())
                && ((Impl) ((Impl) ((Impl) e).getRight()).getLeft()).getRight().equals(FALSE);
    }
}
