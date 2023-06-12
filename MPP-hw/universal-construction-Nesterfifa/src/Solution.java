/**
 * @author : Nesterenko Viktor
 */
public class Solution implements AtomicCounter {
    private final Node root = new Node();
    private final ThreadLocal<Node> last = ThreadLocal.withInitial(() -> root);

    public int getAndAdd(int x) {
        while (true) {
            final int old = last.get().value;
            final Node result = new Node(old + x);
            last.set(last.get().next.decide(result));
            if (last.get() == result) {
                return old;
            }
        }
    }

    private static class Node {
        final int value;
        final Consensus<Node> next = new Consensus<>();

        Node() {
            this(0);
        }

        Node(int value) {
            this.value = value;
        }
    }
}
