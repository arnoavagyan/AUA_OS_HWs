# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

# include "util.h"

void copyFile(char srcPath[], char dstPath[])
{
    int fdSrc = open(srcPath, O_RDONLY);
    // Checking success of opening source file
    if (fdSrc < 0) 
    {
        perror("Error opening source");
        return;
    }

    int fdDst = open(dstPath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    // Checking success of opening/creating destination file
    if (fdDst < 0) 
    {
        perror("Error open/create ing destination");
        close(fdSrc);
        return;
    }

    ssize_t total = 0;
    char buf[COPY_BUF];
    while (1) {
        ssize_t r = read(fdSrc, buf, sizeof buf);
        if (r < 0) 
        {
            if (errno == EINTR) 
            {    
                continue;
            }
            perror("Error reading source");
            break;
        } 
        else if (r == 0) 
        {
            /* EOF */
            break;
        } 
        else 
        {
            ssize_t w = write(fdDst, buf, (size_t)r);
            if (w < 0) 
            {
                perror("Error writing to destination");
                break;
            }
            total += w;
        }
    }

    if (close(fdSrc) < 0) 
    {
        perror("Error closing source");
    }
    if (close(fdDst) < 0) 
    {
        perror("Error closing destination");
    }

    printf("Total bytes copied: %zd\n", total);
}

int main()
{    
    char srcPath[PATH_MAX_LEN];
    char dstPath[PATH_MAX_LEN];

    printf("Enter source file path: ");
    fflush(stdout);
    if (!fgets(srcPath, sizeof srcPath, stdin)) 
    {
        perror("Error during fgets");
        return 1;
    }
    stripNewline(srcPath);

    printf("Enter destination file path: ");
    fflush(stdout);
    if (!fgets(dstPath, sizeof dstPath, stdin)) 
    {
        perror("Error during fgets");
        return 1;
    }
    stripNewline(dstPath);

    copyFile(srcPath, dstPath);
    return 0;
}