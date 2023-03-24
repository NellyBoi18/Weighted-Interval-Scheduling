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
int scheduleJobs(job *jobs, int numJobs) {
    int maxWeight;

    // Array to store the maximum weight for each job i
    int *jobMaxWeights = calloc(numJobs+1, sizeof(int));

    // Sort the jobs based on their end times in ascending order
    qsort(jobs, numJobs, sizeof(job), compareJobs);

    for (int i = 1; i <= numJobs; i++) {
        maxWeight = jobs[i-1].weight;

        // Check all previous jobs j in reverse order to find the one that ends before the current job i starts
        for (int j = i-1; j >= 1; j--) {
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
    maxWeight = jobMaxWeights[numJobs];

    free(jobMaxWeights);

    return maxWeight;
}

int main() {
    int numInstances, numJobs;
    job jobs[MAX_N];
    
    // Number of instances
    scanf("%d", &numInstances);

    // Array to store the maximum weight for each instance
    int *maxWeight = calloc(numInstances+1, sizeof(int));

    for (int i = 0; i < numInstances; i++) {
        // Number of jobs for the current instance
        scanf("%d", &numJobs);

        // Start time, end time, and weight for each job
        for (int j = 0; j < numJobs; j++) {
            scanf("%d %d %d", &jobs[j].start, &jobs[j].end, &jobs[j].weight);
        }

        // Schedule jobs and save max weight for the current instance to array
        maxWeight[i] = scheduleJobs(jobs, numJobs);
        // printf("%d\numJobs", scheduleJobs(jobs, numJobs));
    }

    // Print max weight for each test case
    for (int i = 0; i < numInstances; i++) {
        printf("%d\numJobs", maxWeight[i]);
    }

    return 0;
}
