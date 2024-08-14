#include "include/json2bson.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>

static int getstat(int fd)
{
        struct stat st;
        int ret;

        ret = fstat(fd, &st);
        if (ret < 0) {
                perror("stat");
                return -1;
        }

        return st.st_size;
}

static char* create_heap_str(int fd, size_t size)
{
        char* rawtext = (char*)malloc(size);
        int ret = read(fd, rawtext, size);
        if (ret < 0)
                perror("read");
        return rawtext;
}

int main(void)
{
        int fd = open("../test.json", O_RDONLY);
        if (fd < 0)
                perror("open");

        int fz = getstat(fd);

        char* rawtext = create_heap_str(fd, fz);

        printf("%s", rawtext);
        free(rawtext);

        close(fd);
        return 0;
}