#include "libmx.h"

char *mx_file_to_str(const char *filename) {
    char *str = mx_strnew(0);
    char *buf = mx_strnew(128);
    int file = open(filename, O_RDONLY);
    ssize_t result = -1;

    if (file != -1) {
        while ((result = read(file, buf, 128)) > 0) {
            char *temp = str;
            
            buf[result] = '\0';
            str = mx_strjoin(str, buf);
            mx_strdel(&temp);
        }
        close(file);
    }

    mx_strdel(&buf);
    
    if (result == -1) {
        mx_strdel(&str);
    }
    return str;
}
