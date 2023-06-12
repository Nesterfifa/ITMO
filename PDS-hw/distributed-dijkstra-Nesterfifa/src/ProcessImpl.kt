package dijkstra

import dijkstra.messages.*
import dijkstra.system.environment.Environment

class ProcessImpl(private val environment: Environment) : Process {
    private var distance: Long? = null
    private var childCount: Int = 0
    private var balance: Int = 0
    private var parentId: Int? = null

    private fun relaxNeighbours() {
        for (neighbour in environment.neighbours) {
            environment.send(neighbour.key, MessageRelax(distance!! + neighbour.value))
            balance++
        }
        becomeGreen()
    }

    private fun becomeGreen() {
        if (childCount == 0 && balance == 0) {
            if (parentId == null) {
                environment.finishExecution()
            } else {
                environment.send(parentId!!, MessageWithChildren(ChildType.NO_MORE_CHILD))
                parentId = null
            }
        }
    }

    override fun onMessage(srcId: Int, message: Message) {
        if (message is MessageRelax) {
            if (distance == null || distance!! > message.distance) {
                if (parentId != null) {
                    environment.send(parentId!!, MessageWithChildren(ChildType.NO_MORE_CHILD))
                }
                environment.send(srcId, MessageWithChildren(ChildType.CHILD))
                parentId = srcId
                distance = message.distance
                relaxNeighbours()
            } else {
                environment.send(srcId, MessageWithChildren(ChildType.NOT_CHILD))
            }
        } else if (message is MessageWithChildren) {
            when (message.type) {
                ChildType.CHILD -> childCount++
                ChildType.NOT_CHILD -> {}
                ChildType.NO_MORE_CHILD -> {
                    childCount--
                    balance++
                }
            }
            balance--
            becomeGreen()
        }
    }

    override fun getDistance(): Long? {
        return distance
    }

    override fun startComputation() {
        distance = 0
        relaxNeighbours()
    }
}

enum class ChildType {
    CHILD, NOT_CHILD, NO_MORE_CHILD
}