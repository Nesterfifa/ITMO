package dijkstra

import kotlinx.atomicfu.AtomicInt
import java.util.*
import java.util.concurrent.Phaser
import java.util.concurrent.ThreadLocalRandom
import java.util.concurrent.atomic.AtomicInteger
import java.util.concurrent.locks.ReentrantLock
import kotlin.Comparator
import kotlin.concurrent.thread
import kotlin.random.Random

private val NODE_DISTANCE_COMPARATOR = Comparator<Node> { o1, o2 -> o1!!.distance.compareTo(o2!!.distance) }

class MultiQueue(t: Int) {
    class BlockingQueue {
        val queue = PriorityQueue(NODE_DISTANCE_COMPARATOR)
        val lock = ReentrantLock()
    }

    private val _queues = Collections.nCopies(2 * t, BlockingQueue())
    private val random = Random(0)

    fun enqueue(elem: Node) {
        while (true) {
            val index = random.nextInt(_queues.size)
            val queue = _queues[index]
            if (queue.lock.tryLock()) {
                try {
                    queue.queue.add(elem)
                    break
                } finally {
                    queue.lock.unlock()
                }
            }
        }
    }

    fun dequeue(): Node? {
        while (true) {
            val i = random.nextInt(_queues.size)
            val j = random.nextInt(_queues.size)

            val q1 = _queues[i]
            val q2 = _queues[j]

            if (q1.lock.tryLock()) {
                try {
                    if (q2.lock.tryLock()) {
                        return try {
                            if (q1.queue.peek() == null && q2.queue.peek() == null) {
                                null
                            } else if (q1.queue.peek() == null) {
                                q2.queue.poll()
                            } else if (q2.queue.peek() == null) {
                                q1.queue.peek()
                            } else if (NODE_DISTANCE_COMPARATOR.compare(q1.queue.peek(), q2.queue.peek()) < 0) {
                                q1.queue.poll()
                            } else {
                                q2.queue.poll()
                            }
                        } finally {
                            q2.lock.unlock()
                        }
                    } else {
                        return q1.queue.poll()
                    }
                } finally {
                    q1.lock.unlock()
                }
            }
        }
    }
}

// Returns `Integer.MAX_VALUE` if a path has not been found.
fun shortestPathParallel(start: Node) {
    val workers = Runtime.getRuntime().availableProcessors()
    // The distance to the start node is `0`
    start.distance = 0
    // Create a priority (by distance) queue and add the start node into it
    val q = MultiQueue(workers)
    q.enqueue(start)
    // Run worker threads and wait until the total work is done
    val onFinish = Phaser(workers + 1) // `arrive()` should be invoked at the end by each worker
    val activeNodes = AtomicInteger(1)
    repeat(workers) {
        thread {
            while (activeNodes.get() > 0) {
                val u = q.dequeue()
                if (u != null) {
                    for (v in u.outgoingEdges) {
                        while (true) {
                            if (v.to.distance > u.distance + v.weight) {
                                if (v.to.casDistance(v.to.distance, u.distance + v.weight)) {
                                    q.enqueue(v.to)
                                    activeNodes.incrementAndGet()
                                } else {
                                    continue
                                }
                            } else {
                                break
                            }
                        }
                    }
                    activeNodes.decrementAndGet()
                }
            }
            onFinish.arrive()
        }
    }
    onFinish.arriveAndAwaitAdvance()
}
