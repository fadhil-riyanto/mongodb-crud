#include <bson/bson.h>
#include <time.h>
#include "include/test1_bson.h"

static inline void _create_bson_doc(struct entire_doc *doc)
{
        doc->document = bson_new();
}

static inline void struct_init(struct entire_doc *doc)
{
        _create_bson_doc(doc);
        struct tm *tm_heap = (struct tm*)malloc(sizeof(struct tm));
        doc->user_details = tm_heap;
}

static void append_date(struct entire_doc *doc, int year, int mon, int day)
{
        doc->user_details->tm_year = year;
        doc->user_details->tm_mon = mon;
        doc->user_details->tm_mday = day;
        
        bson_append_date_time(doc->document, 
                                "born", 
                                -1, 
                                mktime(doc->user_details) * 1000
        );
}

static void intepret_bson(bson_t *document)
{
        char* str = bson_as_canonical_extended_json (document, NULL);
        printf ("%s\n", str);
        bson_free (str);
}

static inline void struct_free(struct entire_doc *doc)
{
        free(doc->user_details);
        bson_destroy(doc->document);
}

int main(void)
{
        struct entire_doc doc;
        struct_init(&doc);

        append_date(&doc, 2020, 31, 1);
        intepret_bson(doc.document);
        struct_free(&doc);

}