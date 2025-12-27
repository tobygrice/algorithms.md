Greedy algorithms that make the best local decision at each step are typically efficient, but usually do not guarantee global optimality. 
Exhaustive search algorithms that try all possibilities and select the best always produce the optimum result, but usually at a prohibitive cost in terms of time complexity. 

Dynamic programming combines the best of both worlds. It gives us a way to design custom algorithms that systematically search all possibilities (thus guaranteeing correctness) while storing intermediate results to avoid recomputing (thus providing efficiency). 
- By storing the consequences of all possible decisions and using this information in a systematic way, the total amount of work is minimized.

Dynamic programming is a technique for efficiently implementing a recursive algorithm by storing partial results.
- a naive recursive algorithm computes the same subproblems over and over and over again
- storing the answer for each subproblem in a table to look up instead of recompute can lead to an efficient algorithm

Dynamic programming starts with a recursive algorithm or definition. Only after we have a correct recursive algorithm can we worry about speeding it up by using a results matrix
- Dynamic programming is essentially a tradeoff of space for time

## Caching
Consider a simple recursive function to calculate the $n$th fibonacci number:
```C
long long fib_r(int n) {
    if (n == 0) {
        return (0);
    }
    if (n == 1) {
        return (1);
    }
    return (fib_r(n - 1) + fib_r(n - 2));
}
```
Now consider the recursion tree for calling `fib_r(6)` on this function:
![[Pasted image 20251218182216.png]]
Notice that we compute `F(4)` twice. In this way, we can waste enormous amounts of compute generating these numbers.

We can write a new algorithm that caches numbers after they are calculated:
```C++
#define MAXN 92    /* largest n for which F(n) fits in a long */
#define UNKNOWN -1 /* contents denote an empty cell */
long long f[MAXN + 1];  /* array for caching fib values */

long long fib_c(int n) {
    if (f[n] == UNKNOWN) {
        f[n] = fib_c(n - 1) + fib_c(n - 2);
    }
    return (f[n]);
}

long long fib_c_driver(int n) {
    f[0] = 0;
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        f[i] = UNKNOWN;
    }
    return (fib_c(n));
}

int main() {
    std::cout << fib_c_driver(50);
}
```

This gives us a much cleaner recursion tree:
![[Pasted image 20251218183231.png]]

Finally, we can calculate fibonacci numbers using dynamic programming:
```C
long fib_ultimate(int n) {
	long long back2=0, back1=1; /* last two values of f[n] */
	long long next; /* placeholder for sum */
	
	if (n == 0) return (0);
	
	for (int i = 2; i<n; i++) {
		next = back1+back2;
		back2 = back1;
		back1 = next;
	}
	
	return(back1+back2);
}
```
Observe that we have removed all recursive calls! We evaluate the Fibonacci numbers from smallest to biggest and store all the results, so we know that we have $F_{i−1}$ and $F_{i−2}$ ready whenever we need to compute $F_i$. We also remove the space by only storing the two most previous calculations, which are all we need.

### Another example
Another example of how to eliminate recursion by specifying the order of evaluation: computing binomial coefficients.
The binomial coefficients are the most important class of counting numbers, where $n \choose k$ counts the number of ways to choose k things out of n possibilities.
The binomial coefficient can be computed as:
$${n \choose k}= {n - 1 \choose k - 1} + {n-1 \choose k}$$
We can compute two base cases here:
- ${m \choose 0}$ is always 1, as there is only 1 way to choose 0 things from a set: the empty set
- ${m \choose m}$ is always 1, as there is only 1 way to choose m things from a set of m elements: the complete set
- We can cache results in a matrix and compute the base cases first, then build the rest of the matrix from these base cases
```C
long binomial_coefficient(int n, int k) {
    int i, j;                    /* counters */
    long bc[MAXN + 1][MAXN + 1]; /* binomial coefficient table */
    
    // can access n choose k using bc[n][k]
    // bc of n choose k = bc[n - 1][k - 1] + bc[n - 1][k];
    
    // base case: n choose 0 = 1
    // there is only one way to choose 0 items from a set: the empty set
    for (i = 0; i <= n; i++) {
        bc[i][0] = 1;
    }
    
    // base case: n choose n = 1
    // there is only one way to choose m items from m: the complete set
    for (j = 0; j <= n; j++) {
        bc[j][j] = 1;
    }
    
    // use base cases to compute entire matrix:
    for (i = 2; i <= n; i++) {
        for (j = 1; j < i; j++) {
            bc[i][j] = bc[i - 1][j - 1] + bc[i - 1][j];
        }
    }
    
    return (bc[n][k]);
}
```

