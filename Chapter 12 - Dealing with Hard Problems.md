Demonstrating that a problem is NP-complete is rarely the end of the line. Presumably, there was a reason why you wanted to solve it in the first place. That application won’t go away after you learn there is no polynomial-time algorithm. You still seek a program that solves the problem of interest. All you know is that you won’t find one that quickly solves the problem to optimality in the worst case. There are still three possibilities: 
- *Algorithms fast in the average case* – e.g. backtracking algorithms with substantial pruning. 
- *Heuristics* – Heuristic methods like simulated annealing or greedy approaches can be used to quickly find a solution, albeit with no guarantee that it will be the best one. 
- *Approximation algorithms* – The theory of NP-completeness stipulates that it is hard to get the exact answer. With clever, problem-specific heuristics, we can get provably close to the optimal answer on all possible instances

## Approximation Algorithms
Provably good approximation algorithms are often conceptually simple, fast, and easy to program.
It is usually not clear how well the solution from an approximation algorithm compares to what you might get from a heuristic that gives you no guarantees - it is generally best to test both and pick the better option.

