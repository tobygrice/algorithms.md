https://www.youtube.com/watch?v=p9m2LHBW81M

Template:
```python
def backtrack(params):
    if base_case_condition:
        results.append(copy_of_solution)
        return
	
    for choice in choices:
        if violates_constraints:
	        continue
		
        make_choice
        backtrack(updated_params)
        undo_choice # backtracking step
```

The name is confusing because calling `backtrack(updated_params)` isn't backtracking at all, its actually moving further down the decision tree.

The algorithm gets its name from the step *after* this call, which is undoing the decision and calling `backtrack` again on a different decision. We do this for all possible decisions we could make at this step.

**Backtracking is just a depth-first search of the decision tree. When we reach a leaf (no more decisions can be made), we do something with our current path/solution.**

It explores all possible solutions.