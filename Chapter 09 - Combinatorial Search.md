Combinatorial search is a technique for solving complex problems by systematically exploring a vast "state space" of possible solutions, using clever algorithms and heuristics (like pruning) to avoid checking every single option. It's used for hard problems like chess, for which an exhaustive search is impractical. 

This section introduces backtracking as a technique for listing all possible solutions for a combinatorial algorithm problem. Clever pruning techniques speed up real search applications. For problems that are too large to contemplate using combinatorial search, heuristic methods like simulated annealing are presented in Chapter 12.

## Backtracking
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
Each subset is described by the elements that are contained in it. To construct all $2^n$ subsets, we set up a Boolean array/vector of n cells, where the value of $a_i$ (true or false) signifies whether the ith item is in the given subset. In the scheme of our general backtrack algorithm, `S_k = (true, false)` and `a` is a solution whenever` k = n`. We can now construct all subsets with simple implementations of `is_a_solution()`, `construct_candidates()`, and `process_solution()`.
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
```