#include <mongoc/mongoc.h>
#include <bson/bson.h>
#include <stdio.h>
#include <time.h>
#include "include/server_ping.h"

const char* mongo_uri = "mongodb://localhost:27017";

/* start mongodb internal */
static void __mongo_init(struct mongo_ctx *ctx)
{
        ctx->client = NULL;
        mongoc_init();

}

static inline int __mongo_check_uri(struct mongo_ctx *ctx)
{
        ctx->uri = mongoc_uri_new_with_error(mongo_uri, &ctx->error);

        if (!ctx->uri) {
                fprintf(stderr, "err: %s | %s\n", mongo_uri, ctx->error.message);
                return -1;
        }
        return 0;
}

static void mongo_create_ctx(struct mongo_ctx *ctx)
{
        int ret = 0;
        int ok = 0;

        ret = __mongo_check_uri(ctx);
        if (ret == -1) {
                printf("url failed\n");
                return;
        }
                

        ctx->client = mongoc_client_new(mongo_uri);

        if (!ctx->client) {
                fprintf(stdout, "conn error\n");
                mongodb_cleanup(ctx);
        }

        /* set client stable API */
        ctx->api = mongoc_server_api_new(MONGOC_SERVER_API_V1);
        ok = mongoc_client_set_server_api(ctx->client, ctx->api, &ctx->error);
        if (!ok) {
                fprintf(stdout, "conn error %s\n", ctx->error.message);
                mongodb_cleanup(ctx);
                return;
        }

}

static void mongodb_ping(struct mongo_ctx *ctx)
{
        int ok = 0;
        bson_t reply = BSON_INITIALIZER;

        ctx->db = mongoc_client_get_database(ctx->client, "admin");
        if (!ctx->db) {
                fprintf(stdout, "db get err.\n");
                mongodb_cleanup(ctx);
                return;
        }

        /* start ping */
        ctx->command = BCON_NEW("ping", BCON_INT32(1));
        ok = mongoc_database_command_simple(ctx->db, ctx->command, 
                NULL, &reply, &ctx->error);

        if (!ok) {
                fprintf(stdout, "err query: %s\n", ctx->error.message);
                mongodb_cleanup(ctx);
                return;
        }

        bson_destroy(&reply);
        printf("ping done\n");

        // ctx->co
}

static void mongodb_cleanup(struct mongo_ctx *ctx)
{
        mongoc_client_destroy(ctx->client);
        mongoc_cleanup();
}

int main(void)
{
        struct mongo_ctx ctx;
        __mongo_init(&ctx);
        mongo_create_ctx(&ctx);
        mongodb_ping(&ctx);

        // mongodb_cleanup(&ctx);
        return 0;
}