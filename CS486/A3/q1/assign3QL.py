'''
HEADER:
Introduction to Artificial Intelligence: Assignment 3, Reinforcement Learning(QLearning)
Teach the kid to wear clothes in a proper manner.


(1) Representations of states:
At any given state of the program the state is defined as a 4 character string, where each character denotes the position of the cloth denoted by that character position.
Clothes Order in string: 0: shirt, 1: sweater, 2: socks, 3: shoes.
Example:
RRRR: Denotes that all the clothes are in the room. (initial state)
UUFF: Denotes that all the clothes have been worn in a proper manner. The shirt and sweater are on the upper body and the socks and shoes are on the feet.(Final State)


(2) Transition Diagram:
The transition Diagram is stored in a Dictionary where each key denotes a node in the graph and
the value for eack key is a list of all nodes that have a connection from that node.
For example: For the graph (http://www.mrgeek.me/wp-content/uploads/2014/04/directed-graph.png) the dictionary would look like:

tDiag = {
	"A":["B"],
	"B":["C"],
	"C":["E"],
	"D":["B"],
	"E":["D","F"],
	"F":[]
}

'''

#Libraries allowed: Numpy, Matplotlib
#Installed using: pip install numpy matplotlib
import matplotlib.pyplot as plt
import numpy as np

'''
All possible locations for the clothes: "R: Room", "U: Upper Body", "F: Feet"
Clothes to wear along with their type; U: Upper Body, F: Feet:
NOTE: It is "not" required to use this variable.
'''
clothes = {
	0:{"name":"shirt","type":"U","order":1},
	1:{"name":"sweater","type":"U","order":2},
	2:{"name":"socks","type":"F","order":1},
	3:{"name":"shoes","type":"F","order":2}
}

'''
Global variable to store all "possible" states.
Please enter all possible states from part (a) Transition Graph in this variable.
For state reference check HEADER(1)
'''
states = ["RRRR", "RRFR", "RRFF", "URRR", "URFR", "URFF", "UURR", "UUFR", "UUFF"]
enumState = {
	"RRRR": 0,
	"RRFR": 1,
	"RRFF": 2,
	"URRR": 3,
	"URFR": 4,
	"URFF": 5,
	"UURR": 6,
	"UUFR": 7,
	"UUFF": 8
}

'''
This function is used to build the Transition Diagram.(tDiag)
I/P: states variable, O/P: returns transition dictionary.
For reference check HEADER(2)
'''
def buildTransitionDiag(states):
	tDiag = {}
	for state in states:
		transitions = []
		if state[0] == 'R':
			transitions.append('U' + state[1:])
		elif state[1] == 'R':
			transitions.append("RR" + state[2:])
			transitions.append("UU" + state[2:])
		else:
			transitions.append("UR" + state[2:])

		if state[2] == 'R':
			transitions.append(state[0:2] + 'F' + state[3])
		elif state[3] == 'R':
			transitions.append(state[0:2] + "RR")
			transitions.append(state[0:2] + "FF")
		else:
			transitions.append(state[0:3] + 'R')
		tDiag[state] = transitions
	return tDiag

'''
This function builds the Reward Matrix R.
Penultimate transition are assigned a high score ~ 100.
Possible transitions are assigned 0.
Transitions not possible are assigned -1.
I/P: transition diagram, O/P: returns R matrix.
'''
def buildRMatrix(tD):
	R = {}
	for state in tD:
		reward = {}
		for transition in tD[state]:
			reward[transition] = 0
		R[state] = reward
	R["URFF"][states[8]] = 100
	R["UUFR"][states[8]] = 100
	return R

'''
This function returns the path taken while solving the graph by utilizing the Q-Matrix.
I/P: Q-Matrix. O/P: Steps taken to reach the goal state from the initial state.
NOTE: As you probably infer from the code, the break-off point is 50-traversals. You'll probably encounter this while finishing this assignment that at the initial stages of training, it is impossible for the agent to reach the goal stage using Q-Matrix. This break-off point allows your program to not be stuck in a REALLY-LONG loop.
'''
def solveUsingQ(Q):
	start = initial_state
	steps = [start]
	while start != goal_state:
		start = np.argmax(Q[start])
		steps.append(start)
		if len(steps) > 50: break
	return steps


'''
Q-Learning Function.
This function takes as input the R-Matrix, gamma, alpha and Number of Episodes to train Q for.
It returns the Q-Matrix as output.
'''
def learn_Q(R, gamma = 0.8, alpha = 0.0, numEpisodes = 0):
	Q = []
	for i in range(0, 9):
		row = []
		for k in range(0, 9):
			row.append(0)
		Q.append(row)

	currentIndex = np.random.randint(0, 9)
	for episode in range(0, numEpisodes):
		currentState = states[currentIndex]
		nextState = tDiag[currentState][np.random.randint(0,len(tDiag[currentState]))]
		nextIndex = enumState[nextState]
		Q[currentIndex][nextIndex] += alpha * (R[currentState][nextState] + gamma * max(Q[nextIndex]) - Q[currentIndex][nextIndex])
		currentIndex = nextIndex

	return Q


#variables that hold returned values from the defined functions.
tDiag = buildTransitionDiag(states)
R = buildRMatrix(tDiag)

#Define the initial and goal state with the corresponding index they hold in variable "states".
initial_state = 0
goal_state = 8

'''
Problem: Perform 500 episodes of training, and after every 2nd iteration,
use the Q Matrix to solve the problem, and save the number of steps taken.
At the end of training, use the saved step-count to plot a graph: training episode vs # of Moves.

NOTE: Do this for 4 alpha values. alpha = 0.1, 0.5, 0.8, 1.0
'''
trainSteps = []#Variable to save iteration# and step-count.
runs = [i for i in range(10,500,2)]#List contatining the runs from 10 -> 200, with a jump of 2.

for i in runs:
	Q = learn_Q(R, alpha = 0.1, numEpisodes = i)
	stepsTaken = len(solveUsingQ(Q))
	trainSteps.append([i,stepsTaken])

#After Training, plotting diagram.
#NOTE: rename diagram accordingly or it will overwrite previous diagram.
x,y = zip(*trainSteps)
plt.plot(x,y,".-")
plt.xlabel("Training Episode")
plt.ylabel("# of Traversals.")
#plt.show()
plt.savefig("q1_a0.1.png")

#Save the output for the best possible order, as generated by the code in the FOOTER.
path = solveUsingQ(Q)
print("\nThe best possible order to wear clothes is:\n")
tmp = ""
for i in path:
	tmp += states[i] + " -> "
print(tmp.rstrip(" ->"))
'''
FOOTER: Save program output here:

'''
