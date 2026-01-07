Combinatorial search is a technique for solving complex problems by systematically exploring a vast "state space" of possible solutions, using clever algorithms and heuristics (like pruning) to avoid checking every single option. It's used for hard problems like chess, for which an exhaustive search is impractical. 

This section introduces backtracking as a technique for listing all possible solutions for a combinatorial algorithm problem. Clever pruning techniques speed up real search applications. For problems that are too large to contemplate using combinatorial search, heuristic methods like simulated annealing are presented in Chapter 12.

## Backtracking
https://www.youtube.com/watch?v=Zq4upTEaQyM
Backtracking is a systematic way to run through all the possible configurations of a search space.
- These configurations may represent all possible arrangements of objects (permutations) or all possible ways of building a collection of them (subsets).
- Other common situations demand enumerating all spanning trees of a graph, all paths between two vertices, or all possible ways to partition vertices into colour classes.
- Backtracking ensures correctness by enumerating all possibilities. It ensures efficiency by never visiting a state more than once.
Viewing backtracking as a depth-first search on an implicit graph yields a natural recursive implementation of the basic algorithm:
```
Backtrack-DFS(a, k)
	if a = (a_1, a_2, ..., a_k) is a solution, report it.
	else
		k = k + 1
		construct S_k, the set of candidates for position k of a
		while S_k is not empty do
			// pop some element from S_k and make recursive call with it
			a_k = an element in S_k
			S_k = S_k − {a_k}
			Backtrack-DFS(a, k)
```
- **`a`**: your _current partial solution_, usually thought of as an array/tuple  
    `a = (a1, a2, ..., ak)` where you’ve decided the first `k` choices so far.
- **`k`**: how many positions of `a` are currently filled (your “depth” in the search tree).
- **`S_k`**: the **set of candidates** you’re allowed to put in position `k` (given the problem’s rules and what you already chose in `a_1..a_{k-1}`).
```C
void backtrack(int a[], int k, Data input) {
	int c[MAXCANDIDATES]; /* candidates for next position */
	int nc;               /* next position candidate count */
	
	if (is_a_solution(a, k, input)) {
		process_solution(a, k,input);
	} else {
		k = k + 1;
		construct_candidates(a, k, input, c, &nc);
		for (int i = 0; i < nc; i++) {
			a[k] = c[i];
			make_move(a, k, input); // may not always be used
			backtrack(a, k, input);
			unmake_move(a, k, input); // may not always be used
			
			if (finished) {
				return; /* terminate early */
			}
		}
	}
}
```
- `is_a_solution(a,k,input)` – tests whether the first k elements of vector a form a complete solution for the given problem (returns bool). The last argument, input, allows us to pass general information into the routine. We can use it to specify n—the size of a target solution. This makes sense when constructing permutations or subsets of n elements, but other data may be relevant when constructing variable-sized objects such as sequences of moves in a game.
- `construct_candidates(a,k,input,c,&nc)` – This routine fills an array c with the complete set of possible candidates for the kth position of a, given the contents of the first k − 1 positions. The number of candidates returned in this array is denoted by nc. Again, input may be used to pass auxiliary information.
- `process_solution(a,k,input)` – This routine prints, counts, stores, or processes a complete solution once it is constructed. 
- `make_move(a,k,input)` *and* `unmake_move(a,k,input)` – These routines enable us to modify a data structure in response to the latest move, as well as clean up this data structure if we decide to take back the move. Such a data structure can always be rebuilt from scratch using the solution vector `a`, but this can be inefficient when each move involves small incremental changes that can easily be undone.
- A global `finished` flag is included to allow for premature termination, which could be set in any application-specific routine.

### Examples of backtracking
#### Constructing all subsets
How many subsets are there of an n-element set, say the integers ${1, \ldots ,n}$? There are exactly two subsets for `n = 1`, namely `{}` and `{1}`. There are four subsets for `n = 2`, and eight subsets for `n = 3`. Each new element doubles the number of possibilities, so there are $2^n$ subsets of $n$ elements.
Each subset is described by the elements that are contained in it. To construct all $2^n$ subsets, we set up a Boolean array/vector of n cells, where the value of $a_i$ (true or false) signifies whether the ith item is in the given subset. In the scheme of our general backtrack algorithm, `S_k = (true, false)` and `a` is a solution whenever `k = n`. We can now construct all subsets with simple implementations of `is_a_solution()`, `construct_candidates()`, and `process_solution()`.
```C
int is_a_solution(int a[], int k, int n) {
	return (k == n);
}

void construct_candidates(int a[], int k, int n, int c[], int *nc) {
	c[0] = true;
	c[1] = false;
	*nc = 2;
}

void process_solution(int a[], int k, int input) {
	printf("{");
	for (int i = 1; i <= k; i++) {
		if (a[i] == true) {
			printf(" %d", i);
		}
	}
	printf(" }\n");
}

void generate_subsets(int n) { 
	int a[NMAX]; /* solution vector */ 
	backtrack(a, 0, n); // initial call
}
``` 

#### Constructing all permutations
```C
void construct_candidates(int a[], int k, int n, int c[], int *nc) {
	bool in_perm[NMAX]; /* what is now in the permutation? */
	
	// set of candidates is all values not already in the permuation
	// we create a boolean array to store whether some integer i is in 
	// the permutation
	
	for (int i = 1; i < NMAX; i++) {
		in_perm[i] = false; // initialise in_perm array
	}
	
	for (int i = 1; i < k; i++) {
		in_perm[a[i]] = true; // loop through a to build in_perm
	}
	
	*nc = 0;
	for (int i = 1; i <= n; i++) {
		if (!in_perm[i]) {
			// add integers not already in the permutation to the candidate set
			c[ *nc ] = i;
			*nc = *nc + 1;
		}
	}
}

int is_a_solution(int a[], int k, int n) {
	return (k == n); // same as subset above
}

void process_solution(int a[], int k, int input) {
	// same as subset (print a)
}

void generate_subsets(int n) { 
	int a[NMAX]; /* solution vector */ 
	backtrack(a, 0, n); // initial call
}
```

