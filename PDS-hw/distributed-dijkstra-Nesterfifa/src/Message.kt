package dijkstra.messages

import dijkstra.ChildType

sealed class Message

data class MessageWithChildren(val type : ChildType) : Message()

data class MessageRelax(val distance : Long) : Message()