## Approximate string matching
*Skipped - 10 pages on this*


## Longest Increasing Subsequence
There are three steps involved in solving a problem by dynamic programming: 
1. Formulate the answer you want as a recurrence relation or recursive algorithm. 
2. Show that the number of different parameter values taken on by your recurrence is bounded by a (hopefully small) polynomial. 
3. Specify an evaluation order for the recurrence so the partial results you need are always available when you need them

Consider the problem of finding the longest increasing subsequence of a set (the longest set of ordered numbers within the set). For example, consider set $S$:
$$S = (2, 4, 3, 5, 1, 7, 6, 9, 8)$$
The longest increasing subsequence of S is of length 5: for example, $(2,3,5,6,8)$. In fact, there are eight of this length: $(2,3,5,7,9)$, $(2,4,5,7,9)$, $(2,4,5,6,8)$ etc.
To find the right recurrence, ask what information about the first n − 1 elements of $S = (s_1, \ldots, s_n)$ would enable you to find the answer for the entire sequence:
- The length L of the longest increasing sequence in $(s_1, s_2,...,s_{n−1})$ seems a useful thing to know. In fact, this will be the length of the longest increasing sequence in S, unless $s_n$ extends some increasing sequence of the same length.
  Unfortunately, this length L is not enough information to complete the full solution. Suppose I told you that the longest increasing sequence in $(s_1, s_2,...,s_{n−1})$ was of length 5 and that $s_n = 8$. Will the length of the longest increasing subsequence of S be 5 or 6? It depends on whether the length-5 sequence ended with a value < 8.
- We need to know the length of the longest sequence that $s_n$ will extend. To be certain we know this, we really need the length of the longest sequence ending at every possible value $s_i$.

Define $L_i$ to be the length of the longest sequence ending with $s_i$. The longest increasing sequence containing $s_n$ will be formed by appending it to the longest increasing sequence to the left of $n$ that ends on a number smaller than $s_n$. The following recurrence computes $L_i$: 
![[Pasted image 20251219120041.png]]

## Subset Sum
Find a subset of $S$ such that all elements add up to a target $k$.
- Think of a backpacker trying to completely fill a knapsack of capacity $k$ with possible selections from set $S$.
This is an NP-complete problem, but we can use dynamic programming to trade time complexity for space complexity. 
Either the $n$th integer $s_n$ is part of a subset adding up to $k$, or it is not. If it is, then there must be a way to make a subset of the first $n − 1$ elements of $S$ adding up to $k − s_n$, so the last element can finish the job. If not, there may well be a solution that does not use $s_n$.
```C
bool sum[MAXN + 1][MAXSUM + 1];   /* table of realizable sums */
int parent[MAXN + 1][MAXSUM + 1]; /* table of parent pointers */

bool subset_sum(int s[], int n, int k) {
    int i, j; /* counters */
	
    sum[0][0] = true;
    parent[0][0] = NIL;
	
    for (i = 1; i <= k; i++) {
        sum[0][i] = false;
        parent[0][i] = NIL;
    }
	
    for (i = 1; i <= n; i++) { /* build table */
        for (j = 0; j <= k; j++) {
            sum[i][j] = sum[i - 1][j];
            parent[i][j] = NIL;
			
            if ((j >= s[i - 1]) && (sum[i - 1][j - s[i - 1]] == true)) {
                sum[i][j] = true;
                parent[i][j] = j - s[i - 1];
            }
        }
    }
	
    return (sum[n][k]);
}

void report_subset(int n, int k) {
    if (k == 0) {
        return;
    }
	    
    if (parent[n][k] == NIL) {
        report_subset(n - 1, k);
    } else {
        report_subset(n - 1, parent[n][k]);
        printf(" %d ", k - parent[n][k]);
    }
}
```


