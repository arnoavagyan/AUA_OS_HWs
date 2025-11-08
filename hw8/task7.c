# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>

# include "util.h"

void fileComparator(char path1[], char path2[]) 
{
    int fd1 = open(path1, O_RDONLY);
    if (fd1 < 0) 
    {
        perror("Error opening first file");
        return;
    }
    int fd2 = open(path2, O_RDONLY);
    if (fd2 < 0) 
    {
        perror("Error opening second file");
        close(fd1);
        return;
    }

    const size_t BUFSZ = 4096;
    unsigned char b1[BUFSZ];
    unsigned char b2[BUFSZ];
    off_t byte_index = 0;

    while (true) 
    {
        ssize_t r1 = read(fd1, b1, BUFSZ);
        if (r1 < 0) 
        {
            if (errno == EINTR) 
            {
                continue;
            }
            perror("Error reading first file");
            break;
        }
        ssize_t r2 = read(fd2, b2, BUFSZ);
        if (r2 < 0) 
        {
            if (errno == EINTR) 
            {
                continue;
            }
            perror("Error reading second file");
            break;
        }

        if (r1 == 0 && r2 == 0) 
        {
            /* both EOF and no differences found */
            printf("Files are identical\n");
            if (close(fd1) < 0) 
            {
                perror("Error closing first file");
            }
            if (close(fd2) < 0) 
            {
                perror("Error closing second file");
            }
            return;
        }

        /* compare up to min(r1, r2) */
        ssize_t cmp_len = (r1 < r2) ? r1 : r2;
        for (ssize_t i = 0; i < cmp_len; ++i) 
        {
            if (b1[i] != b2[i]) 
            {
                printf("Files differ at byte %lld\n", (long long)(byte_index + i));
                if (close(fd1) < 0) 
                {
                    perror("Error closing first file");
                }
                if (close(fd2) < 0)
                {
                    perror("Error closing second file");
                }
                exit(1); // Exiting with 1
            }
        }

        // Reporting difference at end position of shorter file
        if (r1 != r2) 
        {
            if (r1 < r2) 
            {
                printf("Files differ at byte %lld\n", (long long)(byte_index + r1));
                if (close(fd1) < 0) 
                {
                    perror("Error closing first file");
                }
                if (close(fd2) < 0)
                {
                    perror("Error closing second file");
                }
                exit(1); // Exiting with 1
            } 
            else 
            {   // r2 < r1
                printf("Files differ at byte %lld\n", (long long)(byte_index + r2));
                if (close(fd1) < 0) 
                {
                    perror("Error closing first file");
                }
                if (close(fd2) < 0)
                {
                    perror("Error closing second file");
                }
                exit(1); // Exiting with 1
            }
        }

        byte_index += cmp_len;
        // continue loop for next chunks
    }

    /* Shouldn't normally reach here; close files */
    if (close(fd1) < 0) 
    {
        perror("Error closing first file");
    }
    if (close(fd2) < 0)
    {
        perror("Error closing second file");
    }
    exit(1); // Exiting with 1
}

int main()
{
    char path1[PATH_MAX_LEN];
    char path2[PATH_MAX_LEN];

    printf("Enter first file path: ");
    fflush(stdout);
    if (!fgets(path1, sizeof path1, stdin)) 
    {
        perror("fgets");
        return 1;
    }
    stripNewline(path1);

    printf("Enter second file path: ");
    fflush(stdout);
    if (!fgets(path2, sizeof path2, stdin)) 
    {
        perror("fgets");
        return 1;
    }
    stripNewline(path2);

    fileComparator(path1, path2);
    return 0;
}