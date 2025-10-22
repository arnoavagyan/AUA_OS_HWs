Author: Arno Avagyan
Title: Description for HW7

Each part in the assignment is implemented as a separate function.

For FCFS:
The code sorts by arrival time and sequentially executes.

For SJF:
Since the first row of Gantt chart is sorted by burst time, there is a separate function to print via this order.
The function findLowestBurstTime(...) tries to find process with minimal burst time which has arrived(<current_time)
In the SJF() I continuously use findLowestBurstTime() to get correct processes by returned index.

Main:
The input actions of user are fully matching with the assignment requirements. 
Since I dont copy array before algorithm, by default 2 calls are commented enabling user to choose desired algorithm.

How to run:
gcc scheduling.c -o sch
./sch
Then follow the instructions for input values.
