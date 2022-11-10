#include "libmx.h"

static char* split_on(char *str, char delim, char **remainder) {
    char *end = mx_strchr(str, delim);

    if (end != NULL) {
        *end = '\0';
        *remainder = mx_strdup(end + 1);
    }
    else {
        *remainder = NULL;
    }

    return str;
}

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    static char *remainder = NULL;
    char *str = NULL;
    int total = 0;
    char *buf = mx_strnew(buf_size);
    ssize_t result = -1;

    if (remainder != NULL) {
        str = split_on(remainder, delim, &remainder);
        total = mx_strlen(str);
        str = mx_realloc(str, total + 1);
        if (remainder != NULL) {
            if (mx_strlen(remainder) == 0) {
                mx_strdel(&remainder);
            }
            *lineptr = str;
            return total;
        }
    }

    while ((result = read(fd, buf, buf_size)) > 0) {
        buf[result] = '\0';
        split_on(buf, delim, &remainder);
        total += mx_strlen(buf);
        str = mx_realloc(str, total + 1);
        mx_strcat(str, buf);
        if (remainder != NULL) {
            if (mx_strlen(remainder) == 0) {
                mx_strdel(&remainder);
            }
            break;
        }
    }

    mx_strdel(&buf);

    if (result == -1) {
        mx_strdel(&str);
        mx_strdel(&remainder);
        return -2;
    }

    if (str == NULL) {
        return -1;
    }

    *lineptr = str;
    return total;
}
