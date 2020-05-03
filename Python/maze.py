from node import *
import numpy as np
import csv
import pandas
from enum import IntEnum
import math


class Action(IntEnum):
    ADVANCE = 1
    U_TURN = 2
    TURN_RIGHT = 3
    TURN_LEFT = 4
    HALT = 5


class Maze:
    def __init__(self, filepath):
        # TODO : read file and implement a data structure you like
        self.raw_data = pandas.read_csv(filepath).values
        self.nodes = list(self.raw_data[:,0])
        for i in range(len(self.nodes)):
            self.nodes[i]=int(self.nodes[i])
        self.nd_dict = dict(zip(self.nodes,list(Node(i) for i in self.nodes)))  # key: index, value: the correspond node
        self.passed=[]

        for index,node in self.nd_dict.items():
            for i in range(1,5):
                try:
                    a=int(self.raw_data[index-1][i])
                    node.setSuccessor(a,i,int(self.raw_data[index-1][i+4]))
                except:
                    pass
        self.adj=dict()

        for k,v in self.nd_dict.items():
            buffer=[]
            for i in v.getSuccessors():
                buffer.append(i[0])
            self.adj[k]=buffer

    def getStartPoint(self):
        if (len(self.nd_dict) < 2):
            print("Error: the start point is not included.")
            return 0
        return self.nd_dict[1]

    def getNodeDict(self):
        '''
        return the node dictionary.
        the keys are ints represent the indexes of nodes, while values are the items in the Node class which indexes match the keys above.
        '''
        return self.nd_dict

    def node(self,index):
        '''
        return the item in class Node that matches the index(An int).
        '''
        return self.getNodeDict()[index]

    def BFS(self, nd):
        ## TODO : design your data structure here for your algorithm
        ## Tips : return a sequence of nodes from the node to the nearest unexplored deadend

        #do BFS and remember where a node come from in 'marked' list
        marked=[None] * (len(self.nodes)+1)
        qu=[nd]
        if not nd in self.nodes:return None 
        marked[nd]='start'
        while qu:
            s=qu.pop(0)
            for i in self.adj[s]:
                if marked[i] == None:
                    qu.append(i)
                    marked[i] = s
        #find all deadend in the map
        deadends=[]
        for node in self.nodes:
            if len(self.adj[node])==1:deadends.append(node)  
        #for all deadend find the way they come from 
        ways={} 
        for deadend in deadends:
            way=[]
            i=deadend
            while marked[i]!='start':
                way.append(i)
                i=marked[i]
            way.append(i)
            ways[deadend]=way[::-1]
        #find the nearest unexplored way  
        self.passed.append(nd)  
        a=80 # some large 
        min_way=None
        destination=0
        for key,val in ways.items():
            if a>len(val) and len(val)!=1 and key not in self.passed:
                a=len(val)
                min_way=val
                destination=key
        self.passed.append(destination)
        return min_way

    def BFS_2(self, nd_from, nd_to):
        # TODO : similar to BFS but fixed start point and end point
        # Tips : return a sequence of nodes of the shortest path

        marked=[None] * (len(self.nodes)+1)
        qu=[nd_from]
        if not (nd_from in self.nodes and nd_to in self.nodes):return None 
        marked[nd_from]='start'
        while qu:
            s=qu.pop(0)
            for i in self.adj[s]:
                if marked[i] == None:
                    qu.append(i)
                    marked[i] = s
        way=[]
        index=nd_to
        while marked[index] != 'start':
            way.append(index)
            index=marked[index]
        way.append(index)

        return way[::-1]

    def getAction(self, car_dir, nd_from, nd_to):
        # TODO : get the car action
        # Tips : return an action and the next direction of the car
        '''
        car_dir : An int.(Please look up Direction class in node.py for more info.)
        nd_from, nd_to : An int that represents the index of the node.
        return a tuple (action,dir_at_next_node)
        '''
        Dir=self.node(nd_from).getDirection(self.node(nd_to))
        if Dir == car_dir:
            return (Action(1),Dir)
        elif (Dir == 1 and car_dir == 2) or (Dir == 2 and car_dir == 1) or(Dir == 3 and car_dir == 4) or (Dir == 4 and car_dir == 3):
            return (Action(2),Dir)
        elif (Dir == 3 and car_dir == 1) or (Dir == 2 and car_dir == 3) or(Dir == 4 and car_dir == 2) or (Dir == 1 and car_dir == 4):
            return (Action(4),Dir)
        elif (Dir == 4 and car_dir == 1) or (Dir == 2 and car_dir == 4) or(Dir == 3 and car_dir == 2) or (Dir == 1 and car_dir == 3):
            return (Action(3),Dir)
    def strategy(self, nd):
        return self.BFS(nd)

    def strategy_2(self, nd_from, nd_to):
        return self.BFS_2(nd_from, nd_to)


if __name__ == '__main__':
    MZ=Maze("data/small_maze.csv")
    #print(MZ.getStartPoint())
    #print(int(MZ.raw_data[0][1]))
    #print(str(np.array(MZ.raw_data)[1][2])=='nan')
    #print(MZ.nodes)

    #node=2
    #route=MZ.BFS(node)
    #while route:
    #    print(route)
    #    node=route[-1]
    #    route=MZ.BFS(node)

    #print(MZ.getStartPoint())

    route=MZ.BFS(1)
    print(route)
    index=0
    Car_dir=NORTH
    while index != len(route)-1:
        move,Car_dir=MZ.getAction(Car_dir,route[index],route[index+1])
        index+=1
        print(move)
