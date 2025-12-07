Clever sorting algorithms exist that run in $O(n*\log(n))$. This is a big improvement over naïve $O(n^2)$ sorting algorithms, for large values of n.

**Stable algorithms & sorting equal keys**
- Can resort to secondary keys (e.g. surname as PK, forename as SK)
- **Stable sorting algorithms** leave equal keys in the same order as the original unsorted input
- Very few fast algorithms are naturally stable, but it can be easily achieved by adding the initial index position as a secondary key

**Quicksort in C stdlib**
```C
#include <stdlib.h>

void qsort(void *base, size_t nel, size_t width, int (*compare) (const void *, const void *));
```

- sorts the first `nel` elements of an array (pointed to by `base`), where each element is `width` bytes long.
- takes a user-defined function to compare elements. Function should returns
	- a negative number if the first belongs before the second 
	- a positive number if the second belongs before the first
	- zero if they are the same

e.g. sort integer array:
```C
int intcompare(int *i, int *j) { 
	if (*i > *j) return (1);
	if (*i < *j) return (-1);
	return (0);
}

qsort(a, n, sizeof(int), intcompare);
```

## Heapsort
```
SelectionSort(A) 
	For i = 1 to n do 
		Sort[i] = Find-Minimum from A 
		Delete-Minimum from A 
	Return(Sort)
```
- Performs n iterations, where the average iteration takes n/2 steps, for a total of $O(n^2)$.
	- O(n) to find smallest value
- Priority queues support finding smallest value in O(lg n) time
	- implemented using heap or BST
- Implement selection sort with a priority queue using heap (hence heapsort)
- This gives us n iterations, with each iteration now taking lg n (instead of n/2)
- Gives us $O(n \log n)$ (instead of $O(n^2)$ with unsorted array)

### Heaps
