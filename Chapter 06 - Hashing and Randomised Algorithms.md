## Randomised Algorithms
Relaxing the demand for either *always* correct or *always* eﬃcient can lead to useful algorithms that still have performance guarantees

We classify randomised algorithms into two types, depending upon whether they guarantee correctness or eﬃciency:
1. *Las Vegas algorithms* - guarantee correctness and are usually (but not always) efficient. 
	- e.g. [[Chapter 04 - Sorting#Quicksort|quicksort]]
2. *Monte Carlo algorithms* - provably efficient, and usually (but not always) produce the correct answer or something close to it.

Randomised algorithms tend to be simple to design and implement
- we do not worry about rare or unlikely situations
- possible to avoid complicated data structures and other contortions
- makes randomised algorithms intuitively appealing and relatively easy to design
However, difficult to analyse
- requires probability theory
- probabilistic analysis often involves algebraic manipulation of long chains of inequalities

$$P(A|B) = \frac{P(A∩B)}{P(B)}$$
Bayes’ theorem:
$$P(B|A) = \frac{P(A|B)P(B)}{P(A)}$$
## Hashing
To avoid creating a worst-case example for an input, we randomise the hash function by reducing it by some random modulo $p$.
- Recall the hashed value = $f(x)\mod m$  
- We can randomise the hash value using: $(f(x) \mod p) \mod m$
This will work fine provided:
- $f(x)$ is large relative to $p$
- $p$ is large relative to $m$ 
- $m$ is relatively prime to $p$.

## Bloom Filters
A bloom filter is a bit-vector hash table 
- each bucket holds only a single bit, no chaining or linking
- a Bloom filter hashes each key $k$ times, using $k$ **different** hash functions. 
- When we insert document $s$ into our Bloom filter, we set all the bits corresponding to $h_1(s), h_2(s), \ldots h_k(s)$ to be $1$, meaning occupied. 
	- To test whether a query document $s$ is present in the data structure, we must test that all $k$ of these bits equal $1$. 
- For a document to be falsely convicted of already being in the filter, it must be unlucky enough that all $k$ of these bits were set in hashes of previous documents.
The odds of a false match:
- $(km/n)^k$
- the error rate associated with larger $k$ increases rapidly with load, so for any given load there is always a point where adding more hash functions becomes counter-productive.

## Perfect Hashing
- Normal hash tables are **fast on average**, but in the **worst case** lookups take $Θ(n)$ time.
- **Perfect hashing** guarantees **worst-case $Θ(1)$ lookup time**.
- This only works for **static sets**:
	- No insertions after construction
	- No deletions after construction
- We try to hash:
	- `n` keys into `m` slots
	- With **no collisions at all**
- The probability that **no collision occurs** is: $$P(\text{no collision}) = \frac{m(m-1)(m-2)\dots(m-n+1)}{m^n}$$
- This is the same math as the **birthday paradox**:
  - With `m = 365` days:
    - At `n = 23` people → collision probability > 50%
    - At `n = 50` people → collision probability > 97%
- From asymptotic analysis:
	- Collisions become likely when: $$n \approx \sqrt{m}$$
	- To avoid collisions safely: $$m = Θ(n^2)$$
- This means:
	- A **single perfect hash table needs quadratic space**
	- This is **too expensive**
### Two-Level Perfect Hashing

#### First-Level Hash Table
- Hash `n` keys into `n` buckets.
- Let $l_i$ = number of elements in bucket `i`.
- We allow collisions at this level.

**The Critical Space Condition**
- We require: $$\sum_{i=1}^{n} l_i^2 = Θ(n)$$
- This means:
	- The **sum of squared bucket sizes stays linear**
	- Even if some buckets are larger, total space remains $Θ(n)$
- The book proves: $$\sum l_i^2 \le 4n \quad \text{with high probability}$$
- If this condition fails, we simply **choose a new first-level hash function and retry**

#### Second-Level Hash Tables
- For each bucket `i` with $l_i$ elements:
	- Allocate a **mini hash table of size $l_i^2$**
	- Choose a new hash function for that bucket
- Because the table is quadratic:
	- The chance of collision is extremely small
	- If a collision occurs:
		- Pick a new hash function
		- Rehash that bucket only
- This guarantees:
	- **No collisions inside second-level tables**
#### Final Lookup Procedure
- Step 1: Find the bucket using: $$i = h_1(s)$$
- Step 2: Jump into the bucket’s private table: $$\text{index} = \text{start}_i + (h_2(s) \bmod l_i^2)$$
- Result:
  - Exactly **two hash computations**
  - Always **$Θ(1)$ worst-case time**

### Guarantees
- **Lookup time:** $Θ(1)$ worst-case  
- **Total space:** $Θ(n)$  
- **Build time:** Expected $Θ(n)$  
- **Fully collision-free after construction**


## String Matching
- **Strings** are sequences of characters where order matters (e.g. `ALGORITHM ≠ LOGARITHM`).
- The **substring pattern matching problem** is:
	- **Input:** A text string `t` and a pattern string `p`
	- **Output:** Does `p` occur as a contiguous substring inside `t`, and if so, where?
- The **naive algorithm**:
	- Tries aligning `p` at every position in `t`
	- Compares all `m` characters each time
	- Worst-case time: $O(nm)$ where:
		- $n = |t|$ (length of text)
		- $m = |p|$ (length of pattern)
### Rabin–Karp: Hash-Based String Matching
- Rabin–Karp is a **randomised, expected linear-time string matching algorithm**.
- Instead of comparing strings directly:
	- Hash the **entire pattern** `p`
	- Hash each **length-`m` window** of `t`
	- If the hash values **do not match**, the strings are definitely different
	- If the hash values **do match**, explicitly compare the substrings (to avoid false positives)
- This reduces the problem to:
	- $(n - m + 1)$ window hash computations
	- A very small number of $O(m)$ direct string checks

## Primality Testing
- Brute force way to test if a number $n$ is prime: 
	- to loop from $i=2$ to $\sqrt {n}$ and check whether $n/i$ is an integer
	- runs in $O(\sqrt {n})$ time
	- very large for big primes
- Fermat's theorem: $$a^{n−1} \mod n = 1 \text { for all } a \text { not divisible by }n$$
	- e.g. when $n = 17$ and $a = 3$, observe that $3^{17−1} \mod 17 = 1$
	- But for $n = 16$, $3^{16−1} \mod 16 = 11$, which proves that 16 cannot be prime.
- Let’s say we can argue that the probability of a composite giving a residue of 1 is less than 1/2.
	- This suggests the following algorithm: Pick 100 random integers $a_j$, each between 1 and n−1. Verify that none of them divide n. 
	- Then compute $(a_j)^{n−1} \mod n$. 
	- If all hundred of these come out to be 1, then the probability that $n$ is not prime must be less than $(1/2)^{100}$, which is vanishingly small. 
	- Because the number of tests (100) is fixed, the running time is always fast, which makes this a **Monte Carlo** type of randomised algorithm.
