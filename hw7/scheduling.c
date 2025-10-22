#include <stdio.h>
#include <stdbool.h>

struct Process
{
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    bool is_completed; // for SJF
    bool is_printed;   // for Gantt Chart
};

void GanttChart(struct Process processes[], int n)
{
    for (int i = 0; i < n; i++) 
    {
        printf("P%d     %d     %d     %d    %d     %d\n", 
               processes[i].pid, 
               processes[i].arrival_time, 
               processes[i].burst_time, 
               processes[i].waiting_time, 
               processes[i].turnaround_time, 
               processes[i].response_time);
    }
    printf("\n");

    float avgWT = 0, avgTAT = 0, avgRT = 0;
    for (int i = 0; i < n; i++)
    {
        avgWT  += processes[i].waiting_time;
        avgTAT += processes[i].turnaround_time;
        avgRT  += processes[i].response_time;
    }
    printf("Average Waiting    Time: %.2f\n", avgWT / n);
    printf("Average Turnaround Time: %.2f\n", avgTAT / n);
    printf("Average Response   Time: %.2f\n", avgRT / n);
}

void printByArrivalTime(struct Process processes[], int n)
{
    printf("Gantt Chart: ");
    for (int i = 0; i < n; i++) 
    {
        printf("| P%d ", processes[i].pid);
    }
    printf("|\n");
    printf("PID    AT    BT    WT   TAT   RT\n"); 
}

void printByBurstTime(struct Process processes[], int n)
{
    printf("Gantt Chart: ");
    int lowest = 1000000;
    int idx    = -1;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            if (processes[j].burst_time <= lowest && 
                !processes[j].is_printed) 
            {
                lowest = processes[j].burst_time;
                idx    = j;
            }
        }
        printf("| P%d ", processes[idx].pid);
        processes[idx].is_printed = true;
        lowest = 1000000;
    }
    printf("|\n");
    printf("PID    AT    BT    WT   TAT   RT\n"); 
}

void sortByArrivalTime(struct Process processes[], int n)
{
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) 
            {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

int findLowestBurstTime(struct Process processes[], int n, int current_time)
{
    int idx    = -1;
    int lowest = 1000000;
    for (int i = 0; i < n; i++) 
    {
        if (processes[i].burst_time < lowest && 
            processes[i].arrival_time <= current_time && 
            !processes[i].is_completed) 
        {
            lowest = processes[i].burst_time;
            idx    = i;
        }
    }
    return idx;
}

void sortByWaitingTime(struct Process processes[], int n)
{
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (processes[j].waiting_time > processes[j + 1].waiting_time) 
            {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void FCFS(struct Process processes[], int n)
{
    sortByArrivalTime(processes, n);
    
    int current_time = 0;
    for (int i = 0; i < n; i++) 
    {
        processes[i].waiting_time    = current_time - processes[i].arrival_time;
        processes[i].turnaround_time = current_time + processes[i].burst_time - processes[i].arrival_time;
        processes[i].response_time   = processes[i].waiting_time;
        processes[i].is_completed    = true;
        current_time += processes[i].burst_time;
    }
}

void SJF(struct Process processes[], int n)
{
    int current_time = 0;
    for (int i = 0; i < n; i++) 
    {
        // Each time we pick process with lowest burst time among the arrived processes
        int idx = findLowestBurstTime(processes, n, current_time);
        if (idx != -1)
        {
            processes[idx].waiting_time    = current_time - processes[idx].arrival_time;
            processes[idx].turnaround_time = current_time + processes[idx].burst_time - processes[idx].arrival_time;
            processes[idx].response_time   = processes[idx].waiting_time;
            processes[idx].is_completed    = true;
            current_time += processes[idx].burst_time;
        }
    }
    // To display in order of waiting time
    sortByWaitingTime(processes, n);
}    

int main()
{
    int n;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) 
    {
        struct Process p;
        p.pid = i + 1;

        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p.arrival_time, &p.burst_time);
        
        processes[i] = p;
    }

    // printf("=== First Come First Served (FCFS) ===\n");
    // FCFS(processes, n);
    // printByArrivalTime(processes, n);
    // GanttChart(processes, n);

    // printf("\n");

    // printf("=== Shortest Job First (SJF) ===\n");
    // SJF(processes, n);
    // printByBurstTime(processes, n);
    // GanttChart(processes, n);
    return 0;
}
