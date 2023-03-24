#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

// Struct to represent a job with start time, end time, and weight
typedef struct job {
    int start;
    int end;
    int weight;
} job;

// Comparison function to sort jobs based on their end times in ascending order
int compareJobs(const void *a, const void *b) {
    job *jobA = (job *) a;
    job *jobB = (job *) b;
    return jobA->end - jobB->end;
}

// Schedule jobs and return the maximum weight of non-overlapping intervals
int scheduleJobs(job *jobs, int n) {
    int i, j, max_weight;

    // Allocate an array to store the maximum weight for each job i
    int *dp = calloc(n+1, sizeof(int));

    // Sort the jobs based on their end times in ascending order
    qsort(jobs, n, sizeof(job), compareJobs);

    for (i = 1; i <= n; i++) {
        max_weight = jobs[i-1].weight;

        // Check all previous jobs j in reverse order to find the one that ends before the current job i starts
        for (j = i-1; j >= 1; j--) {
            if (jobs[j-1].end <= jobs[i-1].start) {
                // If job j doesn't overlap with job i, add its maximum weight to the current job i and break out of the loop
                max_weight += dp[j];
                break;
            }
        }

        // Set the maximum weight for job i to be the maximum of its previous maximum weight and its current maximum weight
        dp[i] = (dp[i-1] > max_weight) ? dp[i-1] : max_weight;
    }

    // Save the maximum weight of the last job as the maximum weight of all non-overlapping intervals
    max_weight = dp[n];
    free(dp);

    // Return the maximum weight of all non-overlapping intervals
    return max_weight;
}

int main() {
    int t, n;
    job jobs[MAX_N];
    

    // Read the number of test cases
    scanf("%d", &t);

    // Allocate an array to store the maximum weight of non-overlapping intervals for each test case
    int maxWeight[t];

    // Loop over all test cases
    for (int i = 0; i < t; i++) {
        // Read the number of jobs for the current test case
        scanf("%d", &n);

        // Read the start time, end time and weight for each job
        for (int j = 0; j < n; j++) {
            scanf("%d %d %d", &jobs[j].start, &jobs[j].end, &jobs[j].weight);
        }

        // Schedule the jobs and save the maximum weight of all non-overlapping intervals for the current test case
        maxWeight[i] = scheduleJobs(jobs, n);
        // printf("%d\n", scheduleJobs(jobs, n));
    }

    // Print the maximum weight of non-overlapping intervals for each test case
    for (int i = 0; i < t; i++) {
        printf("%d\n", maxWeight[i]);
    }

    return 0;
}
