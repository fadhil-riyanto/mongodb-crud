#include <mongoc/mongoc.h>
#include <bson/bson.h>

const char* mongo_uri = "mongodb://localhost:27017";

struct mongo_ctx {
        mongoc_client_t *client;
        mongoc_database_t *db;
        mongoc_collection_t *collection;
        mongoc_uri_t *uri;

        bson_error_t error;
};

static void __mongo_init()
{
        mongoc_init();
}

static void __mongo_check_uri(struct mongo_ctx *ctx)
{
        ctx->uri = mongoc_uri_new_with_error(mongo_uri, &ctx->error);

        if (!ctx->uri) {
                fprintf(stderr, "err: %s | %s", mongo_uri, ctx->error.message);
        }
}

static void __mongo_create_ctx(struct mongo_ctx *ctx)
{

}



int main(void)
{
        struct mongo_ctx ctx;
        __mongo_init();
        __mongo_check_uri(&ctx);
        return 0;
}