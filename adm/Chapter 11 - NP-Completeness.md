## P vs. NP
Every well-defined algorithmic problem must have an asymptotically fastest possible algorithm solving it, as measured in the Big Oh notation.

Polynomial time algorithms do not have input size $n$ in the exponent. Exponential time (e.g. $2^n$) algorithms have the input size in the exponent, and therefore grow very quickly - these are considered 'hard'. Satisfiability, TSP, subset sum, etc are $O(2^n)$ 

**P** is the set of algorithmic problems where there exists a polynomial-time (hence P) algorithm to solve it from scratch. Includes problems such as shortest path and minimum spanning tree.

**NP** is the set of all the algorithmic problems whose solutions can be *verified* in polynomial time. Includes traveling salesman, satisfiability, and vertex cover. It also includes everything in P, as (logically) it must be possible to verify a solution produced in polynomial time, in polynomial time. This is called NP, *not necessarily polynomial time*.

**NP-Hard** is the set of all decision problems that are at least as hard as the hardest NP problem. Every NP problem can be _reduced_ to NP-Hard problems. If you have a solution to an NP-Hard problem, you have a solution to all NP problems, up to a polynomial time (deterministic) computation.

**NP-Complete** is the set of all problems that are both NP and NP-Hard. Famously, 3SAT (logical satisfaction problem), knapsack problem, Hamiltonian path etc... are NP-Complete problems. Given an instance of solution, you can decide in polynomial time if they are correct solutions to these problems, and every NP problem can be reduced to them.

**The Big Question:** is there a problem in NP that is not a member of P? That is, is there a problem that can be verified in polynomial time, but not solved in polynomial time?
- If no such problem exists, the classes must be the same and $P = NP$. 
- If even one such a problem exists, the two classes are different and $P \neq NP$.
 Intuitively, the answer to the question above is yes. If $P=NP$ then every problem whose solution can be checked in polynomial time would be solved in polynomial time - this seems impossible. However, we cannot **prove** conclusively that *no* polynomial-time algorithm exists for a hard problem. It is thought that $P \neq NP$, but there is no proof.

## Reductions for algorithms
We have encountered several problems in this book where we couldn’t find any efficient algorithm. The theory of NP-completeness provides the tools needed to show that these problems are all, on some level, really the same problem.

Consider the following allegory:

> A bunch of kids take turns fighting each other in the school yard to prove how “tough” they are. Adam beats up Bill, who then beats up Dwayne. So who if any among them qualifies as “tough?” The truth is that there is no way to know without an external standard. If I tell you that the action takes place in a kindergarten school yard, then the fight results don’t mean very much. But suppose instead that I tell you Dwayne was in fact Dwayne “The Rock” Johnson, certified tough guy. You have to be impressed—both Adam and Bill must be at least as tough as he is. In this telling, each fight represents a reduction, and Dwayne Johnson takes on the role of satisfiability—a certifiably hard problem.

Reductions are a way to show that two problems are essentially identical. A fast algorithm (or the lack of one) for one of the problems implies a fast algorithm (or the lack of one) for the other.

The easiest reduction to make is to reduce a problem to a **decision problem** (one that returns only true or false). For example, the travelling salesman problem can be reduced to:
- *Problem*: The Traveling Salesman Decision Problem (TSDP) 
- *Input*: A weighted graph G and integer k. 
- *Output*: Does there exist a TSP tour with cost ≤ k?
This is just as hard to compute as the traditional TSP variant, but reduces the problem to a homogenous output. 

Whenever we can translate the input for a problem we **want to solve** into input for a problem we **know how to solve**, we can compose the translation and the solution into an algorithm to deal with our problem.
- To solve problem A, we translate/reduce the A instance to an instance of B, and then solve this instance using an efficient algorithm for problem B.

## Proving Hardness
To prove hardness, show that your problem is a reduction of a problem that is known to be hard, or vice-versa.
Skiena uses four (and only four) problems as reduction candidates:
- **3-SAT:** The old reliable. When none of the three problems below seem appropriate, I go back to the original source. 
- **Integer partition:** This is the one and only choice for problems whose hardness seems to require using large numbers. 
- **Vertex cover:** This is the answer for any graph problem whose hardness depends upon *selection*. Chromatic number, clique, and independent set all involve trying to select the right subset of vertices or edges. 
- **Hamiltonian path:** This is my choice for any graph problem whose hardness depends upon *ordering*. If you are trying to route or schedule something, Hamiltonian path is likely your lever into the problem.

## Satisfiability
The core hard problem at the top of the reduction tree
![[Pasted image 20251223114652.png]]
Proving something is as hard as satisfiability means that it is hard.

