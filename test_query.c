#include <bson/bson.h>
#include "include/conn.h"
#include "mongoc/mongoc.h"
#include <time.h>

static void run_query_find(struct ctx *ctx)
{
        const bson_t *doc;
        char *str;

        bson_t *query = bson_new();
        ctx->cursor = mongoc_collection_find_with_opts(ctx->coll, query, NULL, NULL);

        while(mongoc_cursor_next(ctx->cursor, &doc)) {
                str = bson_as_canonical_extended_json(doc, NULL);
                printf ("%s\n", str);
                bson_free(str);
        }
}

int main(void)
{
        struct ctx ctx;

        setup_conn(&ctx, "mongodb://localhost:27017");
        select_coll_db(&ctx, "test-db", "collection"); /* return ctx */

        run_query_find(&ctx);

        db_clean(&ctx);

}