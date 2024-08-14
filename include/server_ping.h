#ifndef SERVER_PING_H
#define SERVER_PING_H

#include <mongoc/mongoc.h>
#include <bson/bson.h>

struct mongo_ctx {
        mongoc_client_t *client;
        mongoc_database_t *db;
        mongoc_collection_t *collection;
        mongoc_server_api_t *api;
        mongoc_uri_t *uri;

        bson_error_t error;
        bson_t *command;
        
};

static void __mongo_init(struct mongo_ctx *ctx);
static inline int __mongo_check_uri(struct mongo_ctx *ctx);
static void mongo_create_ctx(struct mongo_ctx *ctx);
static void mongodb_cleanup(struct mongo_ctx *ctx);
static void mongodb_ping(struct mongo_ctx *ctx);

#endif