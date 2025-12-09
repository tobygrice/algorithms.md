Clever sorting algorithms exist that run in $O(n \log(n))$. This is a big improvement over naïve $O(n^2)$ sorting algorithms, for large values of n.

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
- an implementation of selection sort using a priority queue
```
SelectionSort(A) 
	For i = 1 to n do 
		Sort[i] = Find-Minimum from A 
		Delete-Minimum from A 
	Return(Sort)
```
- Using an unsorted array, selection sort performs n iterations, where each iteration takes O(n), for a total of $O(n^2)$.
- Priority queues support finding smallest value in O(lg n) time
**Heapsort** is an implementation of selection sort with a priority queue using [[Chapter 03 - Data Structures#Heaps|heaps]]
- This gives us n iterations, with each iteration now taking lg n (instead of n/2)
- Gives us $O(n \log n)$ (instead of $O(n^2)$ with unsorted array)


## Mergesort
- Divide array in half, recursively sort both halves, then merge the two sorted arrays
	- base case: subarray has size 1, already sorted
- Time complexity:
	- We can only halve an $n$-sized array $\lg n$ times 
	- Merge function repeatedly checks the head of each array to build sorted array in $O(n)$
	- Max of $\lg n$ levels with each level running in linear time => $O(n \log(n))$
- Implementation:
```C
void merge_sort(item_type s[], int low, int high) {
    int middle; /* index of middle element */
    if (low < high)
    {
        middle = (low + high) / 2;
        merge_sort(s, low, middle);
        merge_sort(s, middle + 1, high);
        merge(s, low, middle, high);
    }
}

void merge(item_type s[], int low, int middle, int high) {
    int i;                  /* counter */
    queue buffer1, buffer2; /* buffers to hold elements for merging */
    init_queue(&buffer1);
    init_queue(&buffer2);
    for (i = low; i <= middle; i++) {
        enqueue(&buffer1, s[i]);
    }
    for (i = middle + 1; i <= high; i++){
        enqueue(&buffer2, s[i]);
    }

    i = low;
    while (!(empty_queue(&buffer1) || empty_queue(&buffer2))){
        if (headq(&buffer1) <= headq(&buffer2)) {
            s[i++] = dequeue(&buffer1); 
        } else {
            s[i++] = dequeue(&buffer2); 
        }
    }
    while (!empty_queue(&buffer1)) {
        s[i++] = dequeue(&buffer1);
    }
    while (!empty_queue(&buffer2)) {
        s[i++] = dequeue(&buffer2);
    }
}
```

## Quicksort
- Select a random item $p$ from the $n$ items to sort
- Separate the other $n-1$ items into two piles:
	- one containing all elements less than $p$
	- one containing all elements greater than or equal to $p$
- Now $p$ is in its sorted position between the two piles
- The two piles can be sorted entirely independently (do so recursively).
```C
void quicksort(item_type s[], int l, int h) {
    int p; /* index of partition */
    if (l < h) {
        p = partition(s, l, h);
        quicksort(s, l, p - 1);
        quicksort(s, p + 1, h);
    }
}

int partition(item_type s[], int l, int h) {
    int i;         /* counter */
    int p;         /* pivot element index */
    int firsthigh; /* divider position for pivot element */
    
    p = h;         /* select last element as pivot */
    firsthigh = l;
    for (i = l; i < h; i++) {
        if (s[i] < s[p]) {
            swap(&s[i], &s[firsthigh]);
            firsthigh++;
        }
    }
    swap(&s[p], &s[firsthigh]);
    
    return (firsthigh);
}
```

- In best case, pivot is median value of subarray (equal num of elements either side)
	- result is $\lg n$ levels => $O(n \log(n))$ in best case (each level takes linear time to partition)
- In worst case, we select a pivot that is the min or max of every sub array
	- each partition only reduces problem size by 1
	- worst case time of $O(n^2)$
- Worst case is worse than heapsort or mergesort: expected case must be good?

### Expected Case
On average, random quicksort partition trees (and by analogy, binary search trees under random insertion) are very good. 
- More careful analysis shows the average height after n insertions is approximately 2 ln n. Since 2 ln n ≈ 1.386 lg n, this is only 39% taller than a perfectly balanced binary tree.
- Since quicksort does O(n) work partitioning on each level, the average time is O(n log n). 
- If we are extremely unlucky, and our randomly selected elements are always among the largest or smallest element in the array, quicksort turns into selection sort and runs in O(n^2). But the odds against this are vanishingly small.

### Ensuring Randomisation
- Say our program always selected the last element as the pivot
- If the array was truly randomly unsorted, this would be fine
	- but if it was to be given a sorted array, this would run in $O(n^2)$
- We can randomly permute (rearrange) the order of the initial array before sorting to **guarantee** $\Theta (n \log n)$ average time.
	- takes linear time but guarantees average on *any* input
- Alternatively, select a pivot from a random index at each step
- Experiments show that when quicksort is implemented well, it is typically two to three times faster than mergesort or heapsort.