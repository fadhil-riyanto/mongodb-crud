#include <bson/bson.h>
#include <string.h>

int main() 
{
        bson_t b;
        bson_t child;
        bson_array_builder_t *listint;

        bson_init(&b);
        bson_append_utf8(&b, "name", strlen("name"), "fadhil", strlen("fadhil"));
        bson_append_int32(&b, "umur", -1, 18);

        bson_append_document_begin(&b, "personal", -1, &child);
        bson_append_utf8(&child, "nim", -1, "a11202415691", -1);
        bson_append_document_end(&b, &child);

        bson_append_array_builder_begin(&b, "data_list", -1, &listint);
        bson_array_builder_append_int32(listint, 3);
        bson_array_builder_append_int32(listint, 2);
        bson_array_builder_append_int32(listint, 6);
        bson_append_array_builder_end(&b, listint);

        char *str = bson_as_relaxed_extended_json (&b, NULL);

        printf ("%s\n", str); // Prints: { "foo" : { "baz" : 1 } }
        bson_free (str);
        bson_destroy (&b);

}