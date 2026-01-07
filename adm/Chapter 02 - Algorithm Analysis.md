## The RAM Model of Computation
Based on a hypothetical computer called the Random Access Machine, or RAM.
- Each simple operation (`+`, `*`, `–`, `=`, `if`, `call`) takes exactly one time step.
- Loops/subroutines are *not* simple operations - e.g. sorting 10 items is faster than sorting 10,000
- Each memory access takes one time step, cache/disk status is ignored
Very oversimplified but provides an excellent model for algorithm performance analysis.
- Performance estimates are calculated as a function of the input size `n` and the number of simple operations.

## Big-O
Very difficult to precisely calculate best-case, worst-case, and average-case time complexities
- too many bumps, as time does not grow linearly with input size - e.g. binary search is faster for arrays of size exactly $n = 2^k − 1$ (where $k$ is an integer)
- require too much detail to specify precisely

Therefore, we talk in terms of simple upper and lower bounds, using Big Oh notation.
- big-O ignores constant factors: $f(n)=2n=n$. We only care about algorithmic performance - an algorithm written in C may run twice as fast as the same algorithm written in Python. Drop the constant factors.
- The table below demonstrates that the algorithmic bounds are much more impactful than the size of `n`: ![[Pasted image 20251124155403.png]]

### Definitions
We only need our function to provide a bound past some constant $n_0$. We don't care about performance for small $n$, only about performance with very large $n$. Formally:
1. $f(n) = O(g(n))$ means $c · g(n)$ is an upper bound on $f(n)$. Thus, there exists some constant $c$ such that $f(n) ≤ c · g(n)$ for every large enough $n$ (that is, for all $n ≥ n_0$, for some constant $n_0$). 
2. $f(n) = \Omega (g(n))$ means $c · g(n)$ is a lower bound on $f(n)$. Thus, there exists some constant $c$ such that $f(n) ≥ c · g(n)$ for all $n ≥ n_0$. 
3. $f(n) = \Theta (g(n))$ means $c_1 · g(n)$ is an upper bound on $f(n)$ and $c_2 · g(n)$ is a lower bound on $f(n)$, for all $n ≥ n_0$. Thus, there exist constants $c_1$ and $c_2$ $such$ that $f(n) ≤ c_1 · g(n)$ and $f(n) ≥ c_2 · g(n)$ for all $n ≥ n_0$. This means that $g(n)$ provides a nice, tight bound on $f(n)$.
In plainer language (from CTCI):

