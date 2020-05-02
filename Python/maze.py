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
        self.nd_dict = dict(zip(self.nodes,list(self.raw_data[:,1:5])))  # key: index, value: the correspond node
        self.adj=dict()
        for k,v in self.nd_dict.items():
            non_nan=[]
            for i in v:
                if str(i) != 'nan':non_nan.append(int(i))
            self.adj[int(k)]=non_nan

    def getStartPoint(self):
        if (len(self.nd_dict) < 2):
            print("Error: the start point is not included.")
            return 0
        return self.nd_dict[1]

    def getNodeDict(self):
        return self.nd_dict

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
        #find the nearest way    
        a=80 # some large number
        for key,val in ways.items():
            if a>len(val) and len(val)!=1:
                a=len(val)
                min_way=val
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
        return None

    def strategy(self, nd):
        return self.BFS(nd)

    def strategy_2(self, nd_from, nd_to):
        return self.BFS_2(nd_from, nd_to)


if __name__ == '__main__':
    MZ=Maze("data/small_maze.csv")
    #print(MZ.raw_data[:,1:5])
    #print(str(np.array(MZ.raw_data)[1][2])=='nan')
    #print(MZ.nodes)
    print(MZ.BFS_2(5,2))
    #print(MZ.getStartPoint())