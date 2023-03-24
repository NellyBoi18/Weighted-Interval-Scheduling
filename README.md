# Weighted Interval Scheduling
This program implements the optimal algorithm for Weighted Interval Scheduling. It is as efficient as possible and implemented in O(n<sup>2</sup>) time, where n is the number of jobs.

# Input:
The input will start with a positive integer, giving the number of instances that follow. For each instance, there will be a positive integer, giving the number of jobs. For each job, there will a trio of positive integers i, j, and k, where i < j, and i is the start time, j is the end time, and k is the weight.

# Output:
For each instance, the program outputs the total weight of the intervals scheduled on a separate line, terminated by exactly one newline.

# Sample:
**Input:**\
2\
1\
1 4 5\
3\
1 2 1\
3 4 2\
2 6 4\

**Output:**\
5\
5

The sample input has two instances. The first instance has one job to schedule with a start time of 1, an end time of 4, and a weight of 5. The second instance has 3 jobs. 

# Note:
This program uses unsigned integers due to overflow on 32-bit signed integers in specific instances.