#include "include/conn.h"
#include "mongoc/mongoc.h"

void setup_conn(struct ctx *ctx, const char* uri)
{
        mongoc_init();
        ctx->client = mongoc_client_new(uri);
}

void select_coll_db(struct ctx *ctx, char* dbname, char* collname)
{
        ctx->coll = mongoc_client_get_collection(ctx->client, dbname, collname);
}

void db_clean(struct ctx *ctx)
{
        mongoc_collection_destroy(ctx->coll);
        mongoc_client_destroy(ctx->client);
        mongoc_cleanup();
}