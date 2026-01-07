## Linked Lists and Arrays
The **advantages of linked structures** over static arrays include: 
- Overflow on linked structures never occurs unless the memory is actually full.
- Insertion and deletion are simpler than for static arrays. 
- With large records, moving pointers is easier and faster than moving the items themselves. 
Conversely, the relative **advantages of arrays** include: 
- Space efficiency: linked structures require extra memory for storing pointer fields.
- Efficient random access to items in arrays. 
- Better memory locality and cache performance than random pointer jumping.

## Stacks
- LIFO, add to top and take from top (think stack of plates)
- Simple to implement + efficient
- Good when retrieval order doesn't matter at all
- Use `push(data)` and `pop()`
## Queues
- FIFO
- Minimise **maximum** time spent waiting, average time is same as stack
- Trickier to implement and should only be used where order is important
- Use `enqueue(data)` and `dequeue()`

## Dictionaries
![[Pasted image 20251202174218.png]]
![[Pasted image 20251202174209.png]]

## Binary Search Trees
search lg n
insert lg n
delete lg n
successor 1 if parent stored else lg n
predecessor 1 if parent stored else lg n
minimum lg n
maximum lg n

## Priority Queue
Can implement `find_min` in constant time by maintaining a pointer to the minimum element.
- adds O(1) to insertion, compare new value to current min
- deletion requires searching for new min, O(n) for unsorted array and O(lg n) for BBST
	- deletion is already O(n) and O(lg n) in these cases, so this does not affect big O
![[Pasted image 20251205100444.png]]

## Hashing
- Exploit the fact that looking an item up in an array takes constant time once you have its index. 
- A hash function is a mathematical function that maps keys to integers. 
- Use the value of our hash function as an index into an array, and store our item at that position.
- e.g. function to turn a string key into a large integer
	- integer is then reduced `mod m` where `m` is the size of the table
	- result is index of element

### Collision resolution
What to do with keys that hash to the same index?
#### Chaining
- Represents a hash table as an array of m linked lists (“buckets”) ![[Pasted image 20251205101449.png]]
- For `m` buckets with `n` keys, each linked list (bucket) will hold an average of `n/m` elements
- Uses lots of memory on pointers
- Most use open addressing

### Open addressing
- Maintains the hash table as a simple array of elements (not buckets). 
- On each insertion, we check to see whether the desired cell is empty; if so, we insert the item there. 
	- if the cell is already occupied, we must find some other place to put the item. 
	- simplest possibility (called sequential probing) inserts the item into the next open cell in the table. 
	- Provided the table is not too full, the contiguous runs of non-empty cells should be fairly short, hence this location should be only a few cells away from its intended position. 
- Searching for a given key now involves going to the appropriate hash value and checking to see if the item there is the one we want. If so, return it. Otherwise we must keep checking through the length of the run. 
- Deletion in an open addressing scheme can get ugly, since removing one element might break a chain of insertions, making some elements inaccessible. We have no alternative but to reinsert all the items in the run that follows the new hole.

Hashing is a fundamental idea in randomized algorithms, yielding linear expected-time algorithms for problems that are Θ(n log n) or Θ(n^2) in the worst case.

## Heaps
*Defined in chapter 4.3.1*

- maintain a partial order
- a binary tree such that the key of each node dominates the keys of its children.
	- min-heap: a node dominates its children by having a smaller key than they do
	- max-heap: parent nodes dominate by being bigger
- maintaining this as we would a binary tree uses a lot of memory for pointers (parent/left/right)
- heap can be represented without any pointers using an array of keys ![[Pasted image 20251208120145.png]]
- We store the root of the tree in the first position of the array, and its left and right children in the second and third positions, respectively. 
- Scary maths:
	- In general, we store the $2^{l−1}$ keys of the $l$th level of a complete binary tree from left to right in positions $2^{l−1}$ to $2^l−1$. 
	- We assume that the array starts with index 1 to simplify matters
- For a key at position $k$ **with 1-based counting**:
	- Left child is at $2k$
	- Right child is at $2k+1$
	- Parent is at $\left\lfloor {k}/{2} \right\rfloor$
- For a key at position $k$ **with 0-based counting**:
	- Left child is at $2k + 1$
	- Right child is at $2k+2$
	- Parent is at $\left\lfloor \frac {k-1}{2} \right\rfloor$
- To maintain these rules, we must represent a full binary tree
	- a twig (essentially a linked list) would take a huge amount of space
	- e.g. a twig with 8 elements (8 nodes stretching down to depth 8) would require an array of size $2^8-1=255$ to store 8 elements. 
- Therefore, we do not allow holes: 
	- all levels that are not the bottom level must be completely packed
	- the bottom level is packed to the left
	- therefore, $n$ elements are always represented in an array of size $n$
- This implementation saves memory but is far less flexible than using pointers, so is not viable for a BST.

### Implementation
#### Insertion
- Insert the new element at the back of the array: ($n+1$)st position
- If the new element dominates its parent at $\left\lfloor {k}/{2} \right\rfloor$ (not allowed), swap it with its parent
- then check again, does it dominate its new parent?
	- recursively "bubble up" the tree
- Tree height is $\left\lfloor \lg n \right\rfloor$, so insertion is $O(\lg n)$
	- creating a tree of $n$ elements takes $O(n \lg n)$

#### Deletion (only allowed from root)
- The `heap` data structure is designed to pop (delete and return value) the most dominant element (min or max)
	- Root is most dominant element
	- Therefore, you can only delete the root from a heap, no other element
- Remove root and replace with $n$th most element (last element in array)
- If new root dominates both children, great! If not, swap with dominant child
- Then check again, does it dominate both its new children?
	- recursively "bubble down" the tree
- Tree height is $\left\lfloor \lg n \right\rfloor$, so root deletion is $O(\lg n)$
	- deleting all elements a tree of $n$ elements takes $O(n \lg n)$
	- as each element is deleted in sorted order, this can be used to sort an array in $O(n \lg n)$ time
	- this sorting algorithm is called [[Chapter 04 - Sorting#Heapsort|heapsort]]