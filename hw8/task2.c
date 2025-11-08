# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

# include "util.h"

void file_truncate(void) {
    const char *fname = "data.txt";
    const char *alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; /* 26 bytes */

    int fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) 
    {
        perror("Error opening data.txt for write");
        return;
    }

    ssize_t w = write(fd, alpha, strlen(alpha));
    if (w < 0) 
    {
        perror("Error writing data.txt");
        close(fd);
        return;
    }
    if (close(fd) < 0) 
    {
        perror("Error closing data.txt after write");
    }

    fd = open(fname, O_RDWR);
    if (fd < 0) 
    {
        perror("Error reopening data.txt O_RDWR");
        return;
    }

    off_t sizeBefore = lseek(fd, 0, SEEK_END);
    if (sizeBefore < 0) 
    {
        perror("Errow while lseek SEEK_END (before)");
        close(fd);
        return;
    }
    printf("Size before truncate: %lld bytes\n", (long long)sizeBefore);

    if (ftruncate(fd, 10) < 0) 
    {
        perror("Error during ftruncate operation");
        close(fd);
        return;
    }

    off_t sizeAfter = lseek(fd, 0, SEEK_END);
    if (sizeAfter < 0) 
    {
        perror("lseek SEEK_END (after)");
        close(fd);
        return;
    }
    printf("Size after truncate: %lld bytes\n", (long long)sizeAfter);

    if (lseek(fd, 0, SEEK_SET) < 0) 
    {
        perror("Error lseek rewind operation");
        close(fd);
        return;
    }

    /* read remaining content and print to stdout */
    char buf[128];
    ssize_t r;
    printf("Contents after truncate:\n");
    while ((r = read(fd, buf, sizeof buf)) > 0) 
    {
        ssize_t w2 = write(STDOUT_FILENO, buf, (size_t)r);
        if (w2 < 0) 
        {
            perror("Error while writing stdout");
            break;
        }
    }
    if (r < 0) 
    {
        perror("Error reading data.txt after truncate");
    }

    if (close(fd) < 0) 
    {
        perror("Error closing data.txt");
    }
    printf("\n");
}


int main()
{
    file_truncate();
    return 0;
}