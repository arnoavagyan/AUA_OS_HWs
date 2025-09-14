#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/wait.h>

void assign0()
{
    printf("Assignment 0:\n");
    int ret;
    ret = fork();
    if (ret == 0)
    {
        printf("Child Process\n");
        sleep(2);
        // _exit(0); // I've added _exit to ensure child processes terminate properly, since I will have repeated messages
    }
    else
    {
        printf("Parent Process\n");
        wait(NULL);
        sleep(2);
    }
    ret = fork();
    if (ret == 0)
    {
        printf("Child Process\n");
        sleep(2);
        // _exit(0);
    }
    else
    {
        printf("Parent Process\n");
        wait(NULL);
        sleep(2);
    }
    ret = fork();
    if (ret == 0)
    {
        printf("Child Process\n");
        sleep(2);
        // _exit(0);
    }
    else
    {
        printf("Parent Process\n");
        wait(NULL);
        sleep(2);
    }
}

void assign1()
{
    printf("Assignment 1:\n");
    int ret = fork();
    if (ret == 0)
    {
        int execRet = execl("/bin/ls", "ls", NULL);
        if (execRet == -1)
        {
            printf("execl failed\n");
            _exit(1);
        }
    }
    else
    {
        wait(NULL);
        printf("Parent process done\n");
    }
}

void assign2()
{
    printf("Assignment 2:\n");
    int ret = fork();
    if (ret == 0)
    {
        int execRet = execl("/bin/ls", "ls", NULL);
        if (execRet == -1)
        {
            printf("execl failed\n");
            _exit(1);
        }
    }
    else
    {
        wait(NULL);
    }
    ret = fork();
    if (ret == 0)
    {
        int execRet = execl("/bin/date", "date", NULL);
        if (execRet == -1)
        {
            printf("execl failed\n");
            _exit(1);
        }
    }
    else
    {
        wait(NULL);
        wait(NULL);
        printf("Parent process done\n");
    }
}

void assign3()
{
    printf("Assignment 3:\n");
    int ret = fork();
    if (ret == 0)
    {
        int execRet = execl("/bin/echo", "echo", "Hello from the child process", NULL);
        if (execRet == -1)
        {
            printf("execl failed\n");
            _exit(1);
        }
    }
    else
    {
        wait(NULL);
        printf("Parent process done\n");
    }
}

void assign4()
{
    printf("Assignment 4:\n");
    int ret = fork();
    if (ret == 0)
    {
        int execRet = execl("/bin/grep", "grep", "homework", "test.txt", NULL);
        if (execRet == -1)
        {
            printf("execl failed\n");
            _exit(1);
        }
    }
    else
    {
        wait(NULL);
        printf("Parent process completed\n");
    }
}

int main() 
{ 
    // assign0();
    // assign1();
    // assign2();
    // assign3();
    // assign4();
    return 0;
} 