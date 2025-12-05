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

### Conclusion
Hashing is a fundamental idea in randomized algorithms, yielding linear expected-time algorithms for problems that are Θ(n log n) or Θ(n^2) in the worst case.