#include <iostream>
#include <string>
#include "sqlw.h"

int main()
{
	SQLdb *db = new SQLdb();
	
	db->connect("test.db");

	std::string query = "SELECT * FROM test";

	db->query(query);

	 while (db->step())
	 {
		 std::cout << "Name: " << db->column(0) << std::endl;			
		 std::cout << "Number: " << db->column(1) << std::endl << std::endl;			
	 }

	 db->close();
	 
	 system("pause");
	 return 0;
}