> **Problem:** Satisfiability (SAT) 
> **Input:** A set of Boolean variables $V$ and a set of logic clauses $C$ over $V$. 
> **Output:** Does there exist a satisfying truth assignment for $C$ - in other words, a way to set each of the variables ${v_1,...,v_n}$ either `true` or `false` so that every clause contains at least one true literal?

This can be made clear with two examples. Consider $C = \{ \{ v_1, \bar{v}_2 \}, \{ \bar{v}_1, v_2 \} \}$ over the Boolean variables $V = \{ v_1, v_2 \}$. We use $\bar{v}_i$ to denote the complement of the variable $v_i$, because $\bar{v}_i$ means “not $v_i$.” We get credit for satisfying a particular clause containing $v_i$ if $v_i = \text{true}$, or a clause containing $\bar{v}_i$ if $v_i = \text{false}$. Therefore, satisfying a particular set of clauses involves making a series of $n$ true or false decisions, trying to find the right truth assignment to satisfy all of them. The example clause set $C = \{ \{ v_1, \bar{v}_2 \}, \{ \bar{v}_1, v_2 \} \}$ corresponds to the logical expression
$$(v_1 \vee \bar{v}_2) \wedge (\bar{v}_1 \vee v_2)$$
and can be satisfied either by setting $v_1 = v_2 = \text{true}$ or $v_1 = v_2 = \text{false}$.
However, consider the set of clauses $\{ \{ v_1, v_2 \}, \{ v_1, \bar{v}_2 \}, \{ \bar{v}_1 \} \}$. Here there can be no satisfying assignment, because $v_1$ _must_ be false to satisfy the third clause, which means that $v_2$ _must_ be false to satisfy the second clause, which then leaves the first clause unsatisfiable. Although you try, and you try, and you try, you can’t get no satisfaction.

### 3-SAT
Consider satisfiability where each clause only contains one literal. This is trivial to solve. A breadth-first search on an appropriate graph can be used to give a linear-time algorithm for 2-SAT. How many literals per clause do you need to turn the problem from polynomial to hard? This transition occurs when each clause contains three literals.

> **Problem:** 3-Satisfiability (3-SAT) 
> **Input:** A collection of clauses C where each clause contains exactly 3 literals, over a set of Boolean variables V . 
> **Output:** Is there a truth assignment to V such that each clause is satisfied?

## Integer Programming
IP is a fundamental combinatorial optimization problem. It is best thought of as linear programming, with the variables restricted to take only integer (instead of real) values.

> **Problem:** Integer Programming (IP) 
> **Input:** A set of integer variables $V$, a set of linear inequalities over $V$, a linear maximization function $f(V)$, and an integer $B$.
> **Output:** Does there exist an assignment of integers to $V$ such that all inequalities are true and $f(V ) ≥ B$?

Consider the following two examples. Suppose 
![[Pasted image 20251223144226.png]]
A solution to this would be $V_1 = 1, V_2 = 2$. Note that this respects integrality, and yields an objective value $f(V )=4 ≥ B$. 

Not all problems have realizable solutions, however. For the following problem
![[Pasted image 20251223144321.png]]
the maximum possible value of $f(V )$ given the constraints is $2 × 2 = 4$, so there can be no solution to the associated decision problem.

## Vertex Cover
The vertex cover problem asks for a small set of vertices that touch every edge in a graph:

> **Problem:** Vertex Cover 
> **Input:** A graph $G = (V,E)$ and integer $k ≤ |V|$ 
> **Output:** Is there a subset $S$ of at most $k$ vertices such that every $e ∈ E$ contains at least one vertex in $S$?

It is trivial to find a vertex cover of a graph: consider the cover that consists of all the vertices. More tricky is to cover the edges using as small a set of vertices as possible.

## Hamiltonian Path
Seeks a tour that visits each vertex of a given graph exactly once. Hamiltonian path/cycle are very similar - Hamiltonian cycle will end on the starting node, Hamiltonian path will not.

> **Problem:** Hamiltonian Cycle 
> **Input:** An unweighted graph G. 
> **Output:** Does there exist a simple tour that visits each vertex of G without repetition?

Similar to TSP, but TSP works on weighted graphs and Hamiltonian cycle on unweighted. There exists a reduction from HC to TSP:
```
HamiltonianCycle(G = (V,E))
	Construct a complete weighted graph G' = (V', E') where V' = V
	n = |V|
	for i = 1 to n do
		for j = 1 to n do
			if (i, j) ∈ E then w(i, j) = 1 else w(i, j)=2
	Return the answer to TSP-Decision-Problem(G, n).
```

