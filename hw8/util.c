# include <string.h>
# include <errno.h>
# include <unistd.h>


# include "util.h"

void stripNewline(char *s) {
    if (!s)
    { 
        return;
    }
    size_t l = strlen(s);
    if (l == 0) 
    {
        return;
    }
    if (s[l-1] == '\n') 
    {
        s[l-1] = '\0';
    }
}

ssize_t write(int fd, const void *buf, size_t count) {
    size_t written = 0;
    const char *p = buf;
    while (written < count) {
        ssize_t w = write(fd, p + written, count - written);
        if (w < 0) {
            if (errno == EINTR) continue;
            return -1;
        }
        written += (size_t)w;
    }
    return (ssize_t)written;
}