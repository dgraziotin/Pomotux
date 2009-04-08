// include LiteSQL's header file and generated header file
#include <iostream>
#include "litesql.hpp"
#include "pomotuxdatabase.hpp"
#include <time.h>
#include "iactivity.hpp"
#include "iactivityinventorysheet.hpp"
#include "itodotodaysheet.hpp"// no name collisions expected


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
	
	int userInput;
	while (1)
	{
		cout << "--------Pomotux 1.0.1---------" <<endl;
		cout << "what do you like to do? " <<endl;
		cout << "1 - create a Todo Today Sheet" <<endl;
		cout << "2 - create an Activity" <<endl;
		cout << "3 - find an activity in the AIS given the ID" <<endl;
		cout << "* - to exit" <<endl;
		
		
		cin>>userInput;
		if (userInput==1)
		{
				/* same for one Todo Today Sheet*/
				ITodoTodaySheet tdts(db);     
				tdts.update();
		}
		else if (userInput==2)
		{
				int days;
				string description;
				cout << "Insert Activity Description,please :"<<endl;
				cin>> description;
				cout << " Please insert the number of days before deadline,please :" <<endl;
				cin>> days;
				time_t seconds;
				seconds=time(NULL);  // get the current time
				IActivity at(db,description,(int)seconds,(((int)seconds)+days*(24 * 60 * 60)));
				at.update();
				/* activity linked in AIS */
				InsertActivity::link(db,at,ais);
		}
		
		else if (userInput==3)
		{
				int ID;
				cout <<"Isert activity ID:" << endl;
				cin>> ID;
				
				try
				{
					Activity result = InsertActivity::get<Activity>(db,Activity::Id == 1, InsertActivity::ActivityInventorySheet == 1).one();
				//	vector<Activity> selected =select<Activity>(db,Activity::Id == ID).all(); // I have just one record but it's just a try
				//	for (vector<Activity>::iterator i = selected.begin(); i != selected.end(); i++) cout << toString(*i) << endl;
					cout << result <<endl;
				}catch(NotFound e){
					cout << "No Activity Found" << endl;
					break;
				}
				
				
				
				//IActivity selected = select<Activity> (db,Activity::id == ID).one();
				//cout << IActivity.get_mDescription() <<endl; 
				/*	PersonDatabase db("sqlite3", "database=person.db");
					vector<Person> = select<Person>(db).all();
					Person bob = select<Person>(db, Person::Name == "Bob").one();
					* 
					*  for (vector<Person>::iterator i = family.begin(); i != family.end(); i++) cout << toString(*i) << endl;
				*/
		}
				
		else
		{	
				// commit transaction
				db.commit();
				cout<<"see you!!"<<endl;
				return 0;
		
		}
		
	}


	/* creation of an activity 
	IActivity at(db);        
	at.set_mDescription("A dummy Activity");
	time_t seconds;
 	 seconds = time (NULL);
	at.set_mInsertionDate((int) seconds);	// dates must be stored in UNIX datetime format (seconds passed from 1-1-1970)
	at.set_mDeadline(6);			// therefore, this is allowed but not valid
	at.set_mIsFinished(true);
	at.set_mNumPomodoro(15);
	at.update();				// make this activity persistent */


	/* 
	at the moment, the method is used statically, because we don't 
	know if it's legal to create an instance of a relation defined in the db
	See E/R diagram for a better view
	 */
	/* activity linked in AIS 
	InsertActivity::link(db,at,ais);
	InsertActivity::link(db,at2,ais);
	
	/* one activity linked in TDTS */
	//PickUpActivity::link(db,at,tdts);

        // clean up 
        //db.drop();*/
    } catch (Except e) {
        cerr << e << endl;
        return -1;
    }
    return 0;
}

