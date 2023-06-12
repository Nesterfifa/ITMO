package stack;

import kotlinx.atomicfu.AtomicRef;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

public class StackImpl implements Stack {
    private static final int ELIM_SIZE = 1024;
    private static final int NULL = Integer.MIN_VALUE + 5;
    private final List<AtomicRef<Integer>> eliminationArray
            = new ArrayList<>(Collections.nCopies(ELIM_SIZE, new AtomicRef<>(NULL)));

    private static class Node {
        final AtomicRef<Node> next;
        final int x;

        Node(int x, Node next) {
            this.next = new AtomicRef<>(next);
            this.x = x;
        }
    }

    // head pointer
    private AtomicRef<Node> head = new AtomicRef<>(null);

    @Override
    public void push(int x) {
        int index = ThreadLocalRandom.current().nextInt(ELIM_SIZE);
        for (int i = 0; i < 10; i++) {
            if (eliminationArray.get((index + i) % ELIM_SIZE).compareAndSet(NULL, x)) {
                for (int j = 0; j < 10; j++);
                if (eliminationArray.get((index + i) % ELIM_SIZE).compareAndSet(x, NULL)) {
                    break;
                }
                return;
            }
        }
        while (true) {
            Node curHead = head.getValue();
            Node newHead = new Node(x, curHead);
            if (head.compareAndSet(curHead, newHead)) {
                return;
            }
        }
    }

    @Override
    public int pop() {
        int index = ThreadLocalRandom.current().nextInt(ELIM_SIZE);
        for (int i = 0; i < 10; i++) {
            int value = eliminationArray.get((index + i) % ELIM_SIZE).getValue();
            if (value != NULL && eliminationArray.get((index + i) % ELIM_SIZE).compareAndSet(value, NULL)) {
                return value;
            }
        }
        while (true) {
            Node curHead = head.getValue();
            if (curHead == null) return Integer.MIN_VALUE;
            if (head.compareAndSet(curHead, curHead.next.getValue())) {
                return curHead.x;
            }
        }
    }
}
