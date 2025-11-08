# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>


# include "util.h"

void reverseReader(char path[])
{
    int fd = open(path, O_RDONLY);
    if (fd < 0) 
    {
        perror("Error while opening file for reverse");
        return;
    }

    off_t sz = lseek(fd, 0, SEEK_END);
    if (sz < 0) 
    {
        perror("Errro during lseek SEEK_END (reverse)");
        close(fd); // Clsoing file before returning
        return;
    }

    if (sz == 0) // Empty file
    {
        if (write(STDOUT_FILENO, "\n", 1) < 0) 
        {
            perror("Error writing a newline");
        }
        close(fd); // Closing file before returning
        return;
    }

    unsigned char c;
    for (off_t pos = sz - 1; pos >= 0; --pos) 
    {
        if (lseek(fd, pos, SEEK_SET) == (off_t)-1) 
        {
            perror("Error during lseek in reverse loop");
            break;
        }
        ssize_t r = read(fd, &c, 1);
        if (r < 0) 
        {
            if (errno == EINTR) 
            { 
                pos++; 
                continue; // Retry reading the same position
            }
            perror("Error reading in reverse loop");
            break;
        } 
        else if (r == 0) 
        {
            break;
        } 
        else 
        {
            if (write(STDOUT_FILENO, &c, 1) < 0) 
            {
                perror("Error writing stdout (reverse)");
                break;
            }
        }
        if (pos == 0) 
        {
            break;
        }
    }

    if (write(STDOUT_FILENO, "\n", 1) < 0) 
    {
        perror("Error writing a newline after reverse");
    }
    if (close(fd) < 0) 
    {
        perror("Error closing reverse file");
    }
}


int main()
{
    char path[PATH_MAX_LEN];
    printf("Enter path to an existing text file: ");
    fflush(stdout);
    if (!fgets(path, sizeof path, stdin)) 
    {
        perror("fgets");
        return 1;
    }
    stripNewline(path);

    reverseReader(path);
    return 0;
}