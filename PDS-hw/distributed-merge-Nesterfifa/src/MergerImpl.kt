import system.MergerEnvironment

class MergerImpl<T : Comparable<T>>(
    private val mergerEnvironment: MergerEnvironment<T>,
    prevStepBatches: Map<Int, List<T>>?
) : Merger<T> {
    private val batches: HashMap<Int, List<T>> = HashMap()

    init {
        if (prevStepBatches != null) {
            for (batch in prevStepBatches) {
                batches[batch.key] = batch.value
            }
        } else {
            for (i in 0 until mergerEnvironment.dataHoldersCount) {
                batches[i] = mergerEnvironment.requestBatch(i)
            }
        }
    }

    override fun mergeStep(): T? {
        var min: T? = null
        var minIndex = -1
        for (batch in batches) {
            if (min == null || min > batch.value[0]) {
                min = batch.value[0]
                minIndex = batch.key
            }
        }
        if (minIndex != -1) {
            var batch = batches[minIndex].orEmpty()
            batch = batch.subList(1, batch.size)
            if (batch.isNotEmpty()) {
                batches[minIndex] = batch
            } else {
                batch = mergerEnvironment.requestBatch(minIndex)
                if (batch.isEmpty()) {
                    batches.remove(minIndex)
                } else {
                    batches[minIndex] = batch
                }
            }
        }
        return min
    }

    override fun getRemainingBatches(): Map<Int, List<T>> {
        return batches
    }
}