package linked_list_set;

import java.util.concurrent.atomic.AtomicMarkableReference;

public class SetImpl implements Set {
    private static class Node {
        AtomicMarkableReference<Node> next;
        int key;

        Node(int key, AtomicMarkableReference<Node> next) {
            this.next = next;
            this.key = key;
        }
    }

    public Node head = new Node(
            Integer.MIN_VALUE,
            new AtomicMarkableReference<>(new Node(Integer.MAX_VALUE, null), false));

    @Override
    public boolean add(int x) {
        while (true) {
            Node[] curAndNext = findWindow(x);
            Node cur = curAndNext[0];
            Node next = curAndNext[1];
            if (next.key == x) {
                return false;
            }
            Node node = new Node(x, new AtomicMarkableReference<>(next, false));
            if (cur.next.compareAndSet(next, node, false, false)) {
                return true;
            }
        }
    }

    @Override
    public boolean remove(int x) {
        while (true) {
            Node[] curAndNext = findWindow(x);
            Node cur = curAndNext[0];
            Node next = curAndNext[1];
            if (next.key != x) {
                return false;
            }
            Node node = next.next.getReference();
            if (next.next.compareAndSet(node, node, false, true)) {
                cur.next.compareAndSet(next, node, false, false);
                return true;
            }
        }
    }

    @Override
    public boolean contains(int x) {
        return findWindow(x)[1].key == x;
    }

    private Node[] findWindow(int x) {
        retry: while (true) {
            Node cur = head, next = cur.next.getReference();
            while (next.key < x) {
                Node node = next.next.getReference();
                boolean removed = next.next.isMarked();
                if (removed) {
                    if (!cur.next.compareAndSet(next, node, false, false)) {
                        continue retry;
                    }
                    next = node;
                } else {
                    cur = next;
                    next = cur.next.getReference();
                }
            }

            if (next.next == null || !next.next.isMarked()) {
                return new Node[]{cur, next};
            }

            cur.next.compareAndSet(next, next.next.getReference(), false, false);
        }
    }
}