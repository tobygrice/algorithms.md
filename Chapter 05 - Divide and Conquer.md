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
*This gets very technical into time analysis, went over my head. Subchapters 5.3 and 5.4.*

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

## Fast Multiplication

a=7
b=2

n^2.8