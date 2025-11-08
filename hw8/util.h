# ifndef UTIL_H
# define UTIL_H

# define PATH_MAX_LEN 4096
# define BUFFER_SIZE 8192

void stripNewline(char *s);
ssize_t write(int fd, const void *buf, size_t count);

# endif /* UTIL_H */