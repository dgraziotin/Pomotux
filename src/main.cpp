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

int main(int argc, char **argv)
{
    try {
        // using SQLite3 as backend
        PomotuxDatabase db("sqlite3", "database=pomotux.db");
        // create tables, sequences and indexes
        db.verbose = true;
        if (db.needsUpgrade())
            db.upgrade();
        //db.create();
        // start transaction
        db.begin();
        /* creation of one Activity Inventory Sheet */
        ActivityInventorySheet ais(db);
        /* make it persistent */
        ais.update();
        /* same for one Todo Today Sheet*/
        TodoTodaySheet tts(db);
        tts.update();
	/* menu */
	int controller = 1;
	while (controller == 1) {
	cout << "\n";
	cout << "MAIN MENU" << endl;
	cout << "1 - Create an activity" << endl;
	cout << "2 - Modify an activity" << endl;
	cout << "3 - Delete an activyty" << endl;
	cout << "4 - Schedule an activity in the todo today sheet" << endl;
	cout << "5 - Increase or decrease the priority of an activity in the todo today sheet" << endl;
	cout << "6 - Finish an activity" << endl;
	cout << "7 - Close Pomotux" << endl;
	cout << "\n";
	cout << "Choose an option: ";
	cin >> controller;
	cout << "\n";
	if (controller == 1) {
		//creation of an activity
        	Activity at(db);
		string description;
		cout << "Insert a description" << endl;
		cin >> description;
        	at.mDescription = description;
        	time_t seconds;
        	seconds = time (NULL);
        	at.mInsertionDate = (int) seconds;	// dates must be stored in UNIX datetime format (seconds passed from 1-1-1970)
		int days;
		cout << "Insert the number of days until the deadlines" << endl;
		cin >> days;
        	at.mDeadline = (int) seconds + days*(86400);
        	at.mIsFinished = false;
        	at.mNumPomodoro = 0;
        	at.mOrder = 0;
        	at.update();				// make this activity persistent
        	ais.InsertActivity(db,at,ais);		// insert the activity automatically in the AIS
		controller = 1;
	} else if (controller == 2) {
		int id;
		cout << "Select the ID of the activities you want to modify" << endl;
		cin >> id;
		Activity at = select<Activity>(db, Activity::Id == id).one();
		string newDescription;
		int newDeadline;
		cout << "Insert a new description (empty for no changes)" << endl;
		cin >> newDescription;
		cout << "Insert a new deadline (0 for no changes)" << endl;
		cin >> newDeadline;	
		at.Modify(db, at, newDeadline, newDescription);
 		controller = 1;
	} else if (controller == 3) {
		int id;
		cout << "Select the ID of the activities you want to delete" << endl;
		cin >> id;
		Activity at = select<Activity>(db, Activity::Id == id).one();
		at.Delete(db, at, ais, tts);
		controller = 1;
	} else if (controller == 4) {
		int id;
		cout << "Select the ID of the activities you want to schedule" << endl;
		cin >> id;
		Activity at = select<Activity>(db, Activity::Id == id).one();
		tts.ScheduleActivity(db, at, ais, tts);
		controller = 1;
	} else if (controller == 5) {
		int id, direction;
		cout << "Select the ID of the activities you want to schedule" << endl;
		cin >> id;
		Activity at = select<Activity>(db, Activity::Id == id).one();
		cout << "-1 - If you want to increase the priority" << endl;
		cout << "1 - If you want to decrease the priority" << endl;
		cout << "Choose an option: ";
		cin >> direction;
		tts.MoveActivity(db, at, tts, direction);
		controller = 1; 	
	} else if (controller == 6) {
		int id;
		cout << "Select the ID of the activities you want to schedule" << endl;
		cin >> id;
		Activity at = select<Activity>(db, Activity::Id == id).one();
		tts.FinishActivity(db, at, tts);
		controller = 1;
	} else if (controller < 1 || controller > 7) {
		cout << "Your input is not correct. Try again" << endl;
		controller = 1;
	}
	}
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

