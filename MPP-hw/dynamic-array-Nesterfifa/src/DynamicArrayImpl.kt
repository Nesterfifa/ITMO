import kotlinx.atomicfu.*

class DynamicArrayImpl<E> : DynamicArray<E> {
    private val realSize = atomic(0)
    private val core = atomic(Core<E>(INITIAL_CAPACITY))

    override fun get(index: Int): E {
        if (index >= size) throw IllegalArgumentException()
        while (true) {
            val core = core.value
            val value = core.array[index].value

            if (value is NeedToMove<E>) {
                move(core)
                continue
            }

            if (value != null) {
                return value.value
            }
        }
    }

    override fun put(index: Int, element: E) {
        if (index >= size) throw IllegalArgumentException()
        while (true) {
            val core = core.value
            val value = core.array[index].value

            if (value is NeedToMove<E>) {
                move(core)
                continue
            }

            if (core.array[index].compareAndSet(value, NotNeedToMove(element))) {
                return
            }
        }
    }

    override fun pushBack(element: E) {
        while (true) {
            val size = size
            val core = core.value
            if (core.capacity <= size) {
                move(core)
            } else if (core.array[size].compareAndSet(null, NotNeedToMove(element))) {
                realSize.incrementAndGet()
                return
            }
        }
    }

    override val size: Int get() = realSize.value

    private fun move(core: Core<E>) {
        core.next.value ?: core.next.compareAndSet(null, Core(2 * core.capacity))
        val next = core.next.value ?: return
        for (num in 0 until core.capacity) {
            var value: Element<E>?

            do value = core.array[num].value
            while (value is NotNeedToMove<E> && !core.array[num].compareAndSet(value, NeedToMove(value.value)))

            if (value != null) {
                next.array[num].compareAndSet(null, NotNeedToMove(value.value))
            }
        }
        this.core.compareAndSet(core, next)
    }
}

private interface Element<E> {
    val value: E
}
private class NeedToMove<E>(override val value: E) : Element<E>
private class NotNeedToMove<E>(override val value: E) : Element<E>

private class Core<E>(
    val capacity: Int,
) {
    val array = atomicArrayOfNulls<Element<E>>(capacity)
    val next: AtomicRef<Core<E>?> = atomic(null)
}

private const val INITIAL_CAPACITY = 1 // DO NOT CHANGE ME