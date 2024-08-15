#ifndef CONN_H
#define CONN_H

#include "mongoc/mongoc.h"
struct ctx {
        mongoc_client_t *client;
        mongoc_collection_t *coll;
        mongoc_cursor_t *cursor;
        bson_error_t error;
        bson_oid_t oid;
        bson_t *doc;
};

void setup_conn(struct ctx *ctx, const char* uri);
void select_coll_db(struct ctx *ctx, char* dbname, char* collname); /* return ctx */
void db_clean(struct ctx *ctx);

#endif