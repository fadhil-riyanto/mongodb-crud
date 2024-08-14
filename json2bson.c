#include "include/json2bson.h"
#include "bson/bson.h"
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

static bson_t* start_convert(const char *json)
{
        bson_error_t error;
        bson_t *bson = bson_new_from_json((const uint8_t*)json, -1, &error);

        if (!bson) {
                printf("err: %s\n", error.message);
        }
        return bson;
}

static char* intepret_bson(bson_t *obj)
{
        char* string = bson_as_canonical_extended_json (obj, NULL);
        printf("%s\n", string);
        return string;
}

int main(void)
{
        int fd = open("../test.json", O_RDONLY);
        if (fd < 0)
                perror("open");

        int fz = getstat(fd);

        char* rawtext = create_heap_str(fd, fz);

        bson_t *res = start_convert(rawtext);
        free(intepret_bson(res));

        // printf("%s", rawtext);
        free(rawtext);
        close(fd);
        return 0;
}