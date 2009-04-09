// include LiteSQL's header file and generated header file
#include <iostream>
#include "litesql.hpp"
#include "pomotuxdatabase.hpp"
#include <time.h>
#include <string>

// no name collisions expected
using namespace litesql;
using namespace pomotuxdatabase;
using namespace std;

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
	at.mIsFinished = false;
	at.mNumPomodoro = 15;
	at.mOrder = 2;
	at.update();				// make this activity persistent

	/* another activity */
	Activity at2(db);        
	at2.mDescription = "A second dummy Activity tomorrow";
	at2.mInsertionDate = (int) seconds + (24 * 60 * 60);	// just to play, this is inserted tomorrow
	at2.mDeadLine = 6;
	at2.mIsFinished = false;
	at2.mNumPomodoro = 1;
	at2.mOrder = 3;
	at2.update();
	
	Activity at3(db);        
	at3.mDescription = "A third dummy Activity tomorrow";
	at3.mInsertionDate = (int) seconds + 2 * (24 * 60 * 60);	// just to play, this is inserted tomorrow
	at3.mDeadLine = 123123;
	at3.mIsFinished = false;
	at3.mNumPomodoro = 9;
	at3.mOrder = 1;
	at3.update();
	
	Activity at4(db);        
	at4.mDescription = "A fourth dummy Activity tomorrow";
	at4.mInsertionDate = (int) seconds + 2 * (24 * 60 * 60);	// just to play, this is inserted tomorrow
	at4.mDeadLine = 123123;
	at4.mIsFinished = false;
	at4.mNumPomodoro = 9;
	at4.mOrder = 4;
	at4.update();
	

	/* activity linked in AIS */
	ais.InsertActivity(db,at,ais);
	ais.InsertActivity(db,at2,ais);
	ais.InsertActivity(db,at3,ais);
	ais.InsertActivity(db,at4,ais);
	
	/* one activity linked in TDTS */
	tdts.ScheduleActivity(db,at,ais,tdts);
	tdts.ScheduleActivity(db,at2,ais,tdts);
	tdts.ScheduleActivity(db,at3,ais,tdts);
	tdts.ScheduleActivity(db,at4,ais,tdts);
	
	
	tdts.Push(db,at,tdts,1);
	
	at3.Modify(at3, 0, string(""));
	//at2.Delete(db,at2, ais, tdts);
	
	
	
	
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

