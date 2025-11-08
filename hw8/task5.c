# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

# include "util.h"

void sparseFile(void) 
{
    const char *fname = "sparse.bin";
    int fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) 
    {
        perror("Error opening sparse.bin");
        return;
    }

    const char *start = "START";
    const char *end   = "END";

    if (write(fd, start, strlen(start)) < 0) 
    {
        perror("Error writing START");
        close(fd); // Closing before returning
        return;
    }

    /* skip forward by 1 MiB from current position */
    off_t skip = 1024 * 1024; /* 1 MiB */
    off_t newpos = lseek(fd, skip, SEEK_CUR);
    if (newpos < 0) 
    {
        perror("Error during lseek skip 1MiB");
        close(fd); // Closing before returning
        return;
    }

    if (write(fd, end, strlen(end)) < 0) 
    {
        perror("Error writing END");
        close(fd); // Closing before returning
        return;
    }

    if (close(fd) < 0) 
    {
        perror("Error closing sparse.bin after write");
    }
    // Reopening the file for reading
    fd = open(fname, O_RDONLY);
    if (fd < 0) 
    {
        perror("Error during reopening sparse.bin");
        return;
    }
    off_t apar_size = lseek(fd, 0, SEEK_END);
    if (apar_size < 0) 
    {
        perror("Error during lseek SEEK_END (sparse)");
        close(fd); // Closing before returning
        return;
    }
    printf("Apparent file size (bytes): %lld\n", (long long)apar_size);

    /*
     * Note: On many file systems, this will report an apparent size >= 1,048,581
     * (START (5) + 1,048,576 skip + END (3) = 1,048,584). The actual disk usage
     * (what 'du' reports) is often much smaller because the region we skipped
     * was not written with zeros; instead, the file contains a hole. The file
     * system records those holes without allocating disk blocks, so the apparent
     * size is large while actual allocated blocks are few.
     */

    if (close(fd) < 0) 
    {
        perror("Error closeing sparse.bin");
    }
    return;
}

int main(void) 
{
    sparseFile();
    return 0;
}



