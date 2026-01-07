## Binary Search
Binary search on a sorted array allows finding in $\left\lceil \lg n \right\rceil$ comparisons

### Counting Occurrences
If we want to count the number of occurrences of some key $k$ in a sorted list
- sorting means they will all appear in a contiguous block
- we need to count how big the block is
- we can find one occurrence using binary search in O(lg n)
	- then move left and right in the array until a different element is reached
	- for $S$ occurrences of $k$, this gives $O(\lg n + S)$
	- if the entire array is equal keys, this can result in O(n)
- a faster algorithm is to modify binary search to return the boundary of the block

### One-Sided Binary Search
- consider an array consisting of a run of 0s, followed by an unbounded run of 1s
- we have no upper bound on this array, so traditional binary search does not work
- we start at the beginning and test repeatedly in large intervals (`A[1], A[2], A[4], A[8], A[16], ...`) until we find a non-zero value
- Now we have a window and can do traditional binary search
- This can find transition point $p$ using at most $2 \lg p$ comparisons
- Useful when looking for a key that lies close to our current position

### Square and Other Roots
We can use a form of binary search to calculate the square root $r$ of a number $n$.
- take the midpoint $m$ between left $l$ and right $r$
- start with $l=1$ and $r=n$
- square the midpoint: 
	- If $n \geq m^2$, then the square root must be greater than $m$, so we repeat the algorithm with the new midpoint between $m$ and $r$
	-  If $n \lt m^2$, then the square root must be greater than $m$, so we repeat the algorithm with the new midpoint between $l$ and $m$
We can do the same thing to find a root of a function
- root of a function is some value $x$ such that $f(x)=0$
- start with values $l$ and $r$ such that $f(l) > 0$ and $f(r) < 0$.
- take midpoint $m$ of $l$ and $r$ 
- depending upon the sign of $f(m)$, we can cut the window containing the root in half with each test

## Recurrence Relations
An equation in which a function is defined in terms of itself
- e.g. Fibonacci numbers: $F_n = F_{n−1} + F_{n−2}$

### Master Theorem
Divide-and-conquer recurrences of the form $T(n) = aT(n/b)+f(n)$ are generally easy to solve, because the solutions typically fall into one of three distinct cases
1. If $f(n) = O(n^{\log_b {a−e}})$ for some constant $e > 0$, then $T(n) = Θ(n ^ {\log_b a})$. 
2. If $f(n) = Θ(n^{\log_b {a}})$, then $T(n) = Θ(n ^ {\log_b a} \lg n)$. 
3. If  $f(n) = Ω(n^{\log_b {a+e}})$ for some constant $e > 0$, and if $af(n/b) ≤ cf(n)$ for some $c < 1$, then $T(n) = Θ(f(n))$.

### Using the Master Theorem
For
$$T(n)=aT(n/b)+f(n), a≥1,  b>1$$
Define the benchmark:
$$g(n)=n^{log_{⁡b} a}$$
Then compare $f(n)$ to $g(n)$.
1. If $f(n)$ is polynomially smaller than $g(n)$:
	- *Case 1: Too many leaves*
	- Total runtime is $O(n ^ {log_b a})$
	- number of leaf nodes outweighs the overall internal evaluation cost
2. If $f(n)$ is polynomially the same as $g(n)$ (same order):
	- *Case 2: Equal work per level*
	- Total runtime is $O(n^{log_b a} \lg n)$
	- As we move down the tree, each problem gets smaller but there are more of them to solve. If the sums of the internal evaluation costs at each level are equal, the total running time is the cost per level ($n ^ {log_b a}$) times the number of levels ($log_b n$)).
3. If $f(n)$ is polynomially larger than $g(n)$:
	- *Case 3: Too expensive a root*
	- Total runtime is $O(f(n))$.
	- If the internal evaluation cost grows very rapidly with $n$, then the cost of the root evaluation may dominate everything. 
An example of this can be seen below.

## Fast Multiplication
Suppose each number has $n = 2m$ digits. Observe that we can split each number into two pieces each of $m$ digits, such that the product of the full numbers can easily be constructed from the products of the pieces, as follows. Let $w = 10^{m+1}$, and represent $A = a_0 + a_1w$ and $B = b_0 + b_1w$, where $a_i$ and $b_i$ are the pieces of each respective number. Then:
$$A × B = (a_0 + a_1w) × (b_0 + b_1w) = a_0b_0 + a_0b_1w + a_1b_0w + a_1b_1w^2$$
Karatsuba’s algorithm is an alternative recurrence for multiplication, which yields a better running time. Suppose we compute the following three products:
![[Pasted image 20251209123917.png]]
We divide the problem into 3 multiplications of size $n/2$, the combination (addition) of which takes $O(n)$ time. Therefore, the time complexity of this algorithm is governed by the recurrence:
$$T(n)=3T(n/2) + O(n)$$
To solve this, define the benchmark:
$$g(n)=n^{log_{⁡b} a}=n^{log_{⁡2} 3}\approx n^{1.585}$$
The benchmark $g(n)$ is less than $f(n)=O(n)$, so it fits *case 1* of the master theorem. 
Therefore, runtime is $O(n^{1.585})$.

## Largest Subrange and Closest Pair
Say we want to find the largest subrange within the following array:
$$[−17, 5, 3, −10, 6, 1, 4, −3, 8, 1, −13, 4]$$
For a sample this small it is trivial, indexes 4 to 9 inclusive: $[6, 1, 4, −3, 8, 1]$
But how do we find this algorithmically?
The trivial solution is to check every subrange, which requires $O(n^2)$ time.
There exists a divide-and-conquer algorithm that runs in $O(n \log n)$ time

We can divide the array $A$ into left and right halves. 
- The largest subrange is either in the left half or the right half, or includes the middle. 
- A recursive program to find the largest subrange between $A[l]$ and $A[r]$ can easily call itself to work on the left and right subproblems. 
- The largest subrange spanning the middle will be the **union** of the largest subrange on the left ending on $m$, and the largest subrange on the right starting from $m+1$
- Dividing $n$ into two halves, doing linear work, and recurring takes time $T(n)$, where $$T(n)=2 · T(n/2) + Θ(n)$$
- Case 2 of the master theorem yields $T(n) = Θ(n \log n)$.

## Parallel Algorithms
Multiple processors are typically best deployed to exploit data parallelism, running a single algorithm on different and independent data sets.

### Pitfalls
- There is often a small upper bound on the potential win 
	- often, even greater performance gains can often result from developing more eﬃcient sequential algorithms. 
	- your time spent parallelising code might well be better spent enhancing the sequential version.
- Speedup is meaningless if its measured against a poor sequential algorithm
	- e.g. minimax game-tree search algorithm used in computer chess programs. 
	- a brute-force tree search is embarrassingly easy to parallelise: just put each subtree on a diﬀerent processor.
	- the more clever alpha–beta pruning algorithm can easily save 99.99% of the work, thus dwarfing any benefits of a parallel brute-force search. 
	- Alpha–beta can be parallelised, but not easily, and the speedups grow surprisingly slowly as a function of the number of processors you have.
- Parallel algorithms are tough to debug
	- non-deterministic nature of inter-processor communication makes parallel programs notoriously difficult to debug
- 