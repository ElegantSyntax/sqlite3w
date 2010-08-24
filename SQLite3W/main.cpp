#include <iostream>
#include <string>
#include "sqlw.h"

int main()
{
	SQLdb *db = new SQLdb();
	
	db->connect("test.db");

	if (db->table_exists("test"))
	{
		db->query("INSERT INTO test (name, number) VALUES ('Joe3', 8)");

		if (db->fetch_row())
		{
			std::cout << "Insert Succeeded";
		}
	}

	std::string query = "SELECT * FROM test";

	db->query(query);

	 while (db->fetch_row())
	 {
		 std::cout << "Name: " << db->column(0) << std::endl;			
		 std::cout << "Number: " << db->column(1) << std::endl << std::endl;			
		 
		 std::cout << "Name: " << db->column("name") << std::endl;			
		 std::cout << "Number: " << db->column("number") << std::endl << std::endl;			
	 }

	 db->close();
	 
	 system("pause");
	 return 0;
}