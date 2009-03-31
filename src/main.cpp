// include LiteSQL's header file and generated header file
#include <iostream>
#include "litesql.hpp"
#include "pomotuxdatabase.hpp"
#include <time.h>
/*// provide implementation for Person::sayHello
void example::Person::sayHello() {
    std::cout << "Hi! My name is " << name 
        << " and I am " << age << " years old." << std::endl;
}*/

// no name collisions expected
using namespace litesql;
using namespace pomotuxdatabase;

int main(int argc, char **argv) {
    try {
        // using SQLite3 as backend
         PomotuxDatabase db("sqlite3", "database=pomotux.db");
        // create tables, sequences and indexes
        db.verbose = true;
	if(db.needsUpgrade())
		db.upgrade();
        //db.create();
        // start transaction
        db.begin();
	
	ActivityInventorySheet ais(db);     
	ais.update();

	Activity at(db);        
	at.mDescription = "A dummy Activity";
	time_t seconds;
 	 seconds = time (NULL);
	at.mInsertionDate = (int) seconds;
	at.mDeadLine = 6;
	at.mIsFinished = true;
	at.mNumPomodoro = 15;
	at.update();	

	Activity at2(db);        
	at2.mDescription = "A second dummy Activity tomorrow";
	at2.mInsertionDate = (int) seconds + (24 * 60 * 60);
	at2.mDeadLine = 6;
	at2.mIsFinished = false;
	at2.mNumPomodoro = 1;
	at2.update();

	InsertActivity::link(db,at,ais);
	InsertActivity::link(db,at2,ais);
	// commit transaction
        db.commit();
        // clean up 
        //db.drop();
    } catch (Except e) {
        cerr << e << endl;
        return -1;
    }
    return 0;
}

