#include "sqlw.h"

SQLdb::SQLdb()
{
	this->db = NULL;
	this->res = NULL;
	
	this->tail = NULL;
	
	this->sqliteErrorMsg = NULL;
	this->status = 0;
}

bool SQLdb::connect(std::string DBFILE)
{
	this->status  = sqlite3_open(DBFILE.c_str(), &(this->db));
	
	if (this->status != SQLITE_OK)
	{
		sqlite3_close(this->db);
		return false;
	}
	
	return true;
}

bool SQLdb::query(std::string SQL)
{
	if (sqlite3_finalize(this->res) != SQLITE_OK)
	{
		sqlite3_close(this->db);
		return false;
	}
	this->status = sqlite3_prepare_v2(this->db, SQL.c_str(), SQL.length(), &(this->res), &(this->tail));
	
	if (this->status != SQLITE_OK)
	{
		sqlite3_close(this->db);
		return false;
	}
}

bool SQLdb::fetch_row()
{
	if (sqlite3_step(this->res) == SQLITE_ROW)
	{
		return true;
	}

	return false;
}

std::string SQLdb::column(int COLUMN_INDEX)
{
	int numCol = sqlite3_column_count(this->res);
	if ( numCol > 0 && COLUMN_INDEX < numCol)
	{
		std::string result(reinterpret_cast<const char*>(sqlite3_column_text(this->res, COLUMN_INDEX)));
		return result;
	}

	return "ERROR: NOTHING!";
}

std::string SQLdb::column(std::string COLUMN_NAME)
{
	int numCol = sqlite3_column_count(this->res);

	if (numCol > 0)
	{
		for (int i = 0; i < numCol; i++)
		{
			if (COLUMN_NAME == sqlite3_column_name(this->res, i))
			{
				std::string result(reinterpret_cast<const char*>(sqlite3_column_text(this->res, i)));
				return result;
			}
		}
	}

	return "ERROR: NOTHING!";
}

bool SQLdb::close()
{
	if (sqlite3_finalize(this->res) == SQLITE_OK)
	{
		if (sqlite3_close(this->db) == SQLITE_OK)
		{
			return true;
		}
	}

	return false;
}