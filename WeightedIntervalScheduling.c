#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

typedef struct job {
    int start;
    int end;
    int weight;
} job;

int compare_jobs(const void *a, const void *b) {
    job *job_a = (job *) a;
    job *job_b = (job *) b;
    return job_a->end - job_b->end;
}

int schedule_jobs(job *jobs, int n) {
    int i, j, max_weight;
    int *dp = calloc(n+1, sizeof(int));

    qsort(jobs, n, sizeof(job), compare_jobs);

    for (i = 1; i <= n; i++) {
        max_weight = jobs[i-1].weight;
        for (j = i-1; j >= 1; j--) {
            if (jobs[j-1].end <= jobs[i-1].start) {
                max_weight += dp[j];
                break;
            }
        }
        dp[i] = (dp[i-1] > max_weight) ? dp[i-1] : max_weight;
    }

    max_weight = dp[n];
    free(dp);
    return max_weight;
}

int main() {
    int t, n, i;
    job jobs[MAX_N];

    scanf("%d", &t);
    int maxWeight[t];

    for (i = 0; i < t; i++) {
        scanf("%d", &n);
        for (int j = 0; j < n; j++) {
            scanf("%d %d %d", &jobs[j].start, &jobs[j].end, &jobs[j].weight);
        }
        maxWeight[i] = schedule_jobs(jobs, n);
        // printf("%d\n", schedule_jobs(jobs, n));
    }

    for (i = 0; i < t; i++) {
        printf("%d\n", maxWeight[i]);
    }

    return 0;
}
