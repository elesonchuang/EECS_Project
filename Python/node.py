from enum import IntEnum

class Direction(IntEnum):
    NORTH = 1
    SOUTH = 2
    WEST  = 3
    EAST  = 4
globals().update(Direction.__members__)
# Successor : (Node, direction to node, distance)
class Node:
    def __init__(self, index=0):
        self.index = index
        # store successor as (Node, direction to node, distance)
        self.Successors = []
    def __str__(self):
        return 'Node %d' % self.index
    def getIndex(self):
        return self.index

    def getSuccessors(self):
        return self.Successors

    def setSuccessor(self, successor, direction, length=1):
        self.Successors.append((successor, Direction(direction), int(length)))
        print("For Node {}, a successor {} is set.".format(self.index, self.Successors[-1]))
        return


    def getDirection(self, nd):
        #Return the direction of nd from the present node if nd is adjacent to the present node.
        #nd: a Node class item
        for successor in self.Successors:
            if successor[0]==nd.index:return successor[1]

    def isSuccessor(self, nd):
        for succ in self.Successors:
            if succ[0] == nd: 
                return True
        return False

if  __name__ == "__main__":
    a=Node(1)
    a.setSuccessor(2,2,2)
    print(a.getDirection(2)-1)
