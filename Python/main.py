from node import *
import maze as mz
import score
import interface
import time

import numpy as np
import pandas
import time
import sys
import os


def main():
    maze = mz.Maze("data/small_maze.csv")
    point = score.Scoreboard("data/UID.csv", "team_dao", sys.argv[1])
    interf = interface.interface()
    # TODO : Initialize necessary variables

    if (sys.argv[1] == '0'):
        print("Mode 0: for treasure-hunting with rule 1")
        # TODO : for treasure-hunting with rule 1, which encourages you to hunt as many scores as possible
        start_node=1
        route=maze.BFS(start_node)
        total_route=[start_node]
        while route:
            #print(route)
            total_route+=route[1:]
            node=route[-1]
            route=maze.BFS(node)
        print(total_route)
        actions=[]
        direction=maze.node(total_route[0]).getDirection(maze.node(total_route[1]))
        #print(direction)
        for i in range(0,len(total_route)-1):
            action,direction=maze.getAction(direction,total_route[i],total_route[i+1])
            actions.append(action)
        print(actions)
        step=0
        print('start')
        interf.send_action(actions[step])
        print(actions[step])
        while True:
            if str(interf.get_message())=='h':
                print('node encounter')
                step+=1
                interf.send_action(actions[step])
                print(actions[step])
            UID=interf.get_UID()
            if UID : 
                uid=str(UID)[2::].upper()
                point.add_UID(uid)
            if step==len(actions)-1:break
            
        print('end')

    elif (sys.argv[1] == '1'):
        print("Mode 1: for treasure-hunting with rule 2")
        # TODO : for treasure-hunting with rule 2, which requires you to hunt as many specified treasures as possible
        start_node=6
        treasures=point.sequence #for testing
        route=maze.BFS_2(start_node,treasures[0])
        total_route=[start_node]
        total_route+=route[1:]
        for i in range(len(treasures)-1):
            node=treasures[i]
            next_node=treasures[i+1]
            route=maze.BFS_2(node,next_node)
            print('route=',route)
            total_route+=route[1:]
        print(total_route)
        actions=[]
        direction=maze.node(total_route[0]).getDirection(maze.node(total_route[1]))
        for i in range(0,len(total_route)-1):
            action,direction=maze.getAction(direction,total_route[i],total_route[i+1])
            actions.append(action)
        print(actions)
        step=0
        print('start')
        interf.send_action(actions[step])
        print(actions[step])
        while True:
            if interf.get_message()=='h':
                print('node encounter')
                step+=1
                interf.send_action(actions[step])
                print(actions[step])
            UID=interf.get_UID()
            if UID : 
                uid=str(UID)[2::].upper()
                while len(uid)<8:
                    uid='0'+uid

                point.add_UID(uid)
            if step==len(actions)-1:break
            
        print('end')


        
    elif (sys.argv[1] == '2'):
        print("Mode 2: Self-testing mode.")
        # TODO: You can write your code to test specific function.
        interf.send_action(ADVANCE)


if __name__ == '__main__':
    main()
