#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

// Struct to represent a job with start time, end time, and weight
typedef struct job {
    int start;
    int end;
    int weight;
} job;

// Compare to sort jobs based on their end times in ascending order
int compareJobs(const void *a, const void *b) {
    job *jobA = (job *) a;
    job *jobB = (job *) b;
    return jobA->end - jobB->end;
}

// Schedule jobs and return the maximum weight of non-overlapping intervals
int scheduleJobs(job *jobs, int n) {
    int i, j, maxWeight;

    // Array to store the maximum weight for each job i
    int *jobMaxWeights = calloc(n+1, sizeof(int));

    // Sort the jobs based on their end times in ascending order
    qsort(jobs, n, sizeof(job), compareJobs);

    for (i = 1; i <= n; i++) {
        maxWeight = jobs[i-1].weight;

        // Check all previous jobs j in reverse order to find the one that ends before the current job i starts
        for (j = i-1; j >= 1; j--) {
            if (jobs[j-1].end <= jobs[i-1].start) {
                // If job j doesn't overlap with job i, add its maximum weight to the current job i and break out of the loop
                maxWeight += jobMaxWeights[j];
                break;
            }
        }

        // Set max weight for job i to be the maximum of its previous maximum weight and its current maximum weight
        jobMaxWeights[i] = (jobMaxWeights[i-1] > maxWeight) ? jobMaxWeights[i-1] : maxWeight;
    }

    // Save max weight of the last job as the maximum weight
    maxWeight = jobMaxWeights[n];

    free(jobMaxWeights);

    return maxWeight;
}

int main() {
    int t, n;
    job jobs[MAX_N];
    
    // Number of instances
    scanf("%d", &t);

    // Array to store the maximum weight for each instance
    int *maxWeight = calloc(t+1, sizeof(int));

    for (int i = 0; i < t; i++) {
        // Number of jobs for the current instance
        scanf("%d", &n);

        // Start time, end time, and weight for each job
        for (int j = 0; j < n; j++) {
            scanf("%d %d %d", &jobs[j].start, &jobs[j].end, &jobs[j].weight);
        }

        // Schedule jobs and save max weight for the current instance to array
        maxWeight[i] = scheduleJobs(jobs, n);
        // printf("%d\n", scheduleJobs(jobs, n));
    }

    // Print max weight for each test case
    for (int i = 0; i < t; i++) {
        printf("%d\n", maxWeight[i]);
    }

    return 0;
}
