//SQLite3 Wrapper

// STL Includes
#include <string>

// SQLite3 Includes
#include "sqlite3/sqlite3.h"

class SQLdb
{
	protected:
		// Properties
		sqlite3 *db;					// Database connection
		sqlite3_stmt *res;		// Results from a query
		
		const char *tail;			// ?Haven't figure out what this does?
		
		const char *sqliteErrorMsg;			// Holds an sqlite error
		int status;									// Store the sqlite error codes
		
	public:
		// Methods
		SQLdb();
		
		bool connect(std::string DBFILE);	// Establish a connection to a database
		
		bool query(std::string SQL);				// Query the database

		bool fetch_row();	// Move through the rows within a result

		std::string column(int COLUMN_INDEX);	// Return a string with the value of the the column
		std::string column(std::string COLUMN_NAME);	// Return a string with the value of the the column

		bool close();
};