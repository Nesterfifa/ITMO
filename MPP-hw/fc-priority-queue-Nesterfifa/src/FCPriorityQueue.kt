import kotlinx.atomicfu.atomic
import kotlinx.atomicfu.atomicArrayOfNulls
import java.util.*
import java.util.concurrent.ThreadLocalRandom
import java.util.stream.IntStream

private val WORKERS = Runtime.getRuntime().availableProcessors()

class FCPriorityQueue<E : Comparable<E>> {
    private val q = PriorityQueue<E>()
    private val locked = atomic(false)
    private val operations = atomicArrayOfNulls<Operation<E>>(WORKERS)

    class Operation<E>(val f: () -> E?) {
        var result: E? = null
        var isFinished = false

        fun apply() {
            result = f()
            isFinished = true
        }
    }

    private fun apply(f: () -> E?) : E? {
        val operation = Operation(f)
        var index = ThreadLocalRandom.current().nextInt(0, WORKERS)
        while (!operations[index].compareAndSet(null, operation)) {
            index = ThreadLocalRandom.current().nextInt(0, WORKERS)
        }

        while (!operation.isFinished) {
            if (locked.compareAndSet(expect = false, update = true)) {
                IntStream.range(0, WORKERS)
                    .mapToObj { i -> operations[i].value }
                    .forEach { op ->
                        if (op != null && !op.isFinished) {
                            op.apply()
                        }
                    }
                locked.compareAndSet(expect = true, update = false)
                break
            }
        }
        operations[index].getAndSet(null)
        return operation.result
    }

    /**
     * Retrieves the element with the highest priority
     * and returns it as the result of this function;
     * returns `null` if the queue is empty.
     */
    fun poll(): E? {
        return apply { q.poll() }
    }

    /**
     * Returns the element with the highest priority
     * or `null` if the queue is empty.
     */
    fun peek(): E? {
        return apply { q.peek() }
    }

    /**
     * Adds the specified element to the queue.
     */
    fun add(element: E) {
        apply {
            q.add(element)
            null
        }
    }
}