#include <bson/bson.h>
#include <mongoc/mongoc.h>
#include <stdio.h>

int
main (void)
{
    const bson_t *doc;

    mongoc_init ();

    mongoc_client_t *client = mongoc_client_new ("mongodb+srv://test:test@cluster0.bdt4998.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0");
    mongoc_collection_t *collection = mongoc_client_get_collection (client, "jun112025", "test1");


/*--------------------------read data from database ----------------------------------*/
/*
    // Specify the query filter 
    bson_t *query = BCON_NEW ("speed",BCON_DOUBLE(2.34));
    mongoc_cursor_t *results = mongoc_collection_find_with_opts (collection, query, NULL, NULL);

    // Print the results
    while (mongoc_cursor_next (results, &doc))
    {
        char* str = bson_as_canonical_extended_json (doc, NULL);
        printf ("%s\n", str);
        bson_free (str);
    }

    bson_destroy (query);
    mongoc_cursor_destroy (results);
    */
    
    
/*--------------------------Insert single data into database ----------------------------------*/    
   
	/*   
	bson_t *document = BCON_NEW ("test", BCON_UTF8 ("76"));
	bson_error_t error;
	if (!mongoc_collection_insert_one (
		collection, document, NULL, NULL, &error)) {
		fprintf (stderr, "Insert one operation failed: %s\n", error.message);
	}
	bson_destroy (document);
    */
    
/*--------------------------Insert multiple data into database ----------------------------------*/        
    /*
    size_t num_docs = 2;
	bson_t *docs[num_docs];
	docs[0] = BCON_NEW ("test", BCON_UTF8 ("45"));
	docs[1] = BCON_NEW ("speed", BCON_UTF8 ("4.56"));
	bson_error_t error;
	if (!mongoc_collection_insert_many (collection, (const bson_t **) docs, num_docs, NULL, NULL, &error)) {
		fprintf (stderr, "Insert many operation failed: %s\n", error.message);
	}
	bson_destroy (docs[0]);
	bson_destroy (docs[1]);*/
	
/*--------------------------Insert multiple data inside single obejct into database ----------------------------------*/   

	bson_error_t error;
	mongoc_bulk_operation_t *bulk =
	   mongoc_collection_create_bulk_operation_with_opts (collection, NULL);
	bson_t *insert_doc = BCON_NEW (
		"test", BCON_UTF8 ("a"),
		"test1", BCON_UTF8 ("c"),
		"test2", BCON_UTF8 ("b"),
		"test3", BCON_UTF8 ("r")
	);
	mongoc_bulk_operation_insert(bulk, insert_doc);
	bson_destroy (insert_doc);
		
	bson_t *query = BCON_NEW ("<field to match>", BCON_UTF8 ("<value to match>"));
	bson_t *update = BCON_NEW ("$set", "{", "<field name>", BCON_UTF8 ("<value>"), "}");
	mongoc_bulk_operation_update_one(bulk, query, update, false);
	bson_destroy(query);
	bson_destroy(update);
	bool result = mongoc_bulk_operation_execute(bulk, NULL, &error);
	if (!result) {
		fprintf (stderr, "Bulk operation error: %s\n", error.message);
	}
	mongoc_bulk_operation_destroy (bulk);


/*--------------------------destroy all ----------------------------------*/   
 
    mongoc_collection_destroy (collection);
    mongoc_client_destroy (client);
    mongoc_cleanup ();

    return EXIT_SUCCESS;
}
