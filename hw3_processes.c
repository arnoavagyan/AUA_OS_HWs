#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

void assignment1()
{
    int pid = fork();
    if (pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child Process: PID = %d\n", getpid());
    }
    else
    {
        // Parent process
        printf("Parent Process: PID = %d\n", getpid());
    }
}

void assignment2()
{
    // Part 1 of the assignment
    int pid1 = fork();
    if (pid1 < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid1 == 0)
    {
        // Child process
        printf("Child Process: PID = %d\n", getpid());
    }
    else
    {
        // Parent process
        printf("Parent Process: PID = %d\n", getpid());
        int status;
        wait(&status);
        printf("Child exited with status %d\n", status);
    }
    // Part 2 of the assignment
    int pid2 = fork();
    if (pid2 < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid2 == 0)
    {
        // Child process
        printf("Child Process: PID = %d\n", getpid());
    }
    else
    {
        // Parent process
        printf("Parent Process: PID = %d\n", getpid());
        int status;
        waitpid(pid2, &status, 0);
        printf("Child exited with status %d\n", status);
    }
}

void goodbye()
{
    printf("Goodbye, World!\n");
}

void now()
{
    printf("Current time: %ld\n", time(NULL));
}

void assignment3()
{
    // This part is taken from the slides
    if (atexit(goodbye))
    {
        fprintf(stderr, "atexit() failed!\n");
    }
    if (atexit(now))
    {
        fprintf(stderr, "atexit() failed!\n");
    }
    printf("Hello, World!\n");
    exit(0);
    // Functions are invoked in the reverse order that they are registered(LIFO).
    // atexit() is useful when having multiple exit points in a program.
    // For example, in the Robotics code, if an error occurs in the moving function, we want to make sure that the robot stops moving before exiting.
}

void assigment4()
{
    int pid1 = fork();
    if (pid1 < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid1 == 0)
    {
        // Child process
        exit(9);
    }
    else
    {
        // Parent process
        int status;
        wait(&status);
        // I didn't know how to print the exit status correctly, so I looked it up on the internet.
        if (WIFEXITED(status) < 0)
        {
            printf("Child exited abnormally with status %d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("Child exited normally with status %d\n", WEXITSTATUS(status));
        }
    }
    int pid2 = fork();
    if (pid2 < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid2 == 0)
    {
        // Child process
        abort(); // Abnormal termination
    }
    else
    {
        // Parent process
        int status;
        waitpid(pid2, &status, 0);
        if (WIFEXITED(status) < 0)
        {
            printf("Child exited abnormally with status %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)) 
        {
            printf("Child exited abnormally with status %d\n", WTERMSIG(status));
        }

    }
}

void assignment5()
{
    int pid = fork();
    if (pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child Process: PID = %d\n", getpid());
        exit(0);
    }
    else
    {
        // Parent process
        sleep(10); // Sleep for 10 seconds
    }    
}

int main()
{
    // assignment1();
    // assignment2();
    // assignment3();
    // assigment4();
    assignment5();
    return 0;
}