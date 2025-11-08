# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
void appendLog(void) 
{
    const char *fname = "log.txt";
    int fd = open(fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) 
    {
        perror("Error opening log.txt");
        return;
    }

    // Read a line from stdin
    // Until newline or EOF
    char input[4096];
    ssize_t r = 0;
    size_t total_read = 0;
    while (total_read < sizeof input - 1) {
        ssize_t rr = read(STDIN_FILENO, input + total_read, 1);
        if (rr < 0) 
        {
            if (errno == EINTR)
            {
                continue;
            }
            perror("Error reading stdin for log");
            close(fd); // Closing before returning
            return;
        } 
        else if (rr == 0) 
        {
            break;
        } 
        else 
        {
            total_read += 1;
            if (input[total_read - 1] == '\n') // New line is provided
            {
                break;
            }
        }
    }
    input[total_read] = '\0';

    // Remove trailing newline for processing
    bool has_newline = false;
    if (total_read > 0 && input[total_read - 1] == '\n') {
        has_newline = true;
        input[total_read - 1] = '\0';
    }

    pid_t pid = getpid();
    char outbuf[8192];
    int n = snprintf(outbuf, sizeof outbuf, "PID=%d: %s", (int)pid, input);
    if (n < 0) 
    {
        perror("Error during snprintf");
        close(fd); // Closing before returning
        return;
    }

    /* Ensure trailing newline */
    if (!has_newline) {
        if ((size_t)n + 1 >= sizeof outbuf) 
        {
            fprintf(stderr, "Input too long for log line\n");
            close(fd); // Closing before
            return;
        }
        outbuf[n]   = '\n';
        outbuf[n+1] = '\0';
        n += 1;
    } 
    else 
    {
        // Original input had new line
        // But we removed it for processing
        // Now, need to add it back
        if ((size_t)n + 1 >= sizeof outbuf) 
        {
            fprintf(stderr, "Input too long for log line\n");
            close(fd);
            return;
        }
        outbuf[n] = '\n';
        outbuf[n+1] = '\0';
        n += 1;
    }

    if (write(fd, outbuf, (size_t)n) < 0) {
        perror("Error writing log.txt");
        close(fd); // Closing before returning
        return;
    }

    off_t cur = lseek(fd, 0, SEEK_CUR);
    if (cur < 0) 
    {
        perror("Error during lseek SEEK_CUR after write (log)");
        close(fd); // Closing before returing
        return;
    }
    printf("New file offset after append: %lld\n", (long long)cur);

    /*
     * Explanation (in comment):
     * Even when a file descriptor is opened with O_APPEND, the kernel ensures
     * each write is appended at the current end of file atomically. The file
     * offset is updated to reflect the end of file after the write, so a
     * subsequent call to lseek(fd, 0, SEEK_CUR) returns the offset after the
     * appended write. Thus SEEK_CUR still reflects the growing file size.
     */

    if (close(fd) < 0) 
    {
        perror("Error closing log.txt");
    }
    return;
}

int main() 
{
    appendLog();
    return 0;
}