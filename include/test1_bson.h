#include <bson/bson.h>
#include <time.h>

#ifndef TEST1_BSON
#define TEST1_BSON

struct entire_doc {
        bson_t *document;

        struct tm *user_details;
};

static inline void struct_init(struct entire_doc *doc);
static inline void _create_bson_doc(struct entire_doc *doc);
static inline void struct_free(struct entire_doc *doc);
static void append_date(struct entire_doc *doc, int year, int mon, int day);

#endif