## The ordered partition problem
- Problem description:
	- Suppose that three workers are given the task of scanning through a shelf of books in search of a given piece of information. To get the job done fairly and efficiently, the books are to be partitioned among the three workers. To avoid the need to rearrange the books or separate them into piles, it is simplest to divide the shelf into three regions and assign each region to one worker.
	- But what is the fairest way to divide up the shelf? If all books are the same length, the job is pretty easy. Just partition the books into equal-sized regions, 
		- 100 100 100 | 100 100 100 | 100 100 100
	- But in another example, where the books are of varying length, the fairest partition would be:
		- 100 200 300 400 500 | 600 700 | 800 900
	- Notice the set cannot be reordered.
- A novice algorist might suggest a heuristic as the most natural approach to solving the partition problem, perhaps by computing the desired average weight of a partition, and then trying to insert the dividers to come close to this average.
- But there is a better solution using dynamic programming.
- Define $M[n, k]$ to be the minimum possible cost over all partitionings of $s_1,\ldots,s_n$ into $k$ ranges, where the cost of a partition is the largest sum of elements in **one** of its parts. This function can be evaluated:
$$M[n,k] = \min_{i=1}^{n}\left( \max\left( M[i,k-1], \sum_{j=i+1}^{n} s_j \right) \right)$$
- Boundary conditions (smallest possible values for each argument) are as follows:
	- For $n$: smallest reasonable argument is 1, meaning the 1st element of the set
		- can't provide an empty set
		- cannot be partitioned
		- result is the largest sum partition, which in this case is just the first element
		- $M[1, k] = s_1$, for all $k \gt 0$
	- For $k$: smallest reasonable argument is 1, meaning we do not partition the set at all
		- result is just the sum of the whole set
		- $M[n,1] = \sum_{i=1}^{n} s_i$
```C
void partition(int s[], int n, int k) {
    int p[MAXN + 1];           /* prefix sums array */
    int m[MAXN + 1][MAXK + 1]; /* DP table for values */
    int d[MAXN + 1][MAXK + 1]; /* DP table for dividers */
    int cost;                  /* test split cost */
    int i, j, x;               /* counters */
	
	// p[i] holds the sum from s[1] to s[i]
    p[0] = 0; /* construct prefix sums */
    for (i = 1; i <= n; i++) {
        p[i] = p[i - 1] + s[i];
    }
	
	// m[n][k] is the minimum largest partition sum possible when partitioning 
	// the first n elements into k groups
	
	// d[n][k] stores the position of the **last** divider in the solution
	// for m[n][k]. Note that divider is directly after stored index.
	// so if d[n][k] is x, the divider is between x and x+1
	
	// for k = 1 (1 group), result is always the total sum of the set
    for (i = 1; i <= n; i++) {
        m[i][1] = p[i]; /* initialize boundaries */
    }
	
	// for n = 1 (only partition 1st element), result is always the first element
    for (j = 1; j <= k; j++) {
        m[1][j] = s[1];
    }
	
	// start from m[2][2] because all n = 1 and k = 1 are already computed above
    for (i = 2; i <= n; i++) { /* evaluate main recurrence */
        for (j = 2; j <= k; j++) {
	        // partition 1..i
	        // into j groups
            m[i][j] = MAXINT; // initialise max
            // try every possible place `x` to make the **last cut**
            // - first part: items `1..x` (will be split into `j-1` groups)
            // - fast part: items `x+1..i` (one group)
            for (x = 1; x < i; x++) {
	            // cost for partition at x is the larger of:
	            // - the sum from x..i
	            // - the largest minimum partition from 1..x for j-1 partitions
                cost = max(m[x][j - 1], p[i] - p[x]);
                // if our new cost is better, update best cost for m[i][j]
                if (m[i][j] > cost) {
                    m[i][j] = cost;
                    d[i][j] = x; // remember divider position
                }
            }
        }
    }
    reconstruct_partition(s, d, n, k); /* print book partition */
}

void reconstruct_partition(int s[], int d[MAXN + 1][MAXK + 1], int n, int k) {
    if (k == 1) {
        print_books(s, 1, n);
    } else {
        reconstruct_partition(s, d, d[n][k], k - 1);
        print_books(s, d[n][k] + 1, n);
    }
}

void print_books(int s[], int start, int end) {
    printf("\{");
    for (int i = start; i <= end; i++) {
        printf(" %d ", s[i]);
    }
    printf("}\n");
}
```

Skipping 10.8, 10.9
- Parsing context-free grammars
- Limitations of dynamic programming (TSP)