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
        TodoTodaySheet tts(db);
	/* menu */
	char control;
	cout << "\nThis is the first time you run this program? (y/n)" << endl;
	cin >> control;
	if (control == 'y' || control == 'Y') {
		ais.update();
		tts.update();
	} else {
		ais = select<ActivityInventorySheet>(db, ActivityInventorySheet::Id == 1).one();
		tts = select<TodoTodaySheet>(db, TodoTodaySheet::Id == 1).one();
	}	
	int controller = 1;
	while (controller == 1) {
	cout << "\n";
	cout << "********************************************************************************" << endl;
	cout << "*                                 MAIN MENU                                    *" << endl;
	cout << "********************************************************************************" << endl;
	cout << "* 1 - Create an activity                                                       *" << endl;
	cout << "* 2 - Modify an activity                                                       *" << endl;
	cout << "* 3 - Delete an activity                                                       *" << endl;
	cout << "* 4 - Schedule an activity in the todo today sheet                             *" << endl;
	cout << "* 5 - Increase or decrease the priority of an activity in the todo today sheet *" << endl;
	cout << "* 6 - Finish an activity                                                       *" << endl;
	cout << "* 7 - Postpone Activity                                                        *" << endl;
	cout << "* 8 - Print Menu                                                               *" << endl;
	cout << "* 9 - Close Pomotux                                                            *" << endl;
	cout << "********************************************************************************" << endl;
	cout << "\n";
	cout << "Choose an option: ";
	cin >> controller;
	cout << "\n";	
	if (controller == 1) {
		cout << "CREATE AN ACTIVITY" << endl;
		cout << "\n";
        	Activity at(db);
		string description;
		cout << "Insert a description: ";
		cin.clear();
		cin.ignore(1, '\n');
		getline(cin, description, '\n');
        	at.mDescription = description;
        	time_t seconds;
        	seconds = time (NULL);
        	at.mInsertionDate = (int) seconds;	// dates must be stored in UNIX datetime format (seconds passed from 1-1-1970)
		int days;
		cout << "Insert the number of days until the deadlines: ";
		cin >> days;
        	at.mDeadline = (int) seconds + days*(86400);
        	at.mIsFinished = false;
        	at.mNumPomodoro = 0;
        	at.mOrder = 0;
        	at.update();				// make this activity persistent
        	ais.InsertActivity(db,at,ais);		// insert the activity automatically in the AIS
		cout << endl << "A new activity is successfully created." << endl;
		controller = 1;
	} else if (controller == 2) {
		int id;
		cout << "MODIFY AN ACTIVITY" << endl;
		cout << "\n";
		cout << "Select the ID of the activities you want to modify: ";
		cin >> id;
		cin.clear();
		cin.ignore(1, '\n');
		Activity at = select<Activity>(db, Activity::Id == id).one();
		string newDescription;
		int newDeadline;
		cout << "\nInsert a new description (empty for no changes): ";
		getline(cin, newDescription, '\n');
		cout << "Insert a new deadline (0 for no changes): ";
		cin >> newDeadline;	
		at.Modify(db, at, newDeadline, newDescription);
		cout << endl << "The activity is successfully modified." << endl;
 		controller = 1;
	} else if (controller == 3) {
		int id;
		cout << "DELETE AN ACTIVITY" << endl;
		cout << "\n";
		cout << "Select the ID of the activities you want to delete: ";
		cin >> id;
		Activity at = select<Activity>(db, Activity::Id == id).one();
		at.Delete(db, at, ais, tts);
		cout << endl << "The activity is successfully deleted." << endl;
		controller = 1;		
	} else if (controller == 4) {
		int id;
		cout << "SCHEDULE AN ACTIVITY IN A TODO TODAY SHEET" << endl;
		cout << "\n";
		cout << "Select the ID of the activities you want to schedule: ";
		cin >> id;
		Activity at = select<Activity>(db, Activity::Id == id).one();
		tts.ScheduleActivity(db, at, ais, tts);
		cout << endl << "The activity is successfully scheduled." << endl;
		controller = 1;
	} else if (controller == 5) {
		int id, direction;
		cout << "INCREASE OR DECREASE THE PRIORITY OF AN ACTIVITY" << endl;
		cout << "\n";
		cout << "Select the ID of the activities you want to prioritize: ";
		cin >> id;
		Activity at = select<Activity>(db, Activity::Id == id).one();
		cout << "**********************************************" << endl;
		cout << "                PRIORITY MENU                *" << endl;
		cout << "**********************************************" << endl;
		cout << "* -1 - If you want to increase the priority  *" << endl;
		cout << "*  1 - If you want to decrease the priority  *" << endl;
		cout << "**********************************************" << endl;
		cout << "\n";
		cout << "Choose an option: ";
		cin >> direction;
		tts.MoveActivity(db, at, tts, direction);
		controller = 1; 	
	} else if (controller == 6) {
		int id;
		cout << "FINISH AN ACTIVITY" << endl;
		cout << "Select the ID of the activities you want to schedule: ";
		cin >> id;
		Activity at = select<Activity>(db, Activity::Id == id).one();
		tts.FinishActivity(db, at, tts);
		cout << endl << "The activity is successfully finished." << endl;
		controller = 1;
	} else if (controller == 7) {
		int id;
		cout << "Select the ID of the activities you want to post-pone: ";
		cin >> id;
		Activity at = select<Activity>(db, Activity::Id == id).one();
		tts.PostponeActivity(db, at, tts);
		cout << endl << "The activity is successfully postponed." << endl;
		controller = 1;
	} else if (controller == 8) {
		int selection;
		cout << "*************************" << endl;
		cout << "*      PRINT MENU       *" << endl;
		cout << "*************************" << endl;
		cout << "* 1 - Print the AIS     *" << endl;
		cout << "* 2 - Print the TTS	*" << endl;
		cout << "*************************" << endl;
		cout << "\n";
		cout << "Choose an option: ";
		cin >> selection;
		if (selection == 1) {
			vector<Activity> currentAISActivities = ActivityInAIS::get<Activity>(db,Expr(),
            			ActivityInAIS::ActivityInventorySheet==1).orderBy(Activity::Id).all();
			cout << "\nAIS" << endl;
			cout << "ID  | DESCRIPTION" << endl;
			for (vector<Activity>::iterator i = currentAISActivities.begin(); i != currentAISActivities.end(); i++) 
				cout << (*i).id << "   | " << (*i).mDescription << "\n";
		} else {
			vector<Activity> currentTTSActivities = ActivityInTTS::get<Activity>(db,Expr(),
            			ActivityInTTS::TodoTodaySheet==1).orderBy(Activity::MOrder).all();
			cout << "\nTTS" << endl;
			cout << "ID  | DESCRIPTION | order | deadline" << endl;
			for (vector<Activity>::iterator i = currentTTSActivities.begin(); i != currentTTSActivities.end(); i++) 
				cout << (*i).id << " | " << (*i).mDescription << " | " << (*i).mOrder << (*i).mDeadline << "\n";
		}
		controller = 1;
	} else if (controller < 1 || controller > 9) {
		cout << "Your input is not correct. Try again" << endl;
		controller = 1;
	} else {
		controller = 0;
	}
	}
        // commit transaction
        db.commit();
	cout << "See you the next time!" << endl;
        // clean up
        //db.drop();
    } catch (Except e) {
        cerr << e << endl;
        return -1;
    }
    return 0;
}