*Skipped constructing all paths in a graph*

## Search Pruning
- Consider travelling salesman problem
- Optimal solution is to compute all permutations of travel between every vertex in the graph
	- Then take the solution with the smallest edge weight
- However, consider that the starting vertex $v_1$ has no edge to $v_2$. 
	- Rather than compute the $(n-2)!$ permutations that start with $[v_1,v_2]$, we can prune the search here and continue from $[v_1,v_3]$
- Furthermore, say during our search we find a solution (tour) whose cost is $C_t$
	- If we later have a partial solution with a greater cost than $C_t$
	- we should just abandon this path because we know already it is not optimal
**Exploiting symmetry** is another important technique for reducing search time
- Say we compute all tours (sticking with the TSP) starting from $v_1$
- Is there any point computing all tours from $v_2$?
	- No - any tour starting and ending at $v_2$ can be viewed as a rotation of one starting and ending at $v_1$, for TSP tours are closed cycles
- Therefore, there are thus only $(n−1)!$ distinct tours on $n$ vertices, not $n!$. 
- By restricting the first element of the tour to $v_1$, we save a factor of $n$ in time without missing any interesting solutions.

## Sudoku
*Skipped  - examples of pruning techniques and emphasis of their importance*

## Best-First Search
- In the `backtrack` implementation presented above, the search order was determined by the sequence of elements generated by the `construct_candidates` routine.
- Items near the front of the candidates array were tried before those further back.
- A good candidate ordering can have a very powerful effect on the time to solve the problem.
- The examples so far in this chapter have focused on existential search problems, where we look for a single solution (or all solutions) satisfying a given set of constraints. 
- Optimization problems seek the solution with the lowest or highest value of some objective function.
- A simple strategy to deal with optimization problems is to construct all possible solutions, and then report the one that scores best by the optimization criterion. 
- But this can be expensive. 
- Much better would be to generate solutions in order from best to worst, and report the best as soon as we can prove it is the best

Best-first search, also called branch and bound, assigns a cost to every partial solution we have generated. We use a priority queue (named q below) to keep track of these partial solutions by cost, so the most promising partial solution can be easily identified and expanded. As in backtracking, we explore the next partial solution by testing if it is a solution and calling process solution if it is. We identify all ways to expand this partial solution by calling construct candidates, each of which gets inserted into the priority queue with its associated cost. A generic best-first search, which we apply to the traveling salesman problem (TSP), is implemented as follows:

```C
void branch_and_bound(tsp_solution *s, tsp_instance *t) {
    int c[MAXCANDIDATES]; /* candidates for next position */
    int nc;               /* next position candidate count */
    
    first_solution(&best_solution, t);
    best_cost = solution_cost(&best_solution, t);
    initialize_solution(s, t);
    extend_solution(s, t, 1);
    pq_init(&q);
    pq_insert(&q, s);
    
    while (top_pq(&q).cost < best_cost) {
        *s = extract_min(&q);
        if (is_a_solution(s, s->n, t)) {
            process_solution(s, s->n, t);
        } else {
            construct_candidates(s, (s->n) + 1, t, c, &nc);
            for (int i = 0; i < nc; i++) {
                extend_solution(s, t, c[i]);
                pq_insert(&q, s);
                contract_solution(s, t);
            }
        }
    }
}

void extend_solution(tsp_solution *s, tsp_instance *t, int v) {
    s->n++;
    s->p[s->n] = v;
    s->cost = partial_solution_lb(s, t);
}

void contract_solution(tsp_solution *s, tsp_instance *t) {
    s->n--;
    s->cost = partial_solution_lb(s, t);
}
```
Does the first full solution from a best-first search have to be an optimal solution? 
- No, not necessarily. There was certainly no cheaper partial solution available when we pulled it off the priority queue. But extending this partial solution came with a cost, that of the next edge we added to this tour. It is certainly possible that a slightly more costly partial tour might be finishable using a less-expensive next edge, thus producing a better solution
- Thus, to get the global optimal, we must continue to explore the partial solutions coming off the priority queue until they are more expensive than the best solution we already know about.

## A* Heuristic
https://www.youtube.com/watch?v=6TsL96NAZCo
- an elaboration on the branch-and-bound search presented above, where at each iteration we expanded the best (cheapest) partial solution that we have found so far.
- Best-first search is sort of like breadth-first search. A disadvantage of BFS over DFS is the space required. 
- A backtracking/DFS tree uses memory proportional to the height of the tree, but a best-first/BFS tree requires maintaining all partial solutions, more akin to the width of the tree. 
- The resulting size of the priority queue for best-first search is a real problem. 
- Consider the TSP experiments above. For n = 11, the queue size got to 202,063 compared to a stack size of just 11 for backtracking. 
- Space will kill you quicker than time. To get an answer from a slow program you just have to be patient enough, but a program that crashes because of lack of memory will not give an answer no matter how long you wait.
- **IMPORTANT:** for A*, you **must** chose a heuristic that **never** overestimates the cost
	- the heuristic must provide a lower bound on the solution
	- e.g. if it takes 9 units to get to the destination, the heuristic estimate must be 9 or lower, or the algorithm fails
	- e.g. Euclidean distance is the minimum possible distance, so we know it provides a lower bound on the true cost. 

A* score = actual (not heuristic ) cost of path to node + heuristic score of node