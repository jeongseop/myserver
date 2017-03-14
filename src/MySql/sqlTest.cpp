#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
using namespace std;

int main() {
	try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;

		driver = get_driver_instance();
		con = driver->connect("tcp://192.168.0.100", "sjs", "1q2w3e4r!Q");
		con->setSchema("jeongseop");

		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT 'TEST' AS C1, 1 AS C2 FROM DUAL");
		while(res->next())
		{
			cout << "Test1 : " << res->getString("C1") << endl;
			cout << "Test2 : " << res->getString("C2") << endl;
			cout << endl;
		}

		delete res;
		delete stmt;
		delete con;
	} catch(sql::SQLException &e) {
		cout << "ERROR!!!" << endl;
	}
	return 0;
}