> - $O$ (big O): In academia, big O describes an upper bound on the time. An algorithm that prints all the values in an array could be described as $O(N)$, but it could also be described as $O(N^2)$, $O(N^3)$, or $O(2^N)$ (or many other big O times). The algorithm is at least as fast as each of these; therefore they are upper bounds on the runtime. This is similar to a less-than-or-equal-to relationship. If Bob is X years old (I'll assume no one lives past age 130), then you could say $X \leq 130$. It would also be correct to say that $X \leq 1000$ or $X \leq 1000000$. It's technically true (although not terribly useful). Likewise, a simple algorithm to print the values in an array is $O(N)$ as well as $O(N^3)$ or any runtime bigger than $O(N)$. 
> - $\Omega$ (big omega): In academia, $\Omega$ is the equivalent concept but for lower bound. Printing the values in an array is $\Omega (N)$ as well as $\Omega (\log N)$ and $\Omega(1)$. After all, you know that it won't be faster than those runtimes. 
> - $\Theta$ (big theta): In academia, $\Theta$ means both $O$ and $\Omega$. That is, an algorithm is $\Theta (N)$ if it is **both** $O(N)$ and $\Omega(N)$. $\Theta$ gives a tight bound on runtime.

In industry (and therefore in interviews), people seem to have merged $\Theta$ and $O$ together. Industry's meaning of big $O$ is closer to what academics mean by $\Theta$, in that it would be seen as incorrect to describe printing an array as $O(N^2)$. Industry would just say this is $O(N)$.
![[Pasted image 20251124154101.png]]

All Big Oh problems can be correctly solved by going back to the definition and working with that. 
Example: Is $2^{n+1} = O(2^n)$? 
- Read as: is $2^{n+1}$ upper bound by $2^n$?
- According to definition above, $f(n) = O(g(n))$ iff there exists a constant $c$ such that for all sufficiently large $n$, $f(n) ≤ c · g(n)$. Is there? Yes, because $2^{n+1} = 2 · 2^n$, and clearly $2 · 2^n ≤ c · 2^n$ for any $c ≥ 2$.

#### Dominance relationships
We say that a faster growing function dominates a slower growing one, just as a faster growing company eventually comes to dominate the laggard. When $f$ and $g$ belong to different classes (i.e. $f(n) \neq \Theta(g(n))$), we say $g$ dominates $f$ when $f(n) = O(g(n)$). This is sometimes written $g \gg f$.

### Big O Classes
These function classes suffice to cover almost all the algorithms we will discuss in this text, and are listed in order of increasing dominance:
1. **Constant functions**, $f(n) = 1$: Such functions might measure the cost of adding two numbers, printing out “The Star Spangled Banner,” or the growth realized by functions such as f(n) = min(n, 100). In the big picture, there is no dependence on the parameter n.
2. **Logarithmic functions**, $f(n) = \log{n}$: Logarithmic time complexity shows up in algorithms such as binary search. Such functions grow quite slowly as n gets big, but faster than the constant function (which is standing still, after all). Logarithms will be discussed in more detail in Section 2.7 (page 48). 
3. **Linear functions**, $f(n) = n$: Such functions measure the cost of looking at each item once (or twice, or ten times) in an n-element array, say to identify the biggest item, the smallest item, or compute the average value. 
4. **Superlinear functions**, $f(n) = n \log{n}$: This important class of functions arises in such algorithms as quicksort and mergesort. They grow just a little faster than linear (recall Figure 2.4), but enough so to rise to a higher dominance class. 
5. **Quadratic functions**, $f(n) = n^2$: Such functions measure the cost of looking at most or all pairs of items in an n-element universe. These arise in algorithms such as insertion sort and selection sort. 
6. **Cubic functions**, $f(n) = n^3$: Such functions enumerate all triples of items in an n-element universe. These also arise in certain dynamic programming algorithms, to be developed in Chapter 10.
7. **Exponential functions**, $f(n) = c^n$ for a given constant $c > 1$: Functions like $2^n$ arise when enumerating all subsets of $n$ items. As we have seen, exponential algorithms become useless fast, but not as fast as...
8. **Factorial functions**, $f(n) = n!$: Functions like $n!$ arise when generating all permutations or orderings of $n$ items.

$n! \gg 2^n \gg n^3 \gg n^2 \gg n \log{n} \gg n \gg \log {n} \gg 1$


### Simplifying Big O
#### Adding Functions
The sum of two or more functions is simply the dominant function:
e.g. $n^3 + n^2 + n+ 1 = \Theta(n^3)$

#### Multiplying Functions
Multiplying by a constant -> ignore the constant
Multiplying by a function:
- An $O(n! \log {n})$ function dominates $n!$ by just as much as $\log n$ dominates $1$. In general:
	- $O(f(n)) · O(g(n)) → O(f(n) · g(n))$
	- $Ω(f(n)) · Ω(g(n)) → Ω(f(n) · g(n))$
	- $Θ(f(n)) · Θ(g(n)) → Θ(f(n) · g(n))$

### Logarithms
Logarithms arise in any process where things are repeatedly halved. When you see a problem where the number of elements in the problem space gets halved each time, that will likely be a $O(\log N)$ runtime.
The base of the logarithm has no real impact on the growth rate.
Logarithms cut any function down to size: $\log{n^2} = O(\log (n))$