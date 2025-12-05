There are three desirable properties for a good algorithm:
- Correct 
- Efficient
- Easy to implement
These goals may not be simultaneously achievable.

## Travelling Salesman Problem (TSP)
- Find the optimal route through a series of vertexes
- Problem with nearest-neighbour algorithm
	- Starting at $P_0$ results in flipping back and forth between left and right points
	- Starting from the leftmost point solves it in this example, but there is no way to define this rule algorithmically. ![[Pasted image 20251124103726.png]]
- Problem with closest-pair algorithm
	- Repeatedly connect the closest pair of endpoints whose connection will not create a problem
	- In the example below, the gap between rows is smaller than the gap between columns. Result: ![[Pasted image 20251124104057.png]]

