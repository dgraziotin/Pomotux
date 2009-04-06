// include LiteSQL's header file and generated header file
#include <iostream>
#include "litesql.hpp"
#include "pomotuxdatabase.hpp"
#include <time.h>
#include "iactivity.hpp"
#include "iactivityinventorysheet.hpp"
#include "itodotodaysheet.hpp"


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
	
	/* creation of one Activity Inventory Sheet */
	IActivityInventorySheet ais(db);     
	/* make it persistent */
	ais.update();
	
	/* same for one Todo Today Sheet*/
	ITodoTodaySheet tdts(db);     
	tdts.update();

	/* creation of an activity */
	IActivity at(db);        
	at.set_mDescription("A dummy Activity");
	time_t seconds;
 	 seconds = time (NULL);
	at.set_mInsertionDate((int) seconds);	// dates must be stored in UNIX datetime format (seconds passed from 1-1-1970)
	at.set_mDeadline(6);			// therefore, this is allowed but not valid
	at.set_mIsFinished(true);
	at.set_mNumPomodoro(15);
	at.update();				// make this activity persistent

	/* a third debug activity */
	IActivity at2(db,"third activity",(int)seconds,(int) seconds + (24 * 60 * 60));
	at2.update();
	/* 
	at the moment, the method is used statically, because we don't 
	know if it's legal to create an instance of a relation defined in the db
	See E/R diagram for a better view
	 */
	/* activity linked in AIS */
	InsertActivity::link(db,at,ais);
	InsertActivity::link(db,at2,ais);
	
	/* one activity linked in TDTS */
	PickUpActivity::link(db,at,tdts);
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

