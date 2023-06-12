package mutex

/**
 * Distributed mutual exclusion implementation.
 * All functions are called from the single main thread.
 *
 * @author Viktor Nesterenko
 */
class ProcessImpl(private val env: Environment) : Process {
    private var inCS = false
    private var hungry = false
    private val edges: ArrayList<Fork> = ArrayList()
    private val asking = BooleanArray(env.nProcesses + 1)

    init {
        for(i in 0..env.processId) {
            edges.add(Fork.NONE)
        }
        for (i in env.processId + 1 .. env.nProcesses) {
            edges.add(Fork.CLEAN)
        }
    }

    override fun onMessage(srcId: Int, message: Message) {
        message.parse {
            when (readEnum<Request>()) {
                Request.TAKE -> {
                    edges[srcId] = Fork.CLEAN
                    if (isReadyToEat()) {
                        hungry = false
                        inCS = true
                        env.locked()
                    }
                }
                Request.GIVE -> {
                    when (edges[srcId]) {
                        Fork.CLEAN -> asking[srcId] = true
                        Fork.DIRTY -> {
                            if (inCS) {
                                asking[srcId] = true
                            } else {
                                edges[srcId] = Fork.NONE
                                env.send(srcId, Message { writeEnum(Request.TAKE) })
                                if (hungry) {
                                    env.send(srcId, Message { writeEnum(Request.GIVE) })
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    override fun onLockRequest() {
        hungry = true
        if (isReadyToEat()) {
            inCS = true
            hungry = false
            env.locked()
            return
        }
        for (i in 1 .. env.nProcesses) {
            if (i != env.processId && edges[i] == Fork.NONE) {
                edges[i] = Fork.ASKING
                env.send(i, Message { writeEnum(Request.GIVE) })
            }
        }
    }

    override fun onUnlockRequest() {
        inCS = false
        env.unlocked()
        for (i in 1..env.nProcesses) {
            if (i != env.processId) {
                if (asking[i]) {
                    edges[i] = Fork.NONE
                    env.send(i, Message { writeEnum(Request.TAKE) })
                    asking[i] = false
                } else {
                    edges[i] = Fork.DIRTY
                }
            }
        }
    }

    private fun isReadyToEat(): Boolean {
        for (i in 1..env.nProcesses) {
            if (i != env.processId) {
                if (edges[i] != Fork.CLEAN && edges[i] != Fork.DIRTY) {
                    return false
                }
            }
        }
        return true
    }
}

enum class Fork {
    CLEAN, DIRTY, NONE, ASKING
}

enum class Request {
    GIVE, TAKE
}
