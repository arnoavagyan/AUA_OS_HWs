# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <sys/stat.h>

# include "util.h"

void overwriteNumber(void) {
    const char *fname = "numbers.txt";

    /* Create/truncate and write lines 1..10 */
    int fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) 
    {
        perror("Error opening numbers.txt for write");
        return;
    }
    char linebuf[32];
    for (int i = 1; i <= 10; ++i) 
    {
        int n = snprintf(linebuf, sizeof linebuf, "%d\n", i);
        if (n < 0) 
        {
            perror("Error during snprintf numbers");
            close(fd); // Closing before returning
            return;
        }
        if (write(fd, linebuf, (size_t)n) < 0) 
        {
            perror("Error writing numbers.txt");
            close(fd); // Closing before returning
            return;
        }
    }
    if (close(fd) < 0) 
    {
        perror("Error closing numbers.txt after write");
    }

    /* Reopen with O_RDWR */
    fd = open(fname, O_RDWR);
    if (fd < 0) 
    {
        perror("Error reopening numbers.txt O_RDWR");
        return;
    }

    /* Determine file size and read entire file into memory for easy manipulation */
    struct stat st;
    if (fstat(fd, &st) < 0) 
    {
        perror("Error for fstat numbers.txt");
        close(fd); // Closing before returning
        return;
    }
    off_t fsize = st.st_size;
    if (fsize < 0) 
    {
        fsize = 0;
    }

    char *buf = malloc((size_t)fsize + 1);
    if (!buf) 
    {
        fprintf(stderr, "Malloc failed\n");
        close(fd); // Closing before returning
        return;
    }

    if (lseek(fd, 0, SEEK_SET) < 0) 
    {
        perror("Error duringlseek rewind numbers");
        free(buf); // Freeing before returning
        close(fd); // Closing before returning
        return;
    }

    ssize_t rr = read(fd, buf, (size_t)fsize);
    if (rr < 0) 
    {
        perror("Error reading numbers into memory");
        free(buf); // Freeing before returning
        close(fd); // Closing before returning
        return;
    }
    buf[rr] = '\0';
    size_t totalSize = (size_t)rr;

    /* Scan to find start and end of line 4.
     * Lines are 1-based; line 4 starts after three newline characters.
     * We must count newlines and record offsets.
     */
    size_t start4 = 0;
    size_t end4 = 0;
    int newlineCount = 0;
    for (size_t i = 0; i < totalSize; ++i) 
    {
        if (newlineCount == 3) 
        {
            /* start4 should be i (start of line 4) */
            start4 = i;
            /* find end4 as the position of the newline that ends line 4 */
            size_t j = i;
            while (j < totalSize && buf[j] != '\n') 
            {
                ++j;
            }
            if (j < totalSize && buf[j] == '\n') 
            {
                end4 = j; /* position of newline char */
            } 
            else 
            {
                end4 = totalSize - 1; /* no newline found, rare */
            }
            break;
        }
        if (buf[i] == '\n') 
        {
            newlineCount++;
        }
    }

    if (newlineCount < 3) 
    {
        fprintf(stderr, "Couldn't find line 4 in numbers.txt (unexpected)\n");
        free(buf); // Freeing before returning
        close(fd); // Closing before returning
        return;
    }

    /* remainder begins after end4 (i.e., end4 + 1) */
    size_t remainderStart = end4 + 1;
    size_t remainderLen = 0;
    if (remainderStart <= totalSize) 
    {
        remainderLen = totalSize - remainderStart;
    }
    else 
    {
        remainderLen = 0;
    }

    /* Prepare new content for line 4: "100\n" */
    const char *newline4 = "100\n";
    size_t newlen4 = strlen(newline4);

    /* We'll reconstruct: [prefix up to start4] + newline4 + [remainder] */
    size_t prefixLen = start4;
    size_t newTotal = prefixLen + newlen4 + remainderLen;

    char *newbuf = malloc(newTotal);
    if (!newbuf) {
        fprintf(stderr, "malloc failed for newbuf\n");
        free(buf); // Freeing before returning
        close(fd); // Closing before returning
        return;
    }

    /* copy prefix */
    if (prefixLen > 0) 
    {
        memcpy(newbuf, buf, prefixLen);
    }
    /* copy new line 4 */
    memcpy(newbuf + prefixLen, newline4, newlen4);
    /* copy remainder */
    if (remainderLen > 0) 
    {
        memcpy(newbuf + prefixLen + newlen4, buf + remainderStart, remainderLen);
    }

    /* Now write newbuf back to file: seek to start and overwrite, then truncate if needed */
    if (lseek(fd, 0, SEEK_SET) < 0) 
    {
        perror("Error lseek rewind for overwrite");
        free(buf);    // Freeing before returning
        free(newbuf); // Freeing before returning
        close(fd);    // Closing before returning
        return;
    }

    if (write(fd, newbuf, newTotal) < 0) 
    {
        perror("Error writing  new numbers.txt content");
        free(buf);    // Freeing before returning
        free(newbuf); // Freeing before returning
        close(fd);    // Closing before returning
        return;
    }

    /* If new total is smaller than original, truncate; if larger, file already extended */
    if ((off_t)newTotal != (off_t)totalSize) 
    {
        if (ftruncate(fd, (off_t)newTotal) < 0) 
        {
            perror("Error during ftruncate after overwrite");
        }
    }

    /* Print final file content to stdout */
    if (lseek(fd, 0, SEEK_SET) < 0) 
    {
        perror("Error during lseek rewind to print final numbers");
    }
    else 
    {
        char outbuf[256];
        ssize_t r2;
        printf("Final numbers.txt content:\n");
        while ((r2 = read(fd, outbuf, sizeof outbuf)) > 0) 
        {
            if (write(STDOUT_FILENO, outbuf, (size_t)r2) < 0) 
            {
                perror("Error writing stdout final numbers");
                break;
            }
        }
        if (r2 < 0) 
        {
            perror("Error reading final numbers file");
        }
    }

    free(buf); // Freeing buffer
    free(newbuf); // Freeing new buffer
    if (close(fd) < 0) 
    {
        perror("Error closing numbers.txt");
    }
}

int main()
{
    overwriteNumber();
    return 0;
}