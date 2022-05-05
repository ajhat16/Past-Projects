# Timing Results

## Part 1

Enter the timing data for each of the following program. Place the
"real time" measurement in the specified place at the end of the line.

(It the program takes longer than 5 minutes you can terminate its
execution and just indicate "more than 5 minutes" as the time.)

- `time_HW_Lists_Sorted_Words.ml` real time is: 8m43.225s

- `time_HW_Lists_Unsorted_Words.ml` real time is: 9m29.290s

- `time_HW_BSTree_Sorted_Words.ml` real time is: 9m8.342s

- `time_HW_BSTree_Unsorted_Words.ml` real time is: 0m40.506s

- `time_HW_RBTree_Sorted_Words.ml` real time is: 0m46.676s

- `time_HW_RBTree_Unsorted_Words.ml` real time is: 0m36.525s

- `time_HW_TR_Lists_Sorted.ml` real time is: 9m0.866s

- `time_HW_TR_Lists_Unsorted.ml` real time is: 9m23.816s

- `time_HW_TR_BSTree_Sorted.ml` real time is: 8m23.439s

- `time_HW_TR_BSTree_Unsorted.ml` real time is: 0m36.874s

- `time_HW_TR_RBTree_Sorted.ml` real time is: 0m34.409s

- `time_HW_TR_RBTree_Unsorted.ml` real time is: 0m34.569s

## Part 2

Write your answer to the following questions just below the question.

### Question 1

Explain why is the time for `time_HW_Lists_Sorted_Words.ml` so similar to 
the time for `time_HW_Lists_Unsorted_Words.ml`. 

    The times are similar because walking through a list is always O(n) runtime,
    no matter how sorted that list is. 

### Question 2

Explain why is the time for `time_HW_BSTree_Sorted_Words.ml` different from
`time_HW_BSTree_Unsorted_Words.ml`. 

    When inserting sorted elements into a BST, the BST basically becomes a
    List Set with O(n) runtime. However, when the words are inserted in a
    random and unsorted order, the BST will likely be close to balanced,
    making the runtime be O(log(n)). 

### Question 3

Explain why is the time for `time_HW_RBTree_Sorted_Words.ml` so similar to 
the time for `time_HW_RBTree_Unsorted_Words.ml`. 

    No matter in what order the elements are inserted in, the RB tree will
    always rebalance itself if it needs to when a value is inserted. This
    keeps the tree with a consistent O(log(n)) runtime, since rebalancing
    the tree does not take too much time.

### Question 4

How different are the times for `time_HW_RBTree_Sorted_Words.ml` and
`time_HW_TR_RBTree_Sorted_Words.ml`?  Explain why these times are
related in this way.

    The TR version is around 10 seconds faster than the non-TR version.
    The TR version is faster because it does not return to previous
    recursions of the function. This is done by using an accumulator
    to store the variable that is changing.

### Quetions 5

Given the effort to write tail recursive functions, does this
optimization seem worth the effort?

    I would say it is worth it if the function is easy to write
    tail recursively. Otherwise, it does not seem worth the effort
    to rewrite tail recursively.