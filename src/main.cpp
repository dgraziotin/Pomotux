// include LiteSQL's header file and generated header file
#include <iostream>
#include "litesql.hpp"
#include "pomotuxdatabase.hpp"
#include <time.h>

// no name collisions expected
using namespace litesql;
using namespace pomotuxdatabase;

void pomotuxdatabase::Activity::Delete(litesql::Database& database, Activity& delActivity, ActivityInventorySheet& currentAIS, TodoTodaySheet& currentTDTS){
		std::cout << "troia.";
}

void pomotuxdatabase::ActivityInventorySheet::InsertActivity(litesql::Database& database, Activity& delActivity, ActivityInventorySheet& currentAIS){
		std::cout << "troia.";
}

void pomotuxdatabase::TodoTodaySheet::PickUpActivity(litesql::Database& database, Activity& delActivity, ActivityInventorySheet& currentAIS, TodoTodaySheet& currentTDTS){
		std::cout << "troia.";
}
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
	
	/* creation of one Activity Inventory Sheet */
	ActivityInventorySheet ais(db);     
	/* make it persistent */
	ais.update();
	
	/* same for one Todo Today Sheet*/
	TodoTodaySheet tdts(db);     
	tdts.update();

	/* creation of an activity */
	Activity at(db);        
	at.mDescription = "A dummy Activity";
	time_t seconds;
 	 seconds = time (NULL);
	at.mInsertionDate = (int) seconds;	// dates must be stored in UNIX datetime format (seconds passed from 1-1-1970)
	at.mDeadLine = 6;			// therefore, this is allowed but not valid
	at.mIsFinished = true;
	at.mNumPomodoro = 15;
	at.update();				// make this activity persistent

	/* another activity */
	Activity at2(db);        
	at2.mDescription = "A second dummy Activity tomorrow";
	at2.mInsertionDate = (int) seconds + (24 * 60 * 60);	// just to play, this is inserted tomorrow
	at2.mDeadLine = 6;
	at2.mIsFinished = false;
	at2.mNumPomodoro = 1;
	at2.update();
	
	/* 
	at the moment, the method is used statically, because we don't 
	know if it's legal to create an instance of a relation defined in the db
	See E/R diagram for a better view
	 */
	/* activity linked in AIS */
	ActivityAIS::link(db,at,ais);
	ActivityAIS::link(db,at2,ais);
	
	/* one activity linked in TDTS */
	ActivityTDTS::link(db,at,tdts);
	
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

