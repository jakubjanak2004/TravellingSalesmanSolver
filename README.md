# Traveling Salesman Solver

This is a repository for Traveling Salesman Solver project. 
This solver is a command line program that uses branch and bound(also parallel version)
to solve the traveling salesman problem instances exactly.
The program loads
the file in a .dot format and shows the solution in the terminal.
User can also save the 
 solution (there will be an option in the terminal once instance is solved).  

## The Problem Formulation
Is a very famous problem in Computer Science.
Traveling Salesman problem or TSP asks the following:  
Given a list of cities and the distances between each pair of cities,
what is the shortest possible route that visits each city
exactly once and returns to the origin city?  

It is not particularly hard to define the problem, but it is tough to solve it effectively (maybe even impossible).  

The mathematical definition would be:  
Given a directed, weighted graph G = (N, E), where:  
N = {v1, v2, ..., vn} is a set of nodes,  
E = {e1, e2, ..., en} is a set of edges,
w: E -> R+ is a weight function, returning the weight of an edge.  

The goal is to find a Hamiltonian cycle H subset of E such that:
1. each node in N is visited exactly once, and at the end returns to the starting node.  
2. the total weight of the H is minimal.  

Objective Function:  
Find a permutation pi of {1, 2, .., n} such that the total cost of the cycle C(pi) is minimized:  
min C(pi) = sum(i = 1, n) w(a(pi(i), pi(i+1)))  
where pi(n + 1) is defined as pi(1) to complete the cycle.  

The branch of mathematics that studies this type of optimization problems is called Combinatorial Optimization.

The easiest solution would be to find every permutation and see what the total weight would be.
Then find the st of hamiltonian 
cycles with the minimal path.
The problem here is that the computational complexity of such an solution is O(n!) and therefore, 
we will very quickly find ourselves in a place where we are unable to find the solution in normal time(in practice the 
complexity is (n-1)! because we can set some node to be always first).  

The next possibility is to solve the Traveling Salesman by converting it into an LP(linear program).  

Very popular rhythmical is a branch and bound algorithm.
This algorithm finds the set of hamiltonian paths that 
are minimal and is considered exact algorithm.

## Approximation 
The best way to get a good result from a traveling salesman instance is
not by solving it exactly but by finding path
that doesn't have to be optimal but is great.
This method is called approximation and can be done very quickly.
In real life scenarios
is used much more that solving the instance exactly as there may be many nodes and edges(e.g., 1000, 10 000).

## Branch and Bound Algorithm
...

## Implementation
...

## How to use TSS